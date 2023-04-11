#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>
#define WIFI_SSID "tzu"
#define WIFI_PASSWORD "0903015157"
#define MQTT_SERVER "192.168.50.114"
#define MQTT_PORT 1883
#define MQTT_USERNAME "ee"
#define MQTT_PASSWORD "123456ncnuee"
#define MQTT_TOPIC "homeassistant/sensor/bme280"
#define MQTT_TOPIC_1 "homeassistant/sensor/soil_moisture"
#define MQTT_TOPIC_2 "homeassistant/sensor/bh1750"
#define MQTT_SWITCH_TOPIC "homeassistant/switch/led"
#define MQTT_SWITCH_TOPIC_1 "homeassistant/switch/fan"
#define MQTT_SWITCH_TOPIC_2 "homeassistant/switch/pump"
long lastMsg = 0;
char msg[50];
int value = 0;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

Adafruit_BME280 bme;
BH1750 bh;
int soilMoisturePin = A0;
int soilMoistureValue = 0;
int switchPin_led = 2;
int switchPin_fan= 12;
int switchPin_pump= 13;
void setup() {
  Serial.begin(115200);
  pinMode(switchPin_led, OUTPUT);
  digitalWrite(switchPin_led, LOW);
  pinMode(switchPin_fan, OUTPUT);
  digitalWrite(switchPin_fan, LOW);
  pinMode(switchPin_pump, OUTPUT);
  digitalWrite(switchPin_pump, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  while(!mqttClient.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if(mqttClient.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT broker");
      mqttClient.subscribe(MQTT_SWITCH_TOPIC);
      mqttClient.subscribe(MQTT_SWITCH_TOPIC_1);
      mqttClient.subscribe(MQTT_SWITCH_TOPIC_2);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.println(mqttClient.state());
      delay(1000);
    }
  }

  Serial.println("Connected to WiFi and MQTT broker");

}

void loop() {
  bme.begin(0x76); // I2C Address
  bh.begin();
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;
  float light = bh.readLightLevel();
  soilMoistureValue = ((analogRead(soilMoisturePin))/1023)*100;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Soil moisture: ");
  Serial.print(soilMoistureValue);
  Serial.println(" %");

  Serial.print("Light: ");
  Serial.print(light);
  Serial.println(" lx");
  if (mqttClient.connected()) {
    String temperatureString = String(temperature);
    String humidityString = String(humidity);
    String soilmoistureString = String(soilMoistureValue);
    String lightString = String(light);

    mqttClient.publish(MQTT_TOPIC "/temperature", temperatureString.c_str());
    mqttClient.publish(MQTT_TOPIC "/humidity", humidityString.c_str());
    mqttClient.publish(MQTT_TOPIC_1 "/moisture", soilmoistureString.c_str());
    mqttClient.publish(MQTT_TOPIC_2 "/light", lightString.c_str());
    Serial.println("Sensor data published to MQTT broker");
    delay(1000);
    mqttReconnect();
  }
  mqttClient.loop();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  // 設定 Relay 開關控制的訂閱 Topic 名稱
  if (strcmp(topic, MQTT_SWITCH_TOPIC) == 0) {
    if ((char)payload[0] == '1') {
      digitalWrite(switchPin_led, HIGH);      
      Serial.println("Switch Turn On");
    }
      else if ((char)payload[0] == '0') {
      digitalWrite(switchPin_led, LOW);     
      Serial.println("Switch Turn Off");
    }}
  if (strcmp(topic, MQTT_SWITCH_TOPIC_1) == 0) {
     if ((char)payload[0] == '2') {
      digitalWrite(switchPin_fan, LOW);     
      Serial.println("Switch Turn Off");
    }
       else if ((char)payload[0] == '3') {
      digitalWrite(switchPin_fan, HIGH);     
      Serial.println("Switch Turn On");
    }
 }
   if (strcmp(topic, MQTT_SWITCH_TOPIC_2) == 0) {
     if ((char)payload[0] == '4') {
      digitalWrite(switchPin_pump, LOW);     
      Serial.println("Switch Turn Off");
    }
       else if ((char)payload[0] == '5') {
      digitalWrite(switchPin_pump, HIGH);     
      Serial.println("Switch Turn On");
    }
 }
}

void mqttReconnect() {
  while (!mqttClient.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if(mqttClient.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT broker");
      mqttClient.subscribe(MQTT_SWITCH_TOPIC);
      mqttClient.subscribe(MQTT_SWITCH_TOPIC_1);
      mqttClient.subscribe(MQTT_SWITCH_TOPIC_2);
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.println(mqttClient.state());
      delay(1000);
    }
  }
}
