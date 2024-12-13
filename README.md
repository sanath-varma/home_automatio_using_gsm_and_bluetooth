# Home Automation System with GSM and Bluetooth

## Overview
This project is a home automation system built with Arduino, GSM, Bluetooth, and various sensors. It provides functionalities such as controlling lights, fans, motors, and other home appliances. The system is designed to work with multiple sensors, including a gas sensor, temperature sensor (DHT11), IR sensor, LDR (Light Dependent Resistor), and more. Users can control appliances via Bluetooth or SMS, and receive real-time alerts in case of emergencies.

## Features
- **Bluetooth Control**: Control lights, fans, and motors via Bluetooth commands.
- **GSM Control**: Send commands via SMS to control appliances (e.g., turn on/off light, fan, motor).
- **Temperature-based Fan Control**: Fan speed adjusts based on room temperature (using DHT11).
- **Gas Leak Detection**: Alerts users if gas leakage is detected.
- **Water Tank Monitoring**: Receive notifications when the water tank is full.
- **Door Open Detection**: Alerts when the door is open.
- **Motion Detection**: A PIR sensor triggers alerts if motion is detected.
- **Automatic Light Control**: LED light brightness adjusts based on ambient light conditions using an LDR sensor.

## Components Used
- **Arduino Uno**: Main controller board.
- **DHT11**: Temperature and humidity sensor.
- **GSM Module (SIM800)**: For SMS communication.
- **Bluetooth Module (HC-05)**: For Bluetooth communication.
- **Relay**: For controlling appliances (e.g., light, fan, motor).
- **PIR Sensor**: Motion detection sensor.
- **LDR Sensor**: Light-dependent resistor for ambient light detection.
- **Gas Sensor (MQ-2)**: Detects gas leakage.
- **IR Sensors**: For detecting presence in the room and monitoring the water tank.
- **Buzzer**: For alerting the user to certain events (e.g., door open, gas leak).
- **Push Button**: For manual control.

## IMAGES
You can refer to the images provided in the project folder for connecting the components to the Arduino board.

## Software Requirements
- **Arduino IDE**: For compiling and uploading the code to the Arduino.
- **Bluetooth App**: Any Bluetooth terminal app to communicate with the Bluetooth module.
- **SIM Card**: For GSM module communication (with SMS capabilities).

## Installation
1. Install the Arduino IDE on your computer.
2. Open the provided project file in the Arduino IDE.
3. Connect your Arduino board to the computer via USB.
4. Select the correct board and port in the Arduino IDE.
5. Upload the code to the Arduino board.
6. Connect the components as per the circuit diagram.
7. Power the system using an appropriate power source.

## How to Use
### Bluetooth Control:
- Open a Bluetooth terminal app on your phone.
- Pair with the HC-05 Bluetooth module.
- Send commands such as "light on", "fan on", "motor on", etc., to control the devices.

### GSM Control:
- Send SMS commands to the GSM module.
  - Example commands:
    - `@on#`: Turn on the light.
    - `@off#`: Turn off the light.
    - `@fan on#`: Turn on the fan.
    - `@fan off#`: Turn off the fan.

### Sensor Alerts:
- The system will automatically detect changes (e.g., gas leak, door open, water tank full) and send alerts via SMS or activate the buzzer.

### Automatic Temperature-based Fan Control:
- The fan speed will adjust based on the temperature detected by the DHT11 sensor.

### Light Control:
- The system will adjust the light based on the ambient light detected by the LDR sensor.

## Functions
- **handleBluetooth()**: Handles Bluetooth communication and controls devices based on commands.
- **smssending()**: Sends an SMS using the GSM module.
- **handleGasSensor()**: Monitors the gas sensor for gas leaks and sends alerts.
- **handleIRSensor()**: Monitors room occupancy using the IR sensor.
- **handleWaterTankIRSensor()**: Monitors the water tank status using an IR sensor.
- **handleDoorIRSensor()**: Monitors the door status using an IR sensor.
- **fanStatus()**: Controls the fan speed based on the temperature.
- **toggle()**: Toggles the light on/off and sends SMS notifications.
- **buzzeron(), buzzeroff()**: Controls the buzzer for alerting.

## Troubleshooting
- Ensure the GSM module has a valid SIM card with sufficient balance for SMS operations.
- Make sure the Bluetooth module is correctly paired with your phone.
- Check the wiring and connections for all sensors and actuators.

## License
This project is open-source. Feel free to modify and use it according to your needs. Attribution is appreciated.

## Author
This project was developed by **AAKIREDDY SANATH VARMA**.
