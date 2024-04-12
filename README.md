# GreenRoot: Automated Plant Care System

Welcome to the GreenRoot project, where the aim is to revolutionizes plant care at home by automating watering based on customizable soil moisture levels, providing real-time data on soil moisture and temperature data. This system allows you to make informed decisions for your plants, moving beyond guesswork to precision care. I outline the setup process for GreenRoot and explore the technology and architecture behind its construction.

## Project Overview

I have recently dived into the realm of IoT technology, drawn by my interest in programming for embedded systems and a growing fascination with web technologies acquired over the past year. IoT development boards such as ESP32 being popular in controlling things over WiFi naturally caught my attention.

Not too long ago, I wrapped up a project and called it "GreenRoot." It offers users the ability to monitor their plants' health. Additionally, it automatically waters them based on customizable settings. Users can easily control their water pump from the Blynk App or web dashboard. Using Blynk is responsive, adapts various devices and allows for more than just water pump control as you can add more sensors and modes for ease of use.

Creating GreenRoot involved designing schematics, setting up Blynk, and developing the system's firmware. This comprehensive project allowed me to engage with every crucial component of a complete STM Project since there's no HAL usage throughout this project.

## Video Demonstration
For a demo, you can watch the video [here]((https://youtu.be/izzzgu7p95I?si=vIytle1yohXQ31FL))

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

I prioritized using affordable and accessible components for GreenRoot to ensure that others could easily replicate and customize it. For those interested, a detailed parts list and a step-by-step guide for installing GreenRoot at home can be found here.

## Components List

For your convenience, here are direct links to purchase the components needed for the GreenRoot project from Amazon:

- **LCD Display**:
  - [Buy on Amazon](https://www.amazon.ca/dp/B01GPUMP9C?psc=1&ref=ppx_yo2ov_dt_b_product_details)

- **Sensors**:
  - [Buy on Amazon](https://www.amazon.ca/keyestudio-Tutorial-Programming-Learning-Education/dp/B016KIXSMM/ref=asc_df_B016KIXSMM/?tag=googlemobshop-20&linkCode=df0&hvadid=293021489696&hvpos=&hvnetw=g&hvrand=17743198096267389233&hvpone=&hvptwo=&hvqmt=&hvdev=m&hvdvcmdl=&hvlocint=&hvlocphy=1002787&hvtargid=pla-639829366075&psc=1&mcid=1df5754eb72e39fd94f963abe7d3346a)

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
- 20x4 LCD Screen
- Relay
- DC Motor
- Tube
- Powerbank
- Charging Cable
- Jumper Wires
- Breadboard
- Push Button

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

Detailed schematics will provide visual guidance for assembling both the STM32 and ESP32 components of the system, ensuring a smooth setup process.

### STM32 Schematics
<img width="722" alt="Screenshot 2024-04-01 at 11 41 35 PM" src="https://github.com/mazenabid/GreenRoot/assets/87061766/2ef067ff-0a36-4515-b822-b1f228b87d2d">

### ESP32 Schematics
<img width="1016" alt="Screenshot 2024-04-01 at 11 41 04 PM" src="https://github.com/mazenabid/GreenRoot/assets/87061766/ba4b4a68-14cb-4921-b833-5ff3d5e37f6a">

&nbsp;
&nbsp;

# Setting up STM32CubeIDE for Low Level/Bare Metal Coding

This guide is crucial for preparing your development environment to work with the STM32 microcontroller at a low level, enabling precise control over the hardware for projects like GreenRoot. Follow these steps carefully to ensure your environment is correctly set up.

## Initial Setup in STM32CubeIDE

### 1. Prepare Chip Headers

Download the "Chip Headers" folder from the repository and save it in a location that's easily accessible.

### 2. Creating a New Project

- Open STM32CubeIDE and log in to your STM account.
- Go to `File > New > STM32 Project`.
- In the Commercial Part Name field, enter your board's name. For GreenRoot, it's `Nucleo STM32F103RBT6`.
- Opt to create an empty project to start with a clean slate for bare metal programming.


### 3. Configuring Project Properties

- Double-click your project in the Project Explorer to open its properties.
- Navigate to `C/C++ General > Paths and Symbols`.
- Under the `Includes` tab, click `Add` to include the directory of your chip headers.
<img width="398" alt="Screenshot 2024-04-02 at 12 01 47 AM" src="https://github.com/mazenabid/GreenRoot/assets/87061766/52602a31-5b9b-412b-afb5-4cacdeb8148f">
<img width="715" alt="Screenshot 2024-04-02 at 12 06 04 AM" src="https://github.com/mazenabid/GreenRoot/assets/87061766/e3bc44e2-bb8a-4458-8e93-27d37eb46836">

### 4. Adding Include Directories

- Click on `Add > File System` and navigate to the previously saved "Chip Headers" folder.
- Go to `CMSIS > Device > ST > STM32F1xx` and select the `Include` folder. Click `Open`.
- Repeat the process for the CMSIS `Include` folder by navigating to `CMSIS` and then `Include`, and click `Open`.
<img width="979" alt="Screenshot 2024-04-02 at 12 10 35 AM" src="https://github.com/mazenabid/GreenRoot/assets/87061766/0d654fa2-cc73-4074-a503-269824b0492e">

- You should End up with this:
<img width="834" alt="Screenshot 2024-04-02 at 12 14 46 AM" src="https://github.com/mazenabid/GreenRoot/assets/87061766/a2f38381-c7de-4535-886d-44bb80ba6932">


### 5. Configuring Symbols

- In the project properties window, switch to the `Symbols` tab.
- Add any missing symbols from the screenshot that your project may require. This step is vital for informing the compiler about your STM32 chip's specific features.
<img width="834" alt="Screenshot 2024-04-02 at 2 35 07 PM" src="https://github.com/mazenabid/GreenRoot/assets/87061766/3f9c8288-6e23-442c-8373-0692072075ad">

### 6. Finalizing Setup
- Apply the changes and close the properties window. Your development environment is now ready for low-level programming.


# Summary
GreenRoot is more than a project; it's a step towards smarter, more efficient plant care. Please check out the documentations and bring the precision of technology to your plant care routine by trying it yourself at home!
