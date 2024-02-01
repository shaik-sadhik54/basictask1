#include <ESP8266WiFi.h>  
 #include <WiFiClient.h>  
 #include <ThingSpeak.h>
 #include <LiquidCrystal_I2C.h>
 // pin define for LCD
 LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);

 // pin define for gas sensor
 int gas = A0; 
 // pin define buzzer
  int buz=D1;
  //Threshold values for air quality
  const int gas_tsd=200;
 const char* ssid = "SS ID";  
 const char* password = "password";  
 WiFiClient client;  
 unsigned long myChannelNumber = CHANNEL NUMBER;  
 const char * myWriteAPIKey = "ApI KEY";    
 void setup()  
 {
  // initilize LCD
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(gas,INPUT);  
  Serial.begin(115200);  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);
 }  
 void loop()   
 {  
  static boolean data_state = true;  
  int sensorValue = analogRead(gas);
 float a = sensorValue*(5.0/1023.0);
  if(a>1)
  {
       ThingSpeak.writeField(myChannelNumber,  2,a , myWriteAPIKey);
      Serial.println("uploaded");
     lcd.clear();
     lcd.print("Gas value");
     lcd.print(a);
      
  }
  else
  {
        
       ThingSpeak.writeField(myChannelNumber,  2,a , myWriteAPIKey);
      Serial.println("uploaded");
  }
  if(a >  gas_tsd)
  {
    digitalWrite(buz,HIGH);
    delay(1000);
 digitalWrite(buz,LOW);
  }
  Serial.println(a);
  delay(1000);
 
  delay(1000); // ThingSpeak will only accept updates every 1 second.  
 }
