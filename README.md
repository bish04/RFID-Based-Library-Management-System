# RFID Smart Library Management System

## Overview

The RFID Smart Library Management System is an IoT-based solution designed to automate library operations using RFID technology and ESP32. The system enables automatic book issuing and returning, reducing manual work and improving efficiency.

## Features

* RFID-based student and book identification
* Automated issue and return process
* Real-time database updates using Firebase
* Transaction logging using Google Sheets
* LCD for user interaction
* Wi-Fi enabled ESP32 controller

## Hardware Components

* ESP32 Microcontroller
* MFRC522 RFID Reader
* RFID Tags/Cards
* 16x2 LCD Display (I2C)

## Software Components

* Arduino IDE
* Firebase Realtime Database
* Google Apps Script
* Google Sheets

## Working Principle

1. Student RFID card is scanned.
2. Book RFID tag is scanned.
3. ESP32 verifies details from Firebase.
4. Book is issued or returned automatically.
5. Transaction data is stored in Firebase and Google Sheets.

## Team Members

* Bishal Sutradhar
* Parthib Biswas
* Ngawang Damchoe Sherpa

## Future Scope

* Mobile application integration
* Anti-theft RFID gate system
* Automatic fine calculation
* Cloud-based large library deployment
