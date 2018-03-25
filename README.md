# "Water me" indicator for potted plants

When does a plant need water? Sometimes we can drown our plant, and other times leave them to dry. Depending on air humidity, the soil may require watering at shorter or longer intervals. The truth is, we can't tell just by looking (most of us can't.) The only way then, is to feel the soil with our fingers.

Electrical conductivity varies with the level of moisture in soil, and this property can be used as a rough indicator. This design uses a 
[Funduino soil moisture sensor](http://www.greenelectronicstore.com/sensors/766-funduino-soil-moisture-sensor.html) controlled by an ATtiny13A microcontroller. 

Other components include:
- Push button
- RGB LED
- Button cell and holder
- Resistors: 12k, 3k, 1k

I wanted to see how much I can fit inside the 1K program memory of the ATtiny13A. 

## Requirements
- The device should sip as little power as possible, so that the owner doesn't have to change the battery all the time. This means that it should be sleeping most of the time. The sensor takes about 20mA when turned on, therefore it's important to turn it only when needed.  It should only check the moisture level every 10 min.
- The user should be able to check the moisture level at any time, by pressing a button.
- Soil conductivity is also affected by the type of soil and grain size. Therefore it's impractical to hard code the output signal values. A button is used to calibrate the sensor. An assumption is made that if the signal is less than 25% of the signal when the soil is fully moisturised, then it's too dry. If it's too dry, a warning indicator should activate.

## Usage Instructions
### First time (calibration)
1) Press and hold button while powering up. 
2) Release button when LED is red. (LED starts blinking.)
3) Water the soil to the right level.
4) Insert sensor into soil with right moisture level
5) Press the button (LED stops blinking, and turns green.)
6) From then on, the sensor will check the humidity level every 10 min

### Check moisture level
1) Press button.
2) Light shows moisture level (Red = dry, Yellow = medium, Green = ok)



Prototype:
![Schematic](https://github.com/bot1131357/water_me_indicator/blob/master/media/schematic.png)
![Prototype](https://github.com/bot1131357/water_me_indicator/blob/master/media/prototype.jpg)
[Video](https://photos.app.goo.gl/yZkzm7XO45P768l03)



Reading:
[Soil Electrical Conductivity](https://pubs.ext.vt.edu/content/dam/pubs_ext_vt_edu/442/442-508/442-508_pdf.pdf)
