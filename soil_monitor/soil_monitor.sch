EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:soil_monitor-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATTINY13A-P IC1
U 1 1 5A9C62F1
P 4750 3150
F 0 "IC1" H 3950 3550 50  0000 C CNN
F 1 "ATTINY13A-P" H 5400 2750 50  0000 C CNN
F 2 "DIP8" H 5400 3150 50  0000 C CIN
F 3 "" H 3950 3500 50  0000 C CNN
	1    4750 3150
	1    0    0    -1  
$EndComp
$Comp
L Battery BT1
U 1 1 5A9C6DEA
P 6350 3150
F 0 "BT1" H 6450 3200 50  0000 L CNN
F 1 "3V" H 6450 3100 50  0000 L CNN
F 2 "" V 6350 3190 50  0000 C CNN
F 3 "" V 6350 3190 50  0000 C CNN
	1    6350 3150
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 5A9C6E47
P 4150 3750
F 0 "SW1" H 4300 3860 50  0000 C CNN
F 1 "SW_PUSH" H 4150 3670 50  0000 C CNN
F 2 "" H 4150 3750 50  0000 C CNN
F 3 "" H 4150 3750 50  0000 C CNN
	1    4150 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 2500 6350 3000
Wire Wire Line
	6350 2900 5750 2900
Wire Wire Line
	6350 3300 6350 4200
Wire Wire Line
	6350 3400 5750 3400
$Comp
L GND #PWR1
U 1 1 5A9C6F46
P 4650 4300
F 0 "#PWR1" H 4650 4050 50  0001 C CNN
F 1 "GND" H 4650 4150 50  0000 C CNN
F 2 "" H 4650 4300 50  0000 C CNN
F 3 "" H 4650 4300 50  0000 C CNN
	1    4650 4300
	1    0    0    -1  
$EndComp
Connection ~ 6350 3400
Wire Wire Line
	4450 3750 4650 3750
Wire Wire Line
	4650 3750 4650 4300
Wire Wire Line
	3850 3750 3450 3750
Wire Wire Line
	3450 3750 3450 3100
Wire Wire Line
	3450 3100 3750 3100
$Comp
L CONN_01X03 P1
U 1 1 5A9C7399
P 2550 2700
F 0 "P1" H 2550 2900 50  0000 C CNN
F 1 "CONN_01X03" V 2650 2700 50  0000 C CNN
F 2 "" H 2550 2700 50  0000 C CNN
F 3 "" H 2550 2700 50  0000 C CNN
	1    2550 2700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3350 3200 3750 3200
$Comp
L LED_RCBG D1
U 1 1 5A9C7471
P 2550 3650
F 0 "D1" H 2550 4000 50  0000 C CNN
F 1 "LED_RCBG" H 2550 3300 50  0000 C CNN
F 2 "" H 2550 3600 50  0000 C CNN
F 3 "" H 2550 3600 50  0000 C CNN
	1    2550 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 4150 6350 4150
Connection ~ 4650 4150
NoConn ~ 2850 3850
NoConn ~ 3750 3400
$Comp
L PWR_FLAG #FLG1
U 1 1 5A9C7B5D
P 6350 2500
F 0 "#FLG1" H 6350 2595 50  0001 C CNN
F 1 "PWR_FLAG" H 6350 2680 50  0000 C CNN
F 2 "" H 6350 2500 50  0000 C CNN
F 3 "" H 6350 2500 50  0000 C CNN
	1    6350 2500
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 5A9C7B85
P 6350 4200
F 0 "#FLG2" H 6350 4295 50  0001 C CNN
F 1 "PWR_FLAG" H 6350 4380 50  0000 C CNN
F 2 "" H 6350 4200 50  0000 C CNN
F 3 "" H 6350 4200 50  0000 C CNN
	1    6350 4200
	-1   0    0    1   
$EndComp
Connection ~ 6350 4150
Text Label 2850 3450 0    60   ~ 0
R
Text Label 2850 3650 0    60   ~ 0
G
$Comp
L R R1
U 1 1 5A9C7EA0
P 2200 3900
F 0 "R1" V 2280 3900 50  0000 C CNN
F 1 "12k" V 2200 3900 50  0000 C CNN
F 2 "" V 2130 3900 50  0000 C CNN
F 3 "" H 2200 3900 50  0000 C CNN
	1    2200 3900
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5AB78E02
P 3350 2950
F 0 "R2" V 3430 2950 50  0000 C CNN
F 1 "3k" V 3350 2950 50  0000 C CNN
F 2 "" V 3280 2950 50  0000 C CNN
F 3 "" H 3350 2950 50  0000 C CNN
	1    3350 2950
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 5AB78EB6
P 3350 3950
F 0 "R3" V 3430 3950 50  0000 C CNN
F 1 "1k" V 3350 3950 50  0000 C CNN
F 2 "" V 3280 3950 50  0000 C CNN
F 3 "" H 3350 3950 50  0000 C CNN
	1    3350 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3100 3350 3800
Wire Wire Line
	3350 4100 3350 4150
Connection ~ 3350 4150
Connection ~ 6350 2900
Wire Wire Line
	2250 3650 2200 3650
Wire Wire Line
	3150 3300 3750 3300
Wire Wire Line
	3350 2800 3350 2700
Wire Wire Line
	3350 2700 2750 2700
Wire Wire Line
	2750 2800 3150 2800
Wire Wire Line
	3150 2800 3150 3300
Connection ~ 3350 3200
Wire Wire Line
	2750 2600 6350 2600
Connection ~ 6350 2600
Wire Wire Line
	3750 3000 3550 3000
Wire Wire Line
	3550 3000 3550 3450
Wire Wire Line
	3550 3450 2850 3450
Wire Wire Line
	3750 2900 3650 2900
Wire Wire Line
	3650 2900 3650 3650
Wire Wire Line
	3650 3650 2850 3650
Wire Wire Line
	2200 4050 2200 4150
Wire Wire Line
	2200 3650 2200 3750
Text Notes 2500 4700 0    60   ~ 0
ADC: Atmel says output impedance \nshould be 10k or less. Need measuring\nand calculation. (Ro = Rl * (V_open/Vl - 1))
Text Notes 2900 2350 0    60   ~ 0
Sensor output is 0-4.2V with a 5V Vcc, \nso with 3.3V we'll expect a lower \noutput range. This is ok, since we're \nonly interested in a coarse measurement.
$EndSCHEMATC
