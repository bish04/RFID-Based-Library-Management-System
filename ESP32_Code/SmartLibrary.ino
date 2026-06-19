#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>   

//============= WIFI =============
#define WIFI_SSID "YOUR_WIFI"
#define WIFI_PASSWORD "YOUR_PASSWORD"


//=========== FIREBASE ===========
#define API_KEY "YOUR_FIREBASE_API_KEY"

#define DATABASE_URL "YOUR_DATABASE_URL"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

//=========== GOOGLE SHEET ===========
const char* sheetURL = "YOUR SHEET URL";

// RFID
#define SS_PIN 5
#define RST_PIN 4
MFRC522 rfid(SS_PIN, RST_PIN);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables
String studentID="", studentName="", department="";
bool studentScanned=false;


//========= GOOGLE SHEET =========
void sendToSheet(String s, String b, String a, int r){

  WiFiClientSecure client;
  client.setInsecure();   

  HTTPClient http;

  http.begin(client, sheetURL);
  http.addHeader("Content-Type","application/json");
  http.addHeader("Connection","close"); 

  String json = "{\"s\":\""+s+"\",\"b\":\""+b+"\",\"a\":\""+a+"\",\"r\":"+String(r)+"}";

  int code = http.POST(json);

  Serial.print("Sheet HTTP: ");
  Serial.println(code);

  http.end();

  delay(150); 
}


//============= SETUP =============
void setup(){

  Serial.begin(115200);

  Wire.begin(21,22);
  lcd.init();
  lcd.backlight();

  lcd.print("Starting...");
  delay(800);

  // WiFi
  lcd.clear();
  lcd.print("Connecting WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while(WiFi.status()!=WL_CONNECTED){
    delay(300);
    Serial.print(".");
  }

  lcd.clear();
  lcd.print("WiFi OK");
  delay(800);

  // Firebase
  lcd.clear();
  lcd.print("Connecting DB");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.signUp(&config, &auth, "", "");
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  fbdo.setBSSLBufferSize(512,512);   

  while(!Firebase.ready()){
    delay(100);
  }

  lcd.clear();
  lcd.print("DB Ready");
  delay(800);

  SPI.begin();
  rfid.PCD_Init();

  lcd.clear();
  lcd.print("Scan Student");
}


//============= LOOP =============
void loop(){

  if(WiFi.status()!=WL_CONNECTED){
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(1000);
    return;
  }

  if(!rfid.PICC_IsNewCardPresent()) return;
  if(!rfid.PICC_ReadCardSerial()) return;

  String tag="";
  for(byte i=0;i<rfid.uid.size;i++){
    if(rfid.uid.uidByte[i]<0x10) tag+="0";
    tag+=String(rfid.uid.uidByte[i],HEX);
  }
  tag.toUpperCase();

  Serial.println("UID: "+tag);


  //=========== STUDENT ===========
  if(!studentScanned){

    studentID = tag;

    if(Firebase.RTDB.getString(&fbdo,"/Students/"+studentID+"/name")){

      studentName = fbdo.stringData();

      if(Firebase.RTDB.getString(&fbdo,"/Students/"+studentID+"/department")){
        department = fbdo.stringData();
      } else {
        department = "N/A";
      }

      studentScanned = true;

      lcd.clear();
      lcd.print(studentName);
      lcd.setCursor(0,1);
      lcd.print(department);

      delay(1200);

      lcd.clear();
      lcd.print("Scan Book");
      return;
    }
    else{
      lcd.clear();
      lcd.print("Not Registered");
      delay(1200);
      lcd.clear();
      lcd.print("Scan Student");
      return;
    }
  }


  //=========== BOOK ===========
  String bookID = tag;

  String bookName="", key="";
  int copyNo=0;

  if(!Firebase.RTDB.getString(&fbdo,"/Books/"+bookID+"/title")){
    lcd.clear(); lcd.print("Invalid Book");
    delay(1200);
    studentScanned=false;
    lcd.clear(); lcd.print("Scan Student");
    return;
  }

  bookName = fbdo.stringData();

  
  if(Firebase.RTDB.getString(&fbdo,"/Books/"+bookID+"/inventoryKey")){
    key = fbdo.stringData();
  }else{
    key = bookName;
  }

  Firebase.RTDB.getInt(&fbdo,"/Books/"+bookID+"/copyNo");
  copyNo = fbdo.intData();

  lcd.clear();
  lcd.print(bookName);
  lcd.setCursor(0,1);
  lcd.print("Copy:");
  lcd.print(copyNo);

  delay(1200);


  // Inventory
  String availPath="/Inventory/"+key+"/availableCopies";
  String totalPath="/Inventory/"+key+"/totalCopies";
  String issuedPath="/Issued/"+bookID+"/student";

  int copies=0,total=0;
  bool available=true;
  String issuedTo="";

  if(Firebase.RTDB.getInt(&fbdo,availPath)) copies = fbdo.intData();
  if(Firebase.RTDB.getInt(&fbdo,totalPath)) total = fbdo.intData();

  if(Firebase.RTDB.getString(&fbdo,issuedPath))
    issuedTo = fbdo.stringData();

  Firebase.RTDB.getBool(&fbdo,"/Books/"+bookID+"/available");
  available = fbdo.boolData();


  //=========== ISSUE ===========
  if(available){

    if(copies<=0){
      lcd.clear(); lcd.print("No Copies");
      delay(1200);
      studentScanned=false;
      lcd.clear(); lcd.print("Scan Student");
      return;
    }

    int newCopies = copies - 1;
    if(newCopies < 0) newCopies = 0;

    Firebase.RTDB.setBool(&fbdo,"/Books/"+bookID+"/available",false);
    delay(50);
    Firebase.RTDB.setInt(&fbdo,availPath,newCopies);
    delay(50);
    Firebase.RTDB.setString(&fbdo,issuedPath,studentID);

    sendToSheet(studentName, bookName, "Issued", newCopies);

    lcd.clear();
    lcd.print("Issued");
    lcd.setCursor(0,1);
    lcd.print(newCopies);
    lcd.print("/");
    lcd.print(total);
  }


  //=========== RETURN ===========
  else if(issuedTo==studentID){

    int newCopies = copies + 1;
    if(newCopies > total) newCopies = total;

    Firebase.RTDB.setBool(&fbdo,"/Books/"+bookID+"/available",true);
    delay(50);
    Firebase.RTDB.setInt(&fbdo,availPath,newCopies);
    delay(50);
    Firebase.RTDB.deleteNode(&fbdo,issuedPath);

    sendToSheet(studentName, bookName, "Returned", newCopies);

    lcd.clear();
    lcd.print("Returned");
    lcd.setCursor(0,1);
    lcd.print(newCopies);
    lcd.print("/");
    lcd.print(total);
  }

  else{
    lcd.clear();
    lcd.print("In Use");
  }

  delay(1500);   

  studentScanned=false;
  lcd.clear();
  lcd.print("Scan Student");
}
