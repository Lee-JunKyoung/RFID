#include <MFRC522.h>              // RFID 라이브러리
#include <LiquidCrystal_I2C.h>    // 1602 LCD 라이브러리
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>          

// 버튼 핀 설정

#define RST_PIN D3                          // RST핀을 3번핀에 연결
#define SS_PIN D4                           // SS핀을 4번핀에 연결
LiquidCrystal_I2C lcd(0x27, 16, 2);                   // lcd 객체 생성 (I2C용 주소, 사이즈)
MFRC522 rf_id(SS_PIN, RST_PIN);                       // rf_id 객체 생성
const char *ssid     = "EN325";    // PUT YOUR WIFI NAME HERE
const char *password = "en6060!@";      // PUT YOUR WIFI PASSWORD HERE
WiFiUDP ntpUDP;
#define offset 32400                    //UTC -1 = -3600,UTC +1 = 3600, UTC +2 = 7200 (FOR EVERY +1 HOUR ADD 3600,SUBTRACT 3600 FOR -1 HOUR)
NTPClient timeClient(ntpUDP, "pool.ntp.org");



String tag_id = "";                                   // 태그ID 저장 변수
String access_id = "5330673";                         // 접근 허용 ID

void setup() {
  pinMode(D0, INPUT);
  pinMode(D8, INPUT);
  SPI.begin();                                        // SPI 통신 시작    
  rf_id.PCD_Init();                                   // rf_id 객체 초기화
  WiFi.begin(ssid, password);
  timeClient.begin();
  timeClient.setTimeOffset(offset);

  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

 
}
void loop() {
timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;
  String currentDate = String(currentYear)+"/"+String(currentMonth)+"/"+String(monthDay);
 
  lcd.setCursor(0, 0);
  lcd.print("DATE:"+currentDate);
  lcd.setCursor(0, 1);
  lcd.print("TIME:"+formattedTime);
  lcd.setCursor(15, 1);
  delay(100);

if (digitalRead(D0) == HIGH){
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Scan Your Card>>");                      // 1602 LCD 0,1위치 "Scan Your Card>>" 출력
  lcd.setCursor(1, 1);
  lcd.print("Scannig.");                      // 1602 LCD 0,1위치 "Scan Your Card>>" 출력
  delay(1000);
  lcd.print("...");                      // 1602 LCD 0,1위치 "Scan Your Card>>" 출력
  delay(1000);
  lcd.print("...");
  delay(1000);
  lcd.clear();
if (!rf_id.PICC_IsNewCardPresent() || !rf_id.PICC_ReadCardSerial()) // 태그 정보가 없을 때
  {
    delay(500);                                       // 0.5초 대기
    return;                                           // return
  }

  tag_id = "";                                        // tag_id 변수 초기화

  for (uint8_t i = 0; i < 4; i++) {                   // ID 사이즈 4byte로 구성
    tag_id.concat(String(rf_id.uid.uidByte[i], HEX)); // 각각의 문자를 16진수로 변환하고, 연결하여 저장
  }
  tag_id.toUpperCase();                               // tag_id 문자열 대문자로 변경

  lcd.clear();                                        // 1602LCD 모두 지우기
  lcd.setCursor(0, 0);
 
  if (access_id == tag_id)                            // 태그ID가 접근가능한 ID라면
  {
    lcd.print("Welcome");                    // 1602 LCD 0, 0위치 " Welcome" 출력
  }
  else                                                // 접근 가능한 아이디가 아니라면
  {
    lcd.print("Retry");                     // 1602 LCD 0, 0위치 " Retry" 출력
  }

  lcd.setCursor(0, 1);
  lcd.print(" ID : ");                                // 1602 LCD 0, 1위치 " ID : " 출력
  lcd.print(tag_id);                                  // 태그 아이디 출력
  delay(2000);                                        // 2초간 대기
  lcd.clear();                                        // 1602LCD 모두 지우기
  }
  if (digitalRead(D8) == HIGH){
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Scan Your Card>>");                      // 1602 LCD 0,1위치 "Scan Your Card>>" 출력
  lcd.setCursor(1, 1);
  lcd.print("Scanning.");                      // 1602 LCD 0,1위치 "Scan Your Card>>" 출력
  delay(1000);
  lcd.print("...");                      // 1602 LCD 0,1위치 "Scan Your Card>>" 출력
  delay(1000);
  lcd.print("...");
  delay(1000);
  lcd.clear();
if (!rf_id.PICC_IsNewCardPresent() || !rf_id.PICC_ReadCardSerial()) // 태그 정보가 없을 때
  {
    delay(500);                                       // 0.5초 대기
    return;                                           // return
  }

  tag_id = "";                                        // tag_id 변수 초기화

  for (uint8_t i = 0; i < 4; i++) {                   // ID 사이즈 4byte로 구성
    tag_id.concat(String(rf_id.uid.uidByte[i], HEX)); // 각각의 문자를 16진수로 변환하고, 연결하여 저장
  }
  tag_id.toUpperCase();                               // tag_id 문자열 대문자로 변경

  lcd.clear();                                        // 1602LCD 모두 지우기
  lcd.setCursor(0, 0);
 
  if (access_id == tag_id)                            // 태그ID가 접근가능한 ID라면
  {
    lcd.print(" Goodbye!");                    // 1602 LCD 0, 0위치 " Goodbye!" 출력
  }
  else                                                // 접근 가능한 아이디가 아니라면
  {
    lcd.print(" Retry");                     // 1602 LCD 0, 0위치 " Retry" 출력
  }

  lcd.setCursor(0, 1);
  lcd.print(" ID : ");                                // 1602 LCD 0, 1위치 " ID : " 출력
  lcd.print(tag_id);                                  // 태그 아이디 출력
  delay(2000);                                        // 2초간 대기
  lcd.clear();                                        // 1602LCD 모두 지우기
  }
}
