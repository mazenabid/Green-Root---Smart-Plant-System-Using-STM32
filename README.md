# GreenRoot: Automated Plant Care System

Welcome to the GreenRoot project, where I have created a smart plant system using the STM32 and Cube IDE as well as using the ESP32 to control the morot from your phone or laptop over theinternet. GreenRoot revolutionizes plant care at home by automating watering based on customizable soil moisture levels, providing real-time data on soil moisture and temperature data. This system allows you to make informed decisions for your plants, moving beyond guesswork to precision care. I will outlines the setup process for GreenRoot and explores the technology and architecture behind this project.

## Project Overview

I've recently dived into the realm of IoT technology, drawn by my interest in programming for embedded systems and a growing fascination with web technologies acquired over the past year. IoT being popular in controlling things over WiFi naturally caught my attention.

Not long ago, I wrapped up a project and called it "GreenRoot." It offers users the ability to monitor their plants' health. Additionally, it automatically waters them based on customizable settings. Users can easily control their water pump from the Blynk App or web dashboard. This web application is responsive, adapting to various devices and allows for more than just water pump control as you can add more sensors and modes for ease of use.

Creating GreenRoot involved designing schematics, setting up Blynk, and developing the system's firmware. This comprehensive project allowed me to engage with every crucial component of a complete STM Project since there's no HAL usage throughout this project.

I prioritized using affordable and accessible components for GreenRoot to ensure that others could easily replicate and customize it. For those interested, a detailed parts list and a step-by-step guide for installing GreenRoot at home can be found here.

## Video Demonstration
For a more detailed look at the game, you can watch the video [here]((https://youtu.be/izzzgu7p95I?si=vIytle1yohXQ31FL))

[![Watch the video](http://img.youtube.com/vi/izzzgu7p95I/0.jpg)](https://youtu.be/izzzgu7p95I?si=vIytle1yohXQ31FL)

### Key Features

- **Automated Watering:** Customizable settings for soil moisture, ensuring plants receive the right amount of water.
- **Real-time Monitoring:** Track soil moisture and temperature data to make informed care decisions.
- **Remote Control:** Manage your plant care system via the Blynk App or web dashboard.
- **Expandability:** Add more sensors and functionalities as needed.

### Technologies and Tools

- **Microcontrollers:** STM32 and ESP8266/ESP32 for control and connectivity.
- **Development Environments:** Cube IDE for STM32; Arduino IDE for ESP32.
- **Application:** Blynk platform for remote monitoring and control.

## Getting Started

To replicate and customize GreenRoot for your home, we've ensured the use of affordable and readily available components. A complete guide, including a detailed parts list and step-by-step instructions, is available to help you set up GreenRoot.

## Components List

For your convenience, here are direct links to purchase the components needed for the GreenRoot project from Amazon:

- **LCD Display**:
  - [Buy on Amazon](https://www.amazon.ca/dp/B01GPUMP9C?psc=1&ref=ppx_yo2ov_dt_b_product_details)

- **Sensors** (Note: The link provided is the same as the LCD. Please verify this as it might be an error):
  - [Buy on Amazon](https://www.amazon.ca/dp/B01GPUMP9C?psc=1&ref=ppx_yo2ov_dt_b_product_details)

- **ESP32 Module**:
  - [Buy on Amazon](https://www.amazon.ca/dp/B08HJYT6YV?psc=1&ref=ppx_yo2ov_dt_b_product_details)

- **Motor & Tube**:
  - [Buy on Amazon](https://www.amazon.ca/dp/B0BK9MV2C3?psc=1&ref=ppx_yo2ov_dt_b_product_details)

- **Breadboard & Jumper Wires**:
  - [Buy on Amazon](https://www.amazon.ca/HUAREW-Breadboard-Jumper-Include-Points/dp/B09VKYLYN7/ref=sr_1_14?crid=19L9HJDYBJIQJ&dib=eyJ2IjoiMSJ9.H4rd-Nqrk5O7C3Vc89bXrED930cfRDp0lNKsvaNjPsjwuULkQ6Pl6xuib1AkxvsUKNnBOoJl6tsEHkEDKSvt_f6mRWmwLuHEuEBLMym9-6MNUM0TmqO20RnpeVQ1-bRlNcs9VKCYu3a-hENBfqBg-7zQ919eh29LnVSc-A5htaFFZSoKxcHbGkXPDrrqHntRakCkipJb1SlB4UweVYTMfjsIMdVYr0E99RVkViU8YLefsvfKD9cfgLNOVgCrurNdCQNEWA_GyM_umgPn1w6MQWmwoOVV1xq79Vjo8r6nxD0.BZAVayMDBZY-p_ETbJr-V15tMCI1Njdgs2FKPtKHDU8&dib_tag=se&keywords=jumper+wires+and+breadboard&qid=1712036258&s=hi&sprefix=jumper+wires+and+breadboard%2Ctools%2C97&sr=1-14)

Please ensure to verify each link and product before purchase to make sure they meet your project requirements.

### System Components

#### STM32 Part

- Moisture Sensor
- Temperature Sensor
- 16x2 LCD Screen
- Relay
- DC Motor
- Tube
- Powerbank
- Charging Cable
- Jumper Wires
- Breadboard

**Software:** Cube IDE

#### ESP32 Part

- ESP32 Module
- DC Motor
- Powerbank
- Charging Cable
- Jumper Wires
- Breadboard

**Software:** Arduino IDE

## Project Schematics

(Detailed schematics will provide visual guidance for assembling both the STM32 and ESP32 components of the system, ensuring a smooth setup process.)

### STM32 Schematics

(Schematic diagrams for the STM32 part, illustrating connections between the microcontroller, sensors, display, and actuators.)

### ESP32 Schematics

(Schematic diagrams for the ESP32 part, showing how to connect the module for WiFi connectivity and control via Blynk.)


GreenRoot is more than a project; it's a step towards smarter, more efficient plant care. Dive into the documentation, harness the power of IoT for your greenery, and bring the precision of technology to your plant care routine.
