# Results

The developed RFID-Based Smart Library Management System was tested under multiple operating conditions.

---

## Test Case 1: Registered Student

Input:
Valid Student RFID

Output:
Student Name Displayed

Result:
PASS

---

## Test Case 2: Unregistered Student

Input:
Unknown RFID

Output:
Not Registered

Result:
PASS

---

## Test Case 3: Available Book

Input:
Valid Book RFID

Output:
Book Issued Successfully

Result:
PASS

---

## Test Case 4: Book Return

Input:
Previously Issued Book

Output:
Book Returned Successfully

Result:
PASS

---

## Test Case 5: Invalid Book

Input:
Unknown RFID

Output:
Invalid Book

Result:
PASS

---

## Test Case 6: Inventory Update

Expected:
Available Copies Updated

Observed:
Firebase Updated Correctly

Result:
PASS

---

## Test Case 7: Google Sheet Logging

Expected:
Transaction Logged

Observed:
Log Created Successfully

Result:
PASS

---

## Overall Result

The system successfully automates book issue and return operations while maintaining real-time inventory records and transaction history.
