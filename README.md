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
