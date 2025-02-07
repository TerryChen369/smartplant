# ESP8266 IoT Sensor with MQTT

## 📌 Introduction
This project is an IoT-based environmental monitoring and control system using an ESP8266 microcontroller. It integrates multiple sensors, including:
- **BME280** for temperature, humidity, and pressure monitoring
- **BH1750** for light intensity measurement
- **Soil moisture sensor** for monitoring soil moisture levels

Additionally, it supports MQTT communication for real-time data transmission and remote control of:
- **LED light**
- **Fan**
- **Water pump**

## 🛠️ Features
- 📡 **WiFi Connectivity:** Uses ESP8266 to connect to the MQTT broker.
- 🔗 **MQTT Protocol:** Sends sensor data and receives control commands.
- 📊 **Real-time Monitoring:** Publishes temperature, humidity, pressure, light, and soil moisture values.
- 🔌 **Remote Device Control:** Allows remote ON/OFF control for LED, fan, and pump.

## 🏗️ Hardware Requirements
- ESP8266 (e.g., NodeMCU)
- BME280 sensor
- BH1750 light sensor
- Soil moisture sensor
- Relay module for LED, fan, and water pump
- MQTT Broker (e.g., Mosquitto)

## 🔧 Setup Instructions
1. **Install Arduino IDE** and add ESP8266 board support.
2. **Install Required Libraries**:
Adafruit BME280 Library Adafruit Unified Sensor BH1750 PubSubClient
3. **Modify WiFi and MQTT Credentials**:
Update the following constants in `ESP8266_IoT_MQTT.ino`:
```cpp
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define MQTT_SERVER "your_mqtt_broker_ip"
#define MQTT_USERNAME "your_mqtt_username"
#define MQTT_PASSWORD "your_mqtt_password"
Upload Code: Compile and upload the sketch to your ESP8266 board.
Run MQTT Broker: If using Mosquitto, start the broker on your server.
Monitor Data: Use MQTT tools (like MQTT Explorer or Home Assistant) to observe sensor data.
📡 MQTT Topics
Sensor / Actuator	MQTT Topic
Temperature	homeassistant/sensor/bme280/temperature
Humidity	homeassistant/sensor/bme280/humidity
Soil Moisture	homeassistant/sensor/soil_moisture/moisture
Light Intensity	homeassistant/sensor/bh1750/light
LED Control	homeassistant/switch/led
Fan Control	homeassistant/switch/fan
Pump Control	homeassistant/switch/pump
📝 License
This project is open-source and distributed under the MIT License.

📩 Contact
For any questions or contributions, feel free to open an issue or submit a pull request!
