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

