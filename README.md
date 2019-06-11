# SIMalert

## Table of Contents
* [Overview ](#Overview)
* [Description ](#Description)
* [Tools](#Tools)
* [How to use](#How-to-use)
* [Attributions](#Attributions)
* [License](#License)
* [Credits](#Credits)
* [Programmer's_notes](#Notes)
## Overview 
Our project is security system that detects movement and alerts the owner about the threat.

## Description 
We used:
* STM32F407VG microcontroller 
* TM1637 LED Display
* 5 IO Keypad - Waveshare
* SIM900A

## Tools 
* Microcontroler was configured using the STM32 CubeMX Project was created in STM System Workbench
* Language used: C.

## How to use
* Plug-in device
* Configure password on first use by pressing 4 keys. (Password is 4-key long)
* After configuring password, device is ready to go.
* Device detects movement, if movement is detected user has 25 seconds to input correct password.
* If time passed, device calls device owner to inform about the threat.

## Attributions
* [rogerdahl](https://github.com/rogerdahl/stm32-tm1637) - creator of tm1637 library for stm32 devices

## License
MIT License 

## Credits 
* [Maciej Owsianny](https://github.com/maciejows)
* [Gracjan Trawiński](https://github.com/akrynos)

The project was conducted during the Microprocessor Lab course held by the [Institute of Control and Information Engineering](http://www.cie.put.poznan.pl/index.php?lang=en), [Poznan University of Technology](https://www.put.poznan.pl/en).
Supervisor: [Tomasz Mańkowski](https://github.com/Tomasz-Mankowski)










###############################################################################

## Notes
2019_SIMalert

After turning ON the SIM900A V5.1 module you need to wait arount 2-5 seconds.
Then the device is fully usable.

Useful AT commands				Comment							Response
ATD+48987654321;<CR><LF> 		//Make a phone call				OK
ATH<CR><LF>  					//Disconnect/hangup call		OK
AT+CMGF=1						//Change mode to sms			OK
AT+CMGS="+48987654321"<CR><LF> 	//Set SMS Number				>
	then
		This is just a message	//Set SMS Content				>
	then
		1A						//ASCII code of CTRL+Z (HEX)

Control AT commands
AT<CR><LF>  					//Basic command that tests the connection with the module
AT+COPS?<CR><LF> 				//Returns the current mode and the operator
AT+CPAS<CR><LF> 				//Reutrns the activity status, 0 - Ready	
AT+CSQ<CR><LF> 					//Signal Quality level (the higher val (max 31 or 7) the better)

while loop: 
	if movement sensor in high state -> trigger counter (change variable counting to 1)
	when counting==1 enable keyboard and allow to enter 4-digit code to stop counting.

TIM4: 
	if counting==1, starts to count, when 20 seconds passes launch alert() function,
	else reset time

alert(): 
	sends SMS to a specified number, after that dial the number, hang up after 25 seconds repeat unless picked up

How it works step-by-step:
	1. Wait for movement
	2. Movement detected - trigger time counter
	3. Wait (20s) for a user to enter the 4-digit code
		3.1. Entered code is correct
			3.1.1 Stop time counter and reset counted time
		3.2. Entered code is incorrect
			3.1.1 Change nothing, keep counting, let user enter the code again
		3.3. Time's up - trigger SMS and dial function
		3.4. Dial number until picked up
	4. Reset all variables after the operations