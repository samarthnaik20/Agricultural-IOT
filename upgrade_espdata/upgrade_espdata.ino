#include <easyMesh.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(16, 5); // RX, TX            // GPIO16 to Arduino 11 and GPIO5 to Arduino 10
char* ndata;
char* ndata1;

#define   MESH_PREFIX     "FarmAssist"
#define   MESH_PASSWORD   "agriculturalIOT"
#define   MESH_PORT       0001
#define nonodes 6

int b = 1;
easyMesh  mesh;
int samay = 120000; 

String fmsg = "";
String marray[nonodes][7]; 
int k = 0;
int q = 0;


const char* ssid ="Tides M2";
const char* password="summer_camp";
const char* server = "https://agriculturetest.000webhostapp.com"; 
String host = "agriculturetest.000webhostapp.com";
String url = "tabletime.php";

const int BROADCAST_TIME = 10000; // 10 seconds

int i = 0;
/*void post(char* data){
  Serial.print(data);
  
  mySerial.write(data);
  }
*/
int p = 0;
void setup() {
  Serial.begin(9600);
  delete[] ndata;
  delete[] ndata1;
  
  if(q==1 and p == 1)
  { WiFi.mode(WIFI_OFF);
    Serial.println("Sending to Arduino");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
 
    }
  
  else
  {
 
//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT );
  mesh.setReceiveCallback( &receivedCallback );
  mesh.setNewConnectionCallback( &newConnectionCallback );

  //randomSeed( analogRead( A0 ) ); 
  }

   
}


void loop() {

 // Serial.print(millis());
 // Serial.print("\n");
  
  if ((unsigned long)(millis() / samay) >= b and q == 0) {
  q = 1;
  Serial.print(b);
  Serial.print("\n");
  b = b + 1;
  }
  
  if(p == 0){

  mesh.update();

  // get next random time for send message
  i = i + 1;
  delay(10);

  // if the time is ripe, send everyone a message!
  if ( i > BROADCAST_TIME/10 ){
    //double analogValue = analogRead(A0); // read the analog signal
    //double soilhumid = ((1024-450)-(analogValue-450))/(10.24-4.5);
    
    /*String msg = "IOT**" + "Soil Humidity: " + (String)analogValue + "%**";
    msg += mesh.getChipId();
    msg = msg + "**" + nonodes;
    Serial.println(msg);*/
    
    String msg = "**I am the data node**";
    mesh.sendBroadcast( msg );   //original = IOT_Storage**G50.31**H20.12**T50.65**C294567**N5 or IOT_Field**M20.23**H20.12**T50.65**C294567**N5 
    
    i=0;
  }
  if(q == 1){
  p = 1;
  setup();
  }
}

else{
  if(q == 1 ){

 if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
    
  }
/////////////////////////////////////////////////////for knowing amount of data//////////////////////////////////////////
  ndata1 = "";
  String data1 = '$' + (String)k;
  Serial.println(data1); 
  for(int a = 0 ; a < data1.length(); a++){
  ndata1[a] = (char)data1[a];
  }
  ndata1[data1.length()] = '@';
  Serial.println(ndata1);
  
  for(int i=0; i < data1.length()+1; i++){
  mySerial.write(ndata1[i]);
    }
  delay(2000);
///////////////////////////////////////////////////////actual data////////////////////////////////////////////////////////  
  for(int h = 0 ; h < k ; h++){
     // Serial.print(h);
     // Serial.print("\n");
  ndata = "";
  String data = "type=" + marray[h][0] + "&chip=" + marray[h][1] + "&moisture=" + marray[h][2] + "&gas=" + marray[h][3] + "&humidity=" + marray[h][4] + "&temp=" + marray[h][5] + "&smoke=" + marray[h][6];
  Serial.println(data); 
  for(int a = 0 ; a < data.length(); a++){
  ndata[a] = (char)data[a];
  }
  ndata[data.length()] = '@';
  Serial.println(ndata);
  
  for(int i=0; i < data.length(); i++){
  mySerial.write(ndata[i]);
  }
  delay(1000);
  //post(ndata);
    }
  p = 0;
  q = 0;
  //delete[] ndata;
  //WiFi.mode(WIFI_OFF);
  setup();
  }}

}

int search(String from, String humid, String temp, String moisture, String gas, String smoke )
{ int flag = 0;
  for(int j=0; j<nonodes ; j++)
  {
    if(marray[j][1] == from)
    {
      if(marray[j][2] == moisture and marray[j][3] == gas and marray[j][4] == humid and marray[j][5] == temp and marray[j][6] == smoke){
      flag = 1;
      }
      else{
      marray[j][0] = marray[k-1][0];
      marray[j][1] = marray[k-1][1];
      marray[j][2] = marray[k-1][2];
      marray[j][3] = marray[k-1][3];
      marray[j][4] = marray[k-1][4];
      marray[j][5] = marray[k-1][5];
      marray[j][6] = marray[k-1][6];
      k = k-1;
     
      }
      j = nonodes + 1 ;
    }
  }
    return flag;
}


void receivedCallback( uint32_t from, String &msg ) {

  String msg1 = msg.c_str();
  
  
  if(msg1.indexOf('I')==0 && msg1.indexOf('O')==1 && msg1.indexOf('T')==2)
  {
    int h,t,m,g,c,s = 0;
    bool H,T,M,G,C,S = false;
    String humidity,temp,moisture,gas,chip,smoke;
    int firstStar, fifthStar,thirdStar,seventhStar,ninthStar,star;

    String type = msg1.substring(msg1.indexOf('_') + 1 , msg1.indexOf('*'));
    if(msg1.indexOf('H') > 0 ){
     h = msg1.indexOf('H');
     H = true;
     star = msg1.indexOf('*', h );
     humidity = msg1.substring(h+1,star);
     }
     else {
      H = false;
      humidity = "nan";
      } 

    if(msg1.indexOf('T',msg1.indexOf('*')) > 0 ){
   t = msg1.indexOf('T',msg1.indexOf('*'));
     T = true;
     star = msg1.indexOf('*', t );
     temp = msg1.substring(t+1,star);}
     else {T = false;
           temp = "nan";}

    if(msg1.indexOf('M') > 0 ){
     m = msg1.indexOf('M');
     M = true;
     star = msg1.indexOf('*', m );
     moisture = msg1.substring(m+1,star);}
     else {M = false;
           moisture = "nan";}

    if(msg1.indexOf('G') > 0 ){
     g = msg1.indexOf('G');
     G = true;
     star = msg1.indexOf('*', g );
     gas = msg1.substring(g+1,star);}
     else {G = false;
           gas = "nan";}

    if(msg1.indexOf('C') > 0 ){
     c = msg1.indexOf('C');
     C = true;
     star = msg1.indexOf('*', c );
     chip = msg1.substring(c+1,star);}
     else {C = false;
           chip = "nan";}

    if(msg1.indexOf('S',msg1.indexOf('*')) > 0 ){
     s = msg1.indexOf('S',msg1.indexOf('*'));
     S = true;
     star = msg1.indexOf('*', s );
     smoke = msg1.substring(s+1,star);}
     else {S = false;
           smoke = "nan";}

    

  if( (search(chip,humidity,temp,moisture,gas,smoke) == 0 && k < nonodes) or k==0)
  {
  marray[k][0] = type;
  marray[k][1] = chip;
  marray[k][2] = moisture;
  marray[k][3] = gas;
  marray[k][4] = humidity;
  marray[k][5] = temp;
  marray[k][6] = smoke;
  Serial.println("| " + marray[k][0] + " | " + marray[k][1] + " | " + marray[k][2] + " | " + marray[k][3] + " | " + marray[k][4] + " | " + marray[k][5] + " | " + marray[k][6]);
  Serial.println(k);
  k++;
  
  //Serial.printf("startHere: Received from %d msg=%s\n", from, msg.c_str());
  }
  }
  //Serial.printf("startHere: Received from %d msg=%s\n", from, msg.c_str());

}

void newConnectionCallback( bool adopt ) {
  Serial.printf("startHere: New Connection, adopt=%d\n", adopt);
}

