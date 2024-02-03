#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Pin definitions for MQ135 and MQ6 sensors
const int MQ135_pin = A0;

// Pin definitions for LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int buz=5;
// Threshold values for air quality
const int MQ135_threshold = 200; // threshold for MQ135


const char* ssid = "your-ssid";
const char* password = "your-password";
const char* mqtt_server = "mqtt-server-address";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // Connect to Wi-Fi network with SSID and password
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void setup() {
   Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  // Initialize LCD
  lcd.begin(16, 2);
  
  // Initialize serial communication
  Serial.begin(9600);
  
}

void loop() {
  // Read sensor values
  int MQ135_value = analogRead(MQ135_pin);

  // Convert sensor values to PPM
  float MQ135_PPM = map(MQ135_value, 0, 1023, 0, 500); //mapping for MQ135
 

  // Display PPM values on LCD
  lcd.clear();
  lcd.print("MQ135: ");
  lcd.print(MQ135_PPM);
  
  client.loop();
  String message = "MQ135 PPM: " + String(MQ135_PPM);
  client.publish("air-quality-logs", message.c_str());


  // Check air quality thresholds and trigger alarms
  if (MQ135_PPM > MQ135_threshold) {
    digitalWrite(buz,HIGH);
    delay(1000);
 digitalWrite(buz,LOW);

    Serial.println("Air quality deteriorated! Alarm triggered.");

  }

  delay(1000); // Delay for stability
}
