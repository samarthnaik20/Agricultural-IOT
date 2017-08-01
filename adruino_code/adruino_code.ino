#include <SoftwareSerial.h>
#define nonodes 3

SoftwareSerial mySerial(10, 11); // RX, TX             //ESP Module -> Arduino 11 to ESP GPIO16 and Arduino 10 to ESP GPIO5
SoftwareSerial SIM900(6, 5);     // RX, TX             // GSM module

#include <avr/wdt.h>


void softwareReset( uint8_t prescaller) {
  // start watchdog with the provided prescaller
  wdt_enable( prescaller);
  // wait for the prescaller time to expire
  // without sending the reset signal by using
  // the wdt_reset() method
  while(1) {}
}


void setup() {
 // pinMode(reset,OUTPUT);
  digitalWrite(2,HIGH);
  delay(200);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  SIM900.begin(9600);
  
  Serial.println("Bhej ESP Bhej!");
  //Serial.println(samay);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  
  //mySerial.println("HI!");
}


String b1;
String h1;
char ch;
String number = "8860729428";
String message;
String php1 = "tabletime.php" ;
String php2 = "sendsmsnew.php" ;
String php3 = "updatesmsnew.php" ;
//int cnt = 1;
int flag = 0;
String url1;// = "AT+HTTPPARA=\"URL\",\"kumarnikhil1198.000webhostapp.com/updatesmsnew.php?type=Storage&chip=087653&moisture=34&gas=23&humidity=32&temp=33&smoke=4534\""; 
//String test = "iuwemsnew.php?type=Storage&chip=087653&moisture=34&gas=23&humidity=32&temp=33\"";
//////////////////////////////////////////////////////////////////function for HTTP get requests to update table////////////////////////////////////////////////////////

void SubmitHttpRequest(String *data, String php, int mode)             ///////////////mode = 0 -> upload to server, mode = 1  -> send sms
{  b1 = "";

  //if(mode != 2){
  mySerial.end();
  SIM900.begin(9600);
  //}
  //test = data;
  url1 = "AT+HTTPPARA=\"URL\",\"kumarnikhil1198.000webhostapp.com/";
  int l1 = url1.length();
  url1 += php;
  int l2 = php.length();
  url1 += "?";
  url1 += *data;
  int l3 = (*data).length();
  url1 += "\"";
  //String test = data + '#';
  //String test = data;
  //String file = php;
  Serial.println(*data);
  Serial.println(php);
  //Serial.println(mode);
  //data = "type=Storage&chip=087653&moisture=34&gas=23&humidity=32&temp=33";
  int l = l1 + l2 + l3 + 2;
  Serial.println(l);
  Serial.println(url1.length());

  
  /*if(url1.length() < l){
  String url = "AT+HTTPPARA=\"URL\",\"kumarnikhil1198.000webhostapp.com/";
  url += php;
  url += '?';
  url += data;
  url += '\"';
  url1 = url;
  }*/
  
  Serial.println(url1);                                          
  
  SIM900.println("AT"); //Attach or Detach from GPRS Support
  delay(200);
  
  if(mode == 1){
  ShowSerialData();}

  SIM900.println("AT+CPIN?"); //Attach or Detach from GPRS Support
  delay(200);
  if(mode == 1 ){
  ShowSerialData();}

  SIM900.println("AT+CREG?"); //Attach or Detach from GPRS Support
  delay(200);
  if(mode == 1){
  ShowSerialData();}
  
  SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
  delay(200);

  if(mode == 1 ){
  ShowSerialData();}
 
  SIM900.println("AT+CSQ"); // Signal quality check

  delay(200);
 if(mode == 1 ){
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
 }
  
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(200);
 if(mode == 1 ){
  ShowSerialData();}
 
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"bsnlnet\"");//setting the APN, Access point name string
  delay(200);
 if(mode == 1 ){
  ShowSerialData();}
 
  SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(200);
 if(mode == 1 ){
  ShowSerialData();}

  SIM900.println("AT+SAPBR=2,1");//setting the SAPBR
  delay(200);
 if(mode == 1 ){
  ShowSerialData();}
 
  SIM900.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(200); 
  if(mode == 1 ){
  ShowSerialData();}

  SIM900.println("AT+HTTPPARA=\"CID\",1"); //init the HTTP request
 
  delay(200); 
  if(mode == 1 ){
  ShowSerialData();}
 
  SIM900.println(url1);// setting the httppara, the second parameter is the website you want to access
  delay(200);
  url1 = "";
  if(mode == 1  ){
  ShowSerialData();}
 
  SIM900.println("AT+HTTPACTION=0");//submit the request 
  delay(4000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  while(!SIM900.available());
  if(mode == 1  ){
  ShowSerialData();}
  
  SIM900.println("AT+HTTPREAD");// read the data from the website you access
  delay(1000);
  //changeLed();
  if(mode == 1  ){
  ShowSerialData();}
  
  Serial.println("done");

  SIM900.println("AT+HTTPTERM");
  delay(1000);

  if(mode == 1){
  Viewdata();
  }
  delay(2000);
}

/////////////////////////////////////////////////////////////////////function to send sms via SIM900a///////////////////////////////////////////////////////////////////////



void sendSMS(String number, String message)
{
  
  SIM900.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(1000);
  //ShowSerialData();
  String command = "AT + CMGS = \"" + number + "\"";
  SIM900.println(command);                                     // recipient's mobile number, in international format E.123
  delay(1000);
  //ShowSerialData();
  SIM900.println(message);        // message to send
  delay(1000);
  //ShowSerialData();
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(1000);
  //ShowSerialData();
  SIM900.println();
  delay(1000);
  //ShowSerialData();
}

/////////////////////////////////////////////////////////////////Store incoming data////////////////////////////////////////////////////
void ShowSerialData()
{
  while(SIM900.available()!=0)
   { ch = char (SIM900.read());
     // Serial.write(ch);
      b1 = b1 + ch;
   }
  // Serial.println(m);
}

///////////////////////////////////////////////////////////////SMS send/////////////////////////////////////////////////////////

void Viewdata(){
  
  if(b1.indexOf('$') > 0){
  h1 = b1.substring(b1.indexOf('$')+1,b1.indexOf('$',b1.indexOf('$')+1));
  Serial.println(h1);
  //b1 = "";
  if(h1.length() < 40 and h1 != NULL){
  Serial.println(h1);
  message = h1; 
  flag = 1;
  Serial.println("Sending SMS...." );
  //sendSMS(number,message);
  Serial.println("SMS sent" );
  /*String m = "number=" + number;
  for(int y=0; y < 2; y++){
  Serial.println("Updating message status" );
  SubmitHttpRequest(m,php3,2);
  Serial.println("DONE - updating message status" );}*/
  }
  }
}

//////////////////////////////////////////////////////////////////////////////Main Code/////////////////////////////////////////////////////////////////////////


char a;
int c = 0;
String b ;
int k = 6;
int count = 0;
String smsarray[nonodes];
String d;


void loop() { // run over and over
  
  //unsigned long time1 = millis()/300000;                    ////////////////////// every in t = 5 minutes
  //Serial.println(time1);
  if((unsigned long) (millis()/300000) >= 1){
  //if(1>0){
  Serial.println(millis());
  
  String m2 = "number=" + number + "&status=not-sent" ;
  Serial.println("Retrieving messages" );
  mySerial.end();
  SIM900.begin(9600);
  SubmitHttpRequest(&m2,php2,1);
  
  if(b1.indexOf('$') > 0 and h1.length() < 40 and h1 != NULL){
  String m = "number=" + number;
  //for(int y=0; y < 2; y++){
  Serial.println("Updating message status" );
  SubmitHttpRequest(&m,php3,0);
  Serial.println("DONE - updating message status" );
  //}
  }
  
  if(flag == 0){
    Serial.println("No new message to send" );
    }
  else{
    flag = 0;
    }
  Serial.println("Finished - Retrieving messages" );
  b1 = "";
  SIM900.end();
  mySerial.begin(9600);
  //cnt++;
  softwareReset( WDTO_60MS);           /////////////////////////////////////////////RESET in 60 millisecs
  delay(2000);
  setup();
  }
  
  
  else
  { //Serial.println("Bhej ESP Bhej!");
  while (mySerial.available()) {
    //Serial.write(mySerial.read());
    a = mySerial.read();
    b = b + a;   
    c = 0;
     
  }
  if(c == 0){
  //Serial.println(b);
  if(b.indexOf('t') == 0 and b.indexOf('p') == 2){
    d = b.substring(b.indexOf('t'),b.indexOf('@'));
    smsarray[count] = d;
    Serial.println(d);
    count++;
    
    if(count >= k){
        
      Serial.println("GSM ko bulate hai ab!");
      //gsm(smsarray)
      for(int o = 0 ; o < k ; o++){
       if(o == 0){
        b = "";
        mySerial.end();
        SIM900.begin(9600);
        } 
      Serial.println("SubmitHttpRequest - started" );
      SubmitHttpRequest(&smsarray[o],php1,0);
      Serial.println("SubmitHttpRequest - ended" );

      if(o == k-1){
      SIM900.end();
      mySerial.begin(9600);
      }  
        
      }
      
      count = 0;
      SIM900.end();
      mySerial.begin(9600);
    }
    }
  if(b.indexOf('$') == 0 and b.indexOf('@') == 2){
    String h = b.substring(b.indexOf('$'),b.indexOf('$')+2);
    Serial.println(h);
    k = (char)h[b.indexOf('$')+1] - '0'; 
    Serial.println(k);
    }
  c = 1;
  b = "";
  }
  //Serial.write(a);
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

  } 
}
