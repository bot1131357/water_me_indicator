/*
 * ATtiny13A_soil_test_v1.cpp
 *
 * Created: 10/22/2017 12:39:23 PM
 * Author : y.tan
 */ 
 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>

// Set ISP speed to 25kHz to communicate with 128kHz device
 #define F_CPU 128000L
 #include <util/delay.h>

// RESET BUTTON - unless you don't want to program this device anymore
//#define DDR_LED_B DDRB
//#define PORT_LED_B PORTB
//#define PIN_LED_B PORTB5
#define DDR_LED_R DDRB
#define PORT_LED_R PORTB
#define PIN_LED_R PORTB1

#define DDR_LED_G DDRB
#define PORT_LED_G PORTB
#define PIN_LED_G PORTB0

#define DDR_SENSOR_PWR DDRB
#define PORT_SENSOR_PWR PORTB
#define PIN_SENSOR_PWR PORTB4

#define DDR_BUTTON DDRB
#define PORT_BUTTON PINB
#define PIN_BUTTON PINB2
#define PCINT_BUTTON PCINT2

#define DDR_SENSOR_AIN DDRB
#define PORT_SENSOR_AIN PINB
#define PIN_SENSOR_AIN PINB3

/** 
 * NOTE: MCU Fuse128kHz, SUT:: 14CK + 64ms, preserve EEPROM (fuse value: 0xff, 0x3b)
 *
 * Directions
 * First time (calibration)
 * 1) Press and hold button while powering up. 
 * 2) Release button when LED is red. (LED starts blinking.)
 * 3) Water the soil to the right level.
 * 4) Insert sensor into soil with right moisture level
 * 5) Press the button (LED stops blinking, and turns green.)
 * 6) From then on, the sensor will check the humidity level every 10 min
 * 
 * Check moisture level
 * 1) Press button.
 * 2) Light shows moisture level (Red = dry, Yellow = medium, Green = ok)
 *
 */

 /** 
  * Watchdog's longest interval is 8 seconds. We want to spend more time sleeping
  * between measurements, so we will add a countdown variable. 
  * Every time ATtiny13A wakes up, we will decrement the variable.
  * When it's zero, we take a measurement.
  * 
  * If the soil is found to be dry, we can change the countdown to a shorter value
  * to make it blink.
  */
 #define NB_WDTIE_NORMAL 75 // 75 * 8 s = 10 minutes
 #define NB_WDTIE_NORMAL 2 // TESTING
 #define NB_WDTIE_WARNING 3 // 2 s (no prescale)
 uint8_t WDT_interval = NB_WDTIE_NORMAL;

/** 
 * Sanity check: Values should never be equal because it's used to identify and 
 * switch between normal and warning states.
 */
#if (NB_WDTIE_NORMAL==NB_WDTIE_WARNING) 
#error "NB_WDTIE_NORMAL should not be equal to NB_WDTIE_WARNING"
#endif

// Taking multiple measurements gives a more averaged value 
#define nb_measures 4

volatile uint16_t humidity_hi = 100<<nb_measures;
#define LED_DIM_VAL 50 // OCR value for dim brightness
#define eeprom_humidity_hi 0
 
void WDT_enableInterrupt(uint8_t timeout){
	cli();
	MCUSR &= ~_BV(WDRF);
	uint8_t b1 = _BV(WDE)|_BV(WDCE);
	uint8_t b2 =   _BV(WDTIE)|_BV(WDCE)|timeout;
	WDTCR |= b1; // unlock
	WDTCR = b2 ; // set register
	sei();
}

 void WDT_disableInterrupt(){
	 cli();
	 wdt_reset();
	 MCUSR &= ~_BV(WDRF);
	 uint8_t b1 =   _BV(WDE)|_BV(WDCE);
	 WDTCR |= b1; // unlock
	 WDTCR = 0x00; // clear register
	 sei();
 }

 /** 
  * Switch between normal and warning modes
  * Note that the WDT interrupt interval is also changed in the process.
  */
 void change_indicator_interval(uint32_t humidity)
 {
	 if(humidity<(humidity_hi>>2)) // less than quarter
	 {
		 if(WDT_interval!=NB_WDTIE_WARNING)
		 {
			 WDT_interval = NB_WDTIE_WARNING; // no prescale
			 WDT_enableInterrupt(_BV(WDP2)|_BV(WDP1)); // 1sec interrupt 
		 }
	 }
	 else
	 {
		 if(WDT_interval!=NB_WDTIE_NORMAL)
		 {
			 WDT_interval = NB_WDTIE_NORMAL; // prescale 75 (75*8 = 600 = 10 min)
			 WDT_enableInterrupt(_BV(WDP0)|_BV(WDP3)); // 8sec interrupt
		 }
	 }
 }

 /** 
  * Indicates different colours from red (0) to green (humidity_hi) 
  * Ideally we want to display blue if the value to significantly higher than 
  * humidity_hi but 1K program memory...
  */
 void indicateHumidity(uint32_t humidity)
 { 
	TCCR0A |= _BV(COM0A1) | _BV(COM0B1); // connect PWM to pin

	change_indicator_interval(humidity);

		// scale relative humidity value to 0-255 range
		humidity=humidity<<8;
		humidity/=humidity_hi;	

		// saturate at 255
		humidity = (humidity<0xff)?humidity:0xff;

		OCR0A = humidity;
		OCR0B = 0xff-(humidity>>1);

	_delay_ms(400);

	TCCR0A &= ~(_BV(COM0A1) | _BV(COM0B1)); // disconnect PWM to pin
	
 }

void wait_for_button_press(void (*cbfun)(void))
{
	while(PORT_BUTTON & _BV(PIN_BUTTON))
	{
		cbfun();
	}
	_delay_ms(50);
	while(!(PORT_BUTTON & _BV(PIN_BUTTON))){}
}

/** 
 * Measure soil humidity
 * Soil humidity is measured (nb_measures) times. Since we aren't using 
 * floating point calculations, taking the sum of multiple measurements
 * can help increase the resolution and also averages the measurements.
 */
uint32_t measure_soil_humidity()
{
	//PORT_SENSOR_PWR |= _BV(PIN_SENSOR_PWR); // power up
	PORT_SENSOR_PWR &= ~_BV(PIN_SENSOR_PWR); // enable sensor current flow
	ADCSRA |= _BV(ADSC); // start conversion
	uint16_t val = 0;
	for (int i=0;i<nb_measures;++i)
	{
		_delay_ms(1);
		ADCSRA |= _BV(ADSC); // start conversion
		while(!(ADCSRA & _BV(ADSC))){}
		val += ADCH;
	}
	
	//PORT_SENSOR_PWR &= ~_BV(PIN_SENSOR_PWR); // power down
	PORT_SENSOR_PWR |= _BV(PIN_SENSOR_PWR); // stop sensor current flow
	
	//return val/nb_measures; // no need division for better resolution
	return val;
}

void sleepNow(){
	cli();
	sleep_enable();
	sei();
	sleep_cpu();
}
#define PRODUCTION
#ifdef PRODUCTION
int main(void)
{
	// disable WDT (NOT WORKING?)
	//WDT_disableInterrupt();
	
	// Preferred mode of sleeping
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	DDR_SENSOR_PWR|=_BV(PIN_SENSOR_PWR);	
	PORT_SENSOR_PWR |= _BV(PIN_SENSOR_PWR); // stop sensor current flow
	DDR_LED_R |= _BV(PIN_LED_R);
	DDR_LED_G |= _BV(PIN_LED_G);
	DDR_BUTTON &= ~_BV(PIN_BUTTON);
	PORTB |= _BV(PIN_BUTTON); // pull-up

	// ADC setup
	ADMUX = _BV(REFS0); // 1.1V ref
	ADMUX |= _BV(ADLAR); // left adjust
	ADMUX |= 3; // PB3 pin
	ADCSRA = _BV(ADEN); // enable
	ADCSRA |= _BV(ADSC); // start first conversion (initialisation)
	//ADCSRA |= _BV(ADIE); // ADC interrupt enable

	// PWM output
	TCCR0A = _BV(COM0A1) | _BV(COM0B1); // clear on compare match
	TCCR0A |= _BV(WGM01)*0 | _BV(WGM00); // fast PWM
	TCCR0B = _BV(CS00);

	// Read from eeprom
	humidity_hi = eeprom_read_word((uint16_t *) eeprom_humidity_hi);

	// If button is pressed, enter calibrate mode
	if(!(PORT_BUTTON & _BV(PIN_BUTTON)))
	{
		OCR0A = LED_DIM_VAL;
		OCR0B = LED_DIM_VAL;
		_delay_ms(50);
		while(!(PORT_BUTTON & _BV(PIN_BUTTON))){}

		wait_for_button_press([](){
			_delay_ms(100);
			OCR0B = (OCR0B>0)? 0:LED_DIM_VAL;
			OCR0A = (OCR0A>0)? 0:LED_DIM_VAL;
		});

		// Get humid value
		humidity_hi = measure_soil_humidity();

		// Store new humidity level
		eeprom_write_word((uint16_t *)eeprom_humidity_hi, humidity_hi);
	}

	// Indicate ready to be left alone
	OCR0A = LED_DIM_VAL;
	OCR0B = 0;
	_delay_ms(1000);
	OCR0A = 0;

	// Set button interrupt	
	GIMSK |= _BV(PCIE);	// Enable pin change (rise/fall) interrupt
	PCMSK = _BV(PCINT_BUTTON);

	// Set watchdog interrupt
	// do not use WDTO_8S = bugged!
	WDT_enableInterrupt(_BV(WDP3)|_BV(WDP0));

	while (1)
	{
		// sleep (wake when button pressed or timer)
		sleepNow();
	}
}


volatile uint8_t wdt_countdown = WDT_interval;
ISR(WDT_vect)
{
	--wdt_countdown;
	if (wdt_countdown==0)
	{
		indicateHumidity(measure_soil_humidity());
		wdt_countdown = WDT_interval;
	}
}

ISR(PCINT0_vect)
{
	if(~(PORT_BUTTON & PIN_BUTTON))
	{
		indicateHumidity(measure_soil_humidity());
	}

	wdt_reset(); // no need to indicate again since we've already pressed the button
	GIFR |= _BV(PCIF); // clear flag
}
#endif // PRODUCTION