RFID-Based Smart Library Management System

Project Overview

The RFID-Based Smart Library Management System is an IoT-enabled library automation solution developed using ESP32, MFRC522 RFID Reader, Firebase Realtime Database, Google Sheets, and a 16×2 I2C LCD Display. The system simplifies the process of issuing and returning library books by using RFID technology for student and book identification.

The project eliminates manual record keeping by automatically updating book availability, maintaining transaction records in Firebase, and logging all activities to Google Sheets for administrative monitoring.

---

Objectives

- Automate book issue and return operations.
- Reduce manual errors in library record management.
- Maintain real-time inventory of books.
- Provide a user-friendly interface through an LCD display.
- Store and manage records using cloud databases.
- Generate transaction logs automatically using Google Sheets.

---

Features

- RFID-based student authentication.
- RFID-based book identification.
- Automatic book issue and return functionality.
- Real-time synchronization with Firebase Realtime Database.
- Automatic transaction logging to Google Sheets.
- LCD display for user interaction and status updates.
- Wi-Fi connectivity using ESP32.
- Inventory management with available and total copy tracking.

---

Hardware Components

Component| Quantity
ESP32 Development Board| 1
MFRC522 RFID Reader| 1
RFID Cards/Tags| Multiple
16×2 I2C LCD Display| 1
Breadboard| 1
Jumper Wires| As Required
USB Cable| 1

---

Software Requirements

- Arduino IDE
- ESP32 Board Package
- Firebase Realtime Database
- Google Apps Script
- Google Sheets
- GitHub

---

Libraries Used

The following libraries are required in Arduino IDE:

- WiFi.h
- SPI.h
- MFRC522.h
- Firebase_ESP_Client.h
- Wire.h
- LiquidCrystal_I2C.h
- HTTPClient.h
- WiFiClientSecure.h

---

System Architecture

The system follows the workflow below:

1. Student scans RFID card.
2. ESP32 verifies student information from Firebase.
3. Student details are displayed on LCD.
4. Student scans a book RFID tag.
5. ESP32 checks book availability.
6. Book is issued or returned based on current status.
7. Firebase database is updated.
8. Transaction details are sent to Google Sheets.
9. LCD displays operation status.

---

Circuit Connections

MFRC522 RFID Reader to ESP32

MFRC522 Pin| ESP32 Pin
SDA (SS)| GPIO 5
SCK| GPIO 18
MOSI| GPIO 23
MISO| GPIO 19
RST| GPIO 4
GND| GND
3.3V| 3.3V

I2C LCD to ESP32

LCD Pin| ESP32 Pin
SDA| GPIO 21
SCL| GPIO 22
VCC| 5V
GND| GND

---

Firebase Database Structure

{
  "Students": {
    "StudentID": {
      "name": "Student Name",
      "department": "Department Name"
    }
  },

  "Books": {
    "BookID": {
      "title": "Book Title",
      "copyNo": 1,
      "available": true,
      "inventoryKey": "Book Title"
    }
  },

  "Inventory": {
    "Book Title": {
      "availableCopies": 5,
      "totalCopies": 10
    }
  },

  "Issued": {
    "BookID": {
      "student": "StudentID"
    }
  }
}

---

Working Principle

Student Verification

When a student RFID card is scanned, the ESP32 retrieves the corresponding student information from Firebase. If the student exists in the database, the name and department are displayed on the LCD.

Book Issue

If the scanned book is available:

- Available copy count decreases by one.
- Book status changes to unavailable.
- Student ID is stored in the Issued section.
- Transaction is logged in Google Sheets.
- LCD displays successful issue confirmation.

Book Return

If the same student scans an already issued book:

- Available copy count increases by one.
- Book status changes to available.
- Issued record is removed.
- Return transaction is logged.
- LCD displays successful return confirmation.

---

Google Sheets Integration

Google Apps Script acts as a bridge between ESP32 and Google Sheets.

Each transaction records:

- Student Name
- Book Name
- Action (Issued/Returned)
- Remaining Copies
- Timestamp

This allows administrators to monitor all library activities in real time.

---

Installation Procedure

Step 1: Configure Firebase

1. Create a Firebase project.
2. Enable Realtime Database.
3. Obtain:
   - API Key
   - Database URL
4. Add student and book records.

Step 2: Configure Google Sheets

1. Create a Google Sheet.
2. Open Extensions → Apps Script.
3. Paste the provided script.
4. Deploy as Web App.
5. Copy the generated Web App URL.

Step 3: Configure Arduino Code

Replace the following placeholders:

#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define API_KEY "YOUR_FIREBASE_API_KEY"
#define DATABASE_URL "YOUR_FIREBASE_DATABASE_URL"

Update:

const char* sheetURL = "YOUR_GOOGLE_SCRIPT_WEBAPP_URL";

Step 4: Upload Code

1. Select ESP32 board in Arduino IDE.
2. Connect ESP32 via USB.
3. Compile the project.
4. Upload the code.

---

Results

The developed system successfully:

- Identifies students using RFID cards.
- Identifies books using RFID tags.
- Performs automatic issue and return operations.
- Updates Firebase database in real time.
- Maintains inventory records accurately.
- Logs all transactions in Google Sheets.
- Provides user feedback through LCD display.

---

Future Enhancements

- Due date management.
- Fine calculation system.
- Mobile application integration.
- Email and SMS notifications.
- QR code-based identification.
- Admin dashboard for analytics.
- Book search functionality.
- Attendance tracking integration.

---

Advantages

- Reduces manual effort.
- Improves transaction accuracy.
- Real-time cloud synchronization.
- Easy scalability.
- Low-cost implementation.
- User-friendly operation.

---

Applications

- School Libraries
- College Libraries
- University Libraries
- Book Banks
- Digital Resource Centers

---

Conclusion

The RFID-Based Smart Library Management System demonstrates the effective use of IoT technologies for automating library operations. By integrating ESP32, RFID technology, Firebase Realtime Database, and Google Sheets, the system provides a reliable, efficient, and scalable solution for managing book issue and return activities. The project significantly reduces manual work while ensuring accurate record keeping and real-time monitoring.

---

Author

Name: Bishal Sutradhar

Institution: National Institute of Technology Sikkim

Department: Electronics and Communication Engineering

Year: 2026
