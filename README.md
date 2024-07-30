# Plant Monitoring System

This project utilizes an Arduino Uno along with various sensors to monitor the health and conditions of plants. The system collects real-time data and displays it on a dashboard using the ThingSpeak IoT analytics platform.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Components](#components)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)

## Introduction

The Plant Monitoring System is designed to help monitor the health and growth conditions of plants. It uses an Arduino Uno and multiple sensors to measure various environmental parameters and sends this data to ThingSpeak for real-time monitoring and analysis.

## Features

- Real-time monitoring of plant health parameters
- Sensors used: DHT sensor (temperature and humidity), soil moisture sensor, ultrasonic sensor (water level), ESP8266 Wi-Fi module
- Data visualization on ThingSpeak dashboard

## Components

- Arduino Uno
- DHT11 or DHT22 sensor (temperature and humidity)
- Soil moisture sensor
- Ultrasonic sensor (water level)
- ESP8266 Wi-Fi module
- Breadboard and jumper wires

## Installation

1. Clone this repository to your local machine:

    ```bash
    git clone https://github.com/adarshmusa/Plant_Monitoring_System.git
    ```

2. Open the project in the Arduino IDE.

3. Install the necessary libraries:

    - [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)
    - [ESP8266WiFi library](https://github.com/esp8266/Arduino)
    - [ThingSpeak library](https://github.com/mathworks/thingspeak-arduino)

4. Upload the code to your Arduino Uno.

## Usage

1. Connect the sensors and the ESP8266 module to the Arduino Uno as per the circuit diagram.

2. Open the Arduino Serial Monitor to check if the sensors are working correctly.

3. Make sure your Wi-Fi credentials and ThingSpeak channel details are correctly entered in the code.

4. Once the Arduino is connected to Wi-Fi, data will be sent to the ThingSpeak channel and displayed on the dashboard.

## Contributing

Contributions are welcome! Please fork this repository and submit pull requests for any enhancements or bug fixes.
