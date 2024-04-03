// Thingspeak
String myAPIkey = "KRZTAUOSSZJQRTO1";  // Status Channel id: 2065061
#include <SoftwareSerial.h>
#include <DHT.h>
SoftwareSerial ESP8266(10, 11);  // Rx, Tx

/* DHT SENSOR SETUP */
#define DHTTYPE DHT11
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE, 11);
float humidity, temp_f;  // Values read from DHT sensor
int duration, cm;        // Values from ultrasonic sensor

// for ultra sonic sensor
int ECHO = 7;
int TRIG = 8;

// for soil moisture, connect AO (analog output) pin with A0 of arduino board
int moisture_signal = A0;
int moisture;

// Variables to be used with timers
long writingTimer = 17;  // ==>Define Sample time in seconds to send
long startTime = 0;
long waitTime = 0;

// Variables to be used with Actuators
boolean relay1_st = false;
boolean relay2_st = false;
unsigned char check_connection = 0;
unsigned char times_check = 0;
boolean error;

void setup() {
  Serial.begin(9600);
  ESP8266.begin(9600);
  // Comunicacao com Modulo WiFi
  dht.begin();
  startTime = millis();  // starting the "program clock"
  ESP8266.println("AT+RST");
  delay(2000);
  Serial.println("Connecting to Wifi");
  while (check_connection == 0) {
    Serial.print(".");
    ESP8266.print("AT+CWJAP=\"JioFiber-RJ2UZ\",\"rajkumar123\"\r\n");  // Wi-Fi SSID and password
    ESP8266.setTimeout(5000);
    if (ESP8266.find("WIFI CONNECTED\r\n") == 1) {
      Serial.println("WIFI CONNECTED");
      break;
    }
    times_check++;
    if (times_check > 3) {
      times_check = 0;
      Serial.println("Trying to Reconnect..");
    }
  }
}


void loop() {
  waitTime = millis() - startTime;
  if (waitTime > (writingTimer * 1000)) {
    readSensors();
    writeThingSpeak();
    startTime = millis();
  }
}


/********* Read Sensors value *********/
void readSensors(void) {
  temp_f = dht.readTemperature(); 
  humidity = dht.readHumidity();

  // measuring duration of each pulse, Ultra sonic sensor
  duration = pulseIn(ECHO, HIGH);
  // converting duration to cm
  cm = duration / 29 / 2;

  // for soil mositure
  moisture = analogRead(moisture_signal);
}



void writeThingSpeak(void) {
  startThingSpeakCmd();
  // preparacao da string GET
  String getStr = "GET /update?api_key=";
  getStr += myAPIkey;
  getStr += "&field1=";
  getStr += String(temp_f);
  getStr += "&field2=";
  getStr += String(humidity);
  getStr += "&field3=";
  getStr += String(cm);
  getStr += "&field4=";
  getStr += String(moisture);
  getStr += "\r\n\r\n";
  GetThingspeakcmd(getStr);
}


/********** start ThingSpeak **********/
void startThingSpeakCmd(void) {
  ESP8266.flush();
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "api.thingspeak.com";  //api.thingspeak.com IP address - 184.106.153.149
  cmd += "\",80";
  ESP8266.println(cmd);
  Serial.print("Start Commands: ");
  Serial.println(cmd);
  if (ESP8266.find("Error")) {
    Serial.println("AT+CIPSTART error");
    return;
  }
}


/********** GET cmd to ThingSpeak **********/
String GetThingspeakcmd(String getStr) {
  String cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ESP8266.println(cmd);
  Serial.println(cmd);
  if (ESP8266.find(">")) {
    ESP8266.print(getStr);
    Serial.println(getStr);
    delay(500);
    String messageBody = "";
    while (ESP8266.available()) {
      String line = ESP8266.readStringUntil('\n');
      if (line.length() == 1) {  //actual content starts after empty line (that has length (?)
        messageBody = ESP8266.readStringUntil('\n');
      }
    }
    Serial.print("MessageBody recieved: ");
    Serial.println(messageBody);
    return messageBody;
  } else {
    ESP8266.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }
}