# Working Procedure

## Step 1: System Initialization

1. ESP32 powers on.
2. LCD displays "Starting...".
3. ESP32 connects to WiFi.
4. Firebase connection is established.
5. RFID module is initialized.
6. LCD displays "Scan Student".

---

## Step 2: Student Authentication

1. Student places RFID card near RC522.
2. RFID UID is read.
3. UID is searched in Firebase Database.

### If Student Exists

- Student name is retrieved.
- Department is retrieved.
- Information displayed on LCD.
- LCD prompts "Scan Book".

### If Student Does Not Exist

- LCD displays "Not Registered".
- System returns to idle state.

---

## Step 3: Book Identification

1. Book RFID tag is scanned.
2. Book UID is read.
3. Book information is fetched from Firebase.

### If Book Exists

- Book title displayed.
- Copy number displayed.

### If Book Does Not Exist

- LCD displays "Invalid Book".
- System resets.

---

## Step 4: Issue Operation

Condition:

Book Available = TRUE

Process:

1. Available copies reduced by 1.
2. Book status updated to unavailable.
3. Student ID stored under issued records.
4. Firebase database updated.
5. Google Sheet updated.
6. LCD displays issue confirmation.

---

## Step 5: Return Operation

Condition:

Book already issued to same student.

Process:

1. Available copies increased by 1.
2. Book status changed to available.
3. Issued record removed.
4. Firebase updated.
5. Google Sheet updated.
6. LCD displays return confirmation.

---

## Step 6: Logging

Every transaction contains:

- Student Name
- Book Name
- Action (Issue/Return)
- Remaining Copies
- Timestamp

Stored automatically in Google Sheets.

---

## Step 7: Reset

System clears temporary data and waits for next student scan.
