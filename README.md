# ESD-COURSE-PROJECT
ECEN 5613 - SECURITY SYSTEM

This project majorly divided into 2 parts
1.	Testing routines
2.	Production code routines
Testing routines test whether
1.	Keypad press signal is detected by the Microcontroller.
2.	SD card file is opened and able to write a simple message to that.
3.	PWM configuration to configure basic servo motor movement and Buzzer alarm
4.	LCD display displays messages the devices status at various instances of time.
5.	RFID to detect the presence of an input into the device and display the information.

Production code routines
Previously each components where tested with their functionality.
Keypad signal sends a series of numbers(ID). Or the Signal is detected from the RF ID module.
SD card file is detected and file pointer is moved to the immediate location.
Write the accepted data into a file and rejected data into another file enabling segregation as well.
At every point, the data status accepted or rejected is displayed on the HD44780U LCD display.
A real time clock module of MSP432 is initialized to enable real time timestamp to see the time of entry and time of failed attempt as well.

Hardware Description
Power Supply Unit:
We have a power supply unit that provides 3.3V and 5V combination for a 12V AC input.
The circuit consists of voltage regulators. A series of shunt resistances for voltage division.
Junction Diode for AC-DC rectificiation.
Decouplers for storing voltage to drive the load seamlessly.
Jumper cables provide the user the previlege of selecting 3.3v and 5V depending upon the load.
A thermal fuse to save the device on an unexpected heating scenario.
