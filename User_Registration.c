User_Registration()
{
	web_set_sockets_option("SSL_VERSION", "2&3");
	
	lr_output_message("Iteration Number: %d", atoi(lr_eval_string("{pIterationNumber}")));
		
	web_reg_find("Text=Web Tours",
				 "SaveCount=WebTours_Count",
	             LAST);

	lr_start_transaction("SC01_WebTours_T01_LaunchPage");

	web_url("WebTours", 
		"URL=http://{pServerName}:{pPortNo}/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_reg_find("Text=&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;",
	             "SaveCount=Header_Text_Count",
				 LAST);
		
	web_url("header.html", 
		"URL=http://{pServerName}:{pPortNo}/WebTours/header.html", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/WebTours/", 
		"Snapshot=t14.inf", 
		"Mode=HTTP", 
		LAST);

	web_reg_find("Text=<frame src=\"nav.pl?in=home\" name=\"navbar\"",
	             "SaveCount=Frame_Welcome_Count",
				 LAST);
	
	web_url("welcome.pl", 
		"URL=http://{pServerName}:{pPortNo}/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/WebTours/", 
		"Snapshot=t18.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);	
	
	web_concurrent_start(NULL);

	web_url("hp_logo.png", 
		"URL=http://{pServerName}:{pPortNo}/WebTours/images/hp_logo.png", 
		"Resource=1", 
		"RecContentType=image/png", 
		"Referer=http://{pServerName}:{pPortNo}/WebTours/header.html", 
		"Snapshot=t19.inf", 
		LAST);

	web_url("webtours.png", 
		"URL=http://{pServerName}:{pPortNo}/WebTours/images/webtours.png", 
		"Resource=1", 
		"RecContentType=image/png", 
		"Referer=http://{pServerName}:{pPortNo}/WebTours/header.html", 
		"Snapshot=t20.inf", 
		LAST);

	web_concurrent_end(NULL);
	
	web_concurrent_start(NULL);
		
	web_reg_find("Text=To make reservations,please enter your account information to the left.", 
	             "SaveCount=Information_Message_Count",
				 LAST);

	web_url("home.html", 
		"URL=http://{pServerName}:{pPortNo}/WebTours/home.html", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t22.inf", 
		"Mode=HTTP", 
		LAST);

	web_reg_find("Text=&nbsp;Password", 
	             "SaveCount=Login_Frame_Count",
				 LAST);

	web_url("nav.pl", 
		"URL=http://{pServerName}:{pPortNo}/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t26.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_url("mer_login.gif", 
		"URL=http://{pServerName}:{pPortNo}/WebTours/images/mer_login.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/nav.pl?in=home", 
		"Snapshot=t30.inf", 
		LAST);
	
	if(atoi(lr_eval_string("{WebTours_Count}")) > 0)
	{
		lr_end_transaction("SC01_WebTours_T01_LaunchPage", LR_PASS);
	}
	else
	{
		lr_end_transaction("SC01_WebTours_T01_LaunchPage", LR_FAIL);
		lr_output_message("Vuser ID %d encountered an error in Iteration Number %d.",atoi(lr_eval_string("{pVUserID}")), atoi(lr_eval_string("{pIterationNumber}")));
	}

	lr_think_time(10);
	
	lr_rendezvous("Landing_Page_Rend");
	
	web_reg_find("Text=Customer Profile",
				 "SaveCount=CustomerProfile_Count",
				 LAST);

	lr_start_transaction("SC01_WebTours_T02_ClickSignUp");

	web_url("sign up now", 
		"URL=http://{pServerName}:{pPortNo}/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/WebTours/home.html", 
		"Snapshot=t36.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);
	
	web_reg_find("Text=var allAtOnce = true;",
				 "SaveCount=Profile_Validation_Count",
				 LAST);
	
	web_url("profileValidate.js", 
		"URL=http://{pServerName}:{pPortNo}/WebTours/profileValidate.js", 
		"Resource=1", 
		"RecContentType=application/javascript", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t58.inf", 
		LAST);
	
	web_url("button_next.gif", 
		"URL=http://{pServerName}:{pPortNo}/WebTours/images/button_next.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t84.inf", 
		LAST);
	
	web_concurrent_end(NULL);	

	if(atoi(lr_eval_string("{CustomerProfile_Count}")) > 0)
	{
		lr_end_transaction("SC01_WebTours_T02_ClickSignUp",LR_PASS);
	}
	else
	{
		lr_end_transaction("SC01_WebTours_T02_ClickSignUp",LR_FAIL);
		lr_output_message("Vuser ID %d encountered an error in Iteration Number %d.",atoi(lr_eval_string("{pVUserID}")), atoi(lr_eval_string("{pIterationNumber}")));
	}
	
	lr_think_time(10);

	web_reg_find("Text=Thank you, ",
	             "SaveCount=Thankyou_Count",
	             LAST);
		
	lr_start_transaction("SC01_WebTours_T03_ClickContinue");

	web_submit_data("login.pl", 
		"Action=http://{pServerName}:{pPortNo}/cgi-bin/login.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{pServerName}:{pPortNo}/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t59.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=username", "Value={pUsername}", ENDITEM, 
		"Name=password", "Value={pPassword}", ENDITEM, 
		"Name=passwordConfirm", "Value={pPassword}", ENDITEM, 
		"Name=firstName", "Value={pFirstName}", ENDITEM, 
		"Name=lastName", "Value={pLastName}", ENDITEM, 
		"Name=address1", "Value={pAddress1}", ENDITEM, 
		"Name=address2", "Value={pAddress2}", ENDITEM, 
		"Name=register.x", "Value=46", ENDITEM, 
		"Name=register.y", "Value=8", ENDITEM, 
		LAST);

	if(atoi(lr_eval_string("{Thankyou_Count}")) > 0)
	{
		lr_end_transaction("SC01_WebTours_T03_ClickContinue",LR_PASS);
	}
	else
	{
		lr_end_transaction("SC01_WebTours_T03_ClickContinue",LR_FAIL);
		lr_output_message("Vuser ID %d encountered an error in Iteration Number %d.",atoi(lr_eval_string("{pVUserID}")), atoi(lr_eval_string("{pIterationNumber}")));
	}
	
	return 0;
}