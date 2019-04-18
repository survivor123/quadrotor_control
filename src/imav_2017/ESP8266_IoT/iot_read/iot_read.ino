#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <String.h>

//----------------  Fill in your credentails   ---------------------
char ssid[] = "MiFibra-60B8";     // your network SSID (name) 
char pass[] = "madridBatalla"; // your network password
//------------------------------------------------------------------

WiFiClient  client;

unsigned long operador = #######;
unsigned long operadorW = ######;
unsigned int velocidad = 3;
unsigned int altura = 5;
const char * myCounterReadAPIKey = "xxxxxxxxxx";
const char * myWriteAPIKey = "xxxxxxxxxx";    // Paste your ThingSpeak Write API Key between the quotes 
int alturaREAL = 0;
int number = 0;
//--------------------------------------------------------------------------
void setup() {
 //Initialize serial and wait for port to open:
 Serial.begin(9600);
 while (!Serial) {
   ; // wait for serial port to connect. Needed for native USB port only
 }
 WiFi.mode(WIFI_STA);  
 ThingSpeak.begin(client);
}
//------------------------------------------------------------------------
void loop() {

 int statusCode = 0;
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
  //  Serial.print("Attempting to connect to SSID: ");
 
   while(WiFi.status() != WL_CONNECTED){
     WiFi.begin(ssid, pass);
   //   Serial.print(".");
     delay(5000);     
   } 
 //  Serial.println("\nConnected");
 }
 
//------------------------------ up move -------------------------------------
 // Read in field 4 of the public channel recording the temperature
 int high = ThingSpeak.readFloatField(operador, altura); 

 
 // Check the status of the read operation to see if it was successful
 statusCode = ThingSpeak.getLastReadStatus();

 Serial.print(high);
 delay(500); // No need to read the temperature too often.
//-----------------------------------------------------------------------

//-------------------------------------------------------------------------------
if (Serial.available() > 0) {
                // read the incoming byte:
alturaREAL = int(Serial.read());

int x = ThingSpeak.writeField(operadorW,2,  alturaREAL, myWriteAPIKey);
}  

 /*// Read in field 1 of the private channel which is a counter  
// long count = ThingSpeak.readLongField(counterChannelNumber, counterFieldNumber, myCounterReadAPIKey);  

  // Check the status of the read operation to see if it was successful
 //statusCode = ThingSpeak.getLastReadStatus();
 if(statusCode == 200){
  // Serial.println("Counter: " + String(count));
 }
 else{
 //  Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
 }
 
 //delay(15000); // No need to read the counter too often.*/
 
}
