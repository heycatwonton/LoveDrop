#include <Adafruit_Thermal.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <FirebaseArduino.h>
#include <FirebaseObject.h>

#define FIREBASE_HOST "notedrop-379bf.firebaseio.com"
#define FIREBASE_AUTH "UJkgig4c1uvD431PBW2e5aBPWDnpFQXo4KkBPIBR"
#define WIFI_SSID "Schrodingers Cat"
#define WIFI_PASSWORD "fence1935cactus"
#define TX_PIN 4 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void setup() {
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  delay(10);
  Serial.println('\n');
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); Serial.println(" ...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setBool("arduinoStatus", true);
}
void loop() {
  //    FirebaseObject fireObj = Firebase.get("messages");
  const ArduinoJson::JsonObject& object = Firebase.get("messages").getJsonVariant().asObject();
  String key;
  String message;
  String date;
  String sender;
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  } else {
    for (ArduinoJson::Internals::ListConstIterator<JsonPair> jpi = object.begin(); jpi != object.end(); ++jpi) {
      JsonPair jp = *jpi;
      key = jp.key;
      JsonObject& keyObj = jp.value.asObject();
      message = keyObj["message"].as<String>();
      date = keyObj["date"].as<String>();
      sender = keyObj["name"].as<String>();
      Serial.println("Key: " + key + ", Message: " + message + ", Name: " + sender + ", Date: " + date );
      printer.println("Sender: " + sender);
      delay(10);
      printer.println("Date: ");
      delay(10);
      printer.println(date);
      delay(10);
      printer.println("Message: ");
      delay(10);
      printer.println(message);
      delay(100);
    }
    Firebase.remove("messages/" + key);
  }
  delay(1000);
}
//void print(String date, String sender, String message) {
//  printer.println(date);
//  printer.print("From");
//  printer.println(sender);
//  printer.println(message);
//}
