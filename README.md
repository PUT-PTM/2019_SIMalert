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
	sends SMS to a specified number, after that dial the number, hang up after 20 seconds repeat unless picked up

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