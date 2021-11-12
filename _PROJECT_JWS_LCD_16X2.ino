/*Project Ini di buat oleh M.badruttamam
 * Bertujuan untuk pembelajaran 
 * JWS dengan Tampilan Lcd 16x2 I2C
 */


//=========================Memasukkan Library=================================//
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <PrayerTimes.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <EEPROM.h>


#define btnmenu A0
#define btnup   A1
#define btndown A2
#define btnset  A3


//========================Komunikasi Serial===================================//
SoftwareSerial mySerial(10, 11); // RX, TX

//========================Data Nama Hari dan Tanggal==========================//
char WeekDay[][12]   = {"AHAD", "SENIN", "SELASA", "RABU", "KAMIS", "JUM'AT", "SABTU",};
char montheyear[][4] = {"DES", "JAN", "FEB", "MAR", "APR", "MEI", "JUN", "JUL", "AGUS", "SEP", "OKT", "NOV",};

//========================Menganmbil Waktu Sholat=============================//
double times[sizeof(TimeName)/sizeof(char*)];

//========================Menganalisis Alamat lcd=============================//
LiquidCrystal_I2C lcd(0x27, 16, 2);

//========================Menganalisis RTC====================================//
RTC_DS3231 RTC;

//========================Menganalisis waktu Ihtiyat==========================//
int ihti            = 2;

//========================Mencari Titik Kordinat==============================//
float clatitude     = -7.756928;
float clongitude    = 113.211502;
int zonawaktu       = 7;

//========================Data Pin Buzzer=====================================//
const int buzzer    = 3;
int detikbeep;

//========================Data Iqomah=========================================//
int detikiqmh       = 0;
int menitiqmh       = 1;

//=======================Data Lama Adzan=====================================//
uint8_t durasiadzan = 1; // Menit
uint8_t tipealarm;

//=======================Data Waktu=========================================//
int rJam;
int rMen;
int rDet;
int rTgl;
int rHar;
int rBul;
int rTah;


//=======================Data Lama Iqomah===================================//
int iqmhs    = 1; // menit
int iqmhd    = 1; // menit
int iqmha    = 1; // menit
int iqmhm    = 1; // menit
int iqmhi    = 1; // menit

int iqmhsl   = 1; // menit
int iqmhdl   = 1; // menit
int iqmhal   = 1; // menit
int iqmhml   = 1; // menit
int iqmhil   = 1; // menit


int TJam        ;
int TMen        ;
int TDet        ;
int THar        ;

int TJaml        ;
int TMenl        ;
int TDetl        ;
int THarl        ;

int Jam, mnt, dtk, tgl, bln , thn;
bool setting = false;
bool settingl = false;

int menu = 1;
int trtl = 1;
int vol;

void setup()
{
  // initialize the LCD
  lcd.begin();
  Wire.begin();

 
 //Buzzer
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  delay(50);

  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (20);

  pinMode (btnmenu, INPUT_PULLUP);
  pinMode (btnup,   INPUT_PULLUP);
  pinMode (btndown, INPUT_PULLUP);
  pinMode (btnset,  INPUT_PULLUP);

EEPROM.write(50,0);
EEPROM.read(50);    
}

void loop() {
  
  if (digitalRead(btnmenu) == LOW) {                               // Tombol OK
    delay(200);
    lcd.clear();
    setting = true;

  }
  
  while (setting) {
   menusetting();
  }
  if(digitalRead(btnset) == LOW) {
    delay(100);
    settingl = true;
  }
  while (settingl) {
    atur();
  }
tampilnama();
AlarmSholat();
Tartil(); 
Tarhim();
   
}


//===================================================================
String konversi(int num) {
  if (num < 10) return "0" + String(num);
  else return String(num);
}

//===================================================================
String konversil(int numl) {
  if (numl < 10) return "0" + String(numl);
  else return String(numl);
}
//===================================================================
String konversill(int numll) {
  if (numll < 10) return "0" + String(numll);
  else return String(numll);
}

//===================================================================
void displayRTCll( byte _mll) {
  // Tampilan Men
  lcd.setCursor(6, 1);
  lcd.print(konversill(_mll));

}

//===================================================================
void displayRTCl( byte _jl, byte _ml) {
  // Tampilan Jam dan Men
  lcd.setCursor(5, 1);
  lcd.print(konversil(_jl));
  lcd.setCursor(7, 1);
  lcd.print(':');
  lcd.setCursor(8, 1);
  lcd.print(konversil(_ml));

}

//===================================================================
void displayRTC(byte _t, byte _b, byte _d, byte _j, byte _m) {
  // Tampilan Jam
  lcd.setCursor(1, 1);
  lcd.print(konversi(_j));
  lcd.setCursor(3, 1);
  lcd.print(':');
  lcd.setCursor(4, 1);
  lcd.print(konversi(_m));

  // Tampilan Tanggal
  lcd.setCursor(7, 1);
  lcd.print(konversi(_d));
  lcd.setCursor(9, 1);
  lcd.print('/');
  lcd.setCursor(10, 1);
  lcd.print(konversi(_b));
  lcd.setCursor(12, 1);
  lcd.print('/');
  lcd.setCursor(13, 1);
  lcd.print(konversi(_t));
}
//============================================================
void ReadRTC() {
 DateTime now = RTC.now();
  thn = now.year() - 2000;
  bln = now.month();
  tgl = now.day();
  Jam = now.hour();
  mnt = now.minute();
}
//============================================================

void atur(){
  if (!digitalRead(btndown)){
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(btndown));
  }
  if (!digitalRead(btnup)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(btnup));
  }
  if (digitalRead(btnset) == LOW){
   updateMenu();
    delay(100);
  }
    if (digitalRead(btnmenu) == LOW){
    executeAction();
    delay(100);
  }
}

void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print("~SET IQOMAH");
      lcd.setCursor(0, 1);
      lcd.print(" SET STANDBY");
      break;
    case 2:
      lcd.clear();
      lcd.print(" SET IQOMAH");
      lcd.setCursor(0, 1);
      lcd.print("~SET STANDBY");
      break;
    case 3:
      lcd.clear();
      lcd.print("~SET WKT TARTIL");
      lcd.setCursor(0, 1);
      lcd.print(" SET WKT TARHIM");
      break;
    case 4:
      lcd.clear();
      lcd.print(" SET WKT TARTIL");
      lcd.setCursor(0, 1);
      lcd.print("~SET WKT TARHIM");
      break;
    case 5:
      lcd.clear();
      lcd.print("~SET SRH TARTIL");
      lcd.setCursor(0,1);
      lcd.print(" SET ON/OF TRTL");
      break;
    case 6:
      lcd.clear();
      lcd.print(" SET SRH TARTIL");
      lcd.setCursor(0,1);
      lcd.print("~SET ON/OF TRTL");
      break;
    case 7:
      lcd.clear();
      lcd.print("~SET ON/OF TRHM");
      lcd.setCursor(0,1);
      lcd.print(" MANUAL SURAT");
      break;
    case 8:
      lcd.clear();
      lcd.print(" SET ON/OF TRHM");
      lcd.setCursor(0,1);
      lcd.print("~MANUAL SURAT");
      break;
    case 9:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("~KEMBALI KE WKT");
      lcd.setCursor(0,1);
      lcd.print("~TEKAN TMBL SET");
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
    delay(700);
      action1();
      break;
    case 2:
    delay(700);
      action2();
      break;
    case 3:
    delay(700);
      action3();
      break;
    case 4:
    delay(700);
      action4();
      break;
      case 5:
    delay(700);      
       action5();
      break;
      case 6:
    delay(700);
       action6();
      break;
      case 7:
    delay(700);
       action7();
      break;
      case 8:
    delay(700);
       action8();
      break;
      case 9:
    delay(700);      
       action9();
      break;      
  }
}

void action1() {

lcd.clear();   
setIQMH:

  lcd.setCursor(3, 0);
  lcd.print("SET IQOMAH 1");
  displayRTCll(iqmhs);

  if (digitalRead(btnmenu) == LOW) {
    delay(300);
    lcd.clear();   
    goto setIQMH2;
  }
  else if (digitalRead(btnup) == LOW) {
    iqmhs++;
    if (iqmhs >= 59) iqmhs = 1;
    EEPROM.write(2, iqmhs); 
    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhs--;
    if (iqmhs < 1) iqmhs = 59;
    EEPROM.write(2, iqmhs);  
  }
  delay(300);
  goto setIQMH;

//============================================================
lcd.clear();   
setIQMH2:

  lcd.setCursor(3, 0);
  lcd.print("SET IQOMAH 2");
  displayRTCll(iqmhd);

  if (digitalRead(btnmenu) == LOW) {
    delay(300);
    lcd.clear();
    goto setIQMH3;

  }
  else if (digitalRead(btnup) == LOW) {
    iqmhd++;
    if (iqmhd >= 59) iqmhd = 1;
    EEPROM.write(3, iqmhd); 
    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhd--;
    if (iqmhd < 1) iqmhd = 59;
    EEPROM.write(3, iqmhd);     
  }

  delay(300);
  goto setIQMH2;

//============================================================
lcd.clear();   
setIQMH3:

  lcd.setCursor(3, 0);
  lcd.print("SET IQOMAH 3");
  displayRTCll(iqmha);

  if (digitalRead(btnmenu) == LOW) {
    delay(300);
    lcd.clear();
    goto setIQMH4;

  }
  else if (digitalRead(btnup) == LOW) {
    iqmha++;
    if (iqmha >= 59) iqmha = 1;
    EEPROM.write(4, iqmha);     

  }
  else if (digitalRead(btndown) == LOW) {
    iqmha--;
    if (iqmha < 1) iqmha = 59;
    EEPROM.write(4, iqmha);     
  
  }

  delay(300);

  goto setIQMH3;

//
//  //============================================================
lcd.clear();
setIQMH4:
  lcd.setCursor(3, 0);
  lcd.print("SET IQOMAH 4");
  displayRTCll(iqmhm);

  if (digitalRead(btnmenu) == LOW) {
    delay(300);
    lcd.clear();    
    goto setIQMH5;
  }
  else if (digitalRead(btnup) == LOW) {
    iqmhm++;
    if (iqmhm >= 59) iqmhm = 1;
    EEPROM.write(5, iqmhm); 

    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhm--;
    if (iqmhm < 1) iqmhm = 59;
    EEPROM.write(5, iqmhm); 
    
  }

  delay(300);
  goto setIQMH4;

//  //============================================================
lcd.clear();
setIQMH5:
  lcd.setCursor(3, 0);
  lcd.print("SET IQOMAH 5");
  displayRTCll(iqmhi);

  if (digitalRead(btnset) == LOW) {
    delay(200);
    lcd.clear();   
    goto setEND;
  }
  else if (digitalRead(btnup) == LOW) {
    iqmhi++;
    if (iqmhi >= 59) iqmhi = 1;
    EEPROM.write(6, iqmhi); 

    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhi--;
    if (iqmhi < 1) iqmhi = 59;
    EEPROM.write(6, iqmhi); 
    
  }

  delay(300);
  goto setIQMH5;

//===========================================================
setEND:
  iqmhs = EEPROM.read(2);
  iqmhd = EEPROM.read(3);
  iqmha = EEPROM.read(4);
  iqmhm = EEPROM.read(5);
  iqmhi = EEPROM.read(6);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Data Tersimpan");
  delay(1000);
  lcd.clear();
  updateMenu();

}
void action2() {

lcd.clear();   
setIQMHl:

  lcd.setCursor(3, 0);
  lcd.print("SET STANBY 1");
  displayRTCll(iqmhsl);
  
  if (digitalRead(btnmenu) == LOW) {
    delay(300);
    lcd.clear();   
    goto setIQMH2l;
  }
  else if (digitalRead(btnup) == LOW) {
    iqmhsl++;
    if (iqmhsl >= 59) iqmhsl = 1;
    EEPROM.write(2, iqmhsl); 

    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhsl--;
    if (iqmhsl < 1) iqmhsl = 59;
    EEPROM.write(2, iqmhsl);  

  }
  delay(300);
  goto setIQMHl;

//============================================================
lcd.clear();   
setIQMH2l:

  lcd.setCursor(3, 0);
  lcd.print("SET STANDBY 2");
  displayRTCll(iqmhdl);

  if (digitalRead(btnmenu) == LOW) {
    delay(300);
    lcd.clear();
    goto setIQMH3l;

  }
  else if (digitalRead(btnup) == LOW) {
    iqmhdl++;
    if (iqmhdl >= 59) iqmhdl = 1;
    EEPROM.write(3, iqmhdl); 

    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhdl--;
    if (iqmhdl < 1) iqmhdl = 59;
    EEPROM.write(3, iqmhdl); 
   
  }

  delay(300);
  goto setIQMH2l;

//============================================================
lcd.clear();   
setIQMH3l:

  lcd.setCursor(3, 0);
  lcd.print("SET STANDBY 3");
  displayRTCll(iqmhal);

  if (digitalRead(btnmenu) == LOW) {
    delay(300);
    lcd.clear();
    goto setIQMH4l;

  }
  else if (digitalRead(btnup) == LOW) {
    iqmhal++;
    if (iqmhal >= 59) iqmhal = 1;
    EEPROM.write(4, iqmhal);     

    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhal--;
    if (iqmhal < 1) iqmhal = 59;
    EEPROM.write(4, iqmhal);     
    
  }

  delay(300);

  goto setIQMH3l;


//  //============================================================
lcd.clear();
setIQMH4l:
  lcd.setCursor(3, 0);
  lcd.print("SET STANDBY 4");
  displayRTCll(iqmhml);
  
  if (digitalRead(btnmenu) == LOW) {
    delay(300);
    lcd.clear();    
    goto setIQMH5l;
  }
  else if (digitalRead(btnup) == LOW) {
    iqmhml++;
    if (iqmhml >= 59) iqmhml = 1;
    EEPROM.write(5, iqmhml); 

    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhml--;
    if (iqmhml < 1) iqmhml = 59;
    EEPROM.write(5, iqmhml); 
    
  }

  delay(300);
  goto setIQMH4l;

//  //============================================================
lcd.clear();
setIQMH5l:
  lcd.setCursor(3, 0);
  lcd.print("SET STANDBY 5");
   displayRTCll(iqmhil);


  if (digitalRead(btnset) == LOW) {
    delay(200);
    lcd.clear();   
    goto setENDl;
  }
  else if (digitalRead(btnup) == LOW) {
    iqmhil++;
    if (iqmhil >= 59) iqmhil = 1;
    EEPROM.write(6, iqmhil); 

    
  }
  else if (digitalRead(btndown) == LOW) {
    iqmhil--;
    if (iqmhil < 1) iqmhil = 59;
    EEPROM.write(6, iqmhil); 
    
  }

  delay(300);
  goto setIQMH5l;

//===========================================================
setENDl:
  iqmhsl = EEPROM.read(2);
  iqmhdl = EEPROM.read(3);
  iqmhal = EEPROM.read(4);
  iqmhml = EEPROM.read(5);
  iqmhil = EEPROM.read(6);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Data Tersimpan");
  delay(1000);
  lcd.clear();
  updateMenu();

}
void action3() {
//============================================================

lcd.clear();
BacaRTC();
setTARTIL:
  lcd.setCursor(1, 0);
  lcd.print("SET JAM TARTIL");
   displayRTCl(TJam, TMen);
   
  if (digitalRead(btnmenu) == LOW) {
    delay(500);
    goto setMNTT;
  }
  else if (digitalRead(btnup) == LOW) {
    TJam++;
    if (TJam >= 24) TJam = 0;
    EEPROM.write(10, TJam);

  }
  else if (digitalRead(btndown) == LOW) {
    TJam--;
    if (TJam < 0) TJam = 23;
    EEPROM.write(10, TJam);

  }
  delay(300);
  goto setTARTIL;

//============================================================
lcd.clear();
setMNTT:
  lcd.setCursor(1, 0);
  lcd.print("SET MEN TARTIL");
   displayRTCl(TJam, TMen);

  if (digitalRead(btnset) == LOW) {
    delay(500);
    goto setENDD;
  }
  else if (digitalRead(btnup) == LOW) {
    TMen++;
    if (TMen >= 59) TMen = 0;
    EEPROM.write(11, TMen);
  }
  else if (digitalRead(btndown) == LOW) {
    TMen--;
    if (TMen < 0) TMen = 59;
    EEPROM.write(11, TMen);

  }
  delay(300);
  goto setMNTT;

//====================================================
setENDD:
  TJam = EEPROM.read(10);
  TMen = EEPROM.read(11);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Data Tersimpan");
  delay(1000);
  lcd.clear();
  updateMenu();

}
void action4() {
//============================================================

lcd.clear();
BacaRTC();
setTARHIM:
  lcd.setCursor(1, 0);
  lcd.print("SET JAM TARHIM");
   displayRTCl(TJaml, TMenl);
   
  if (digitalRead(btnmenu) == LOW) {
    delay(500);
    goto setMNTTl;
  }
  else if (digitalRead(btnup) == LOW) {
    TJaml++;
    if (TJaml >= 24) TJaml = 0;
    EEPROM.write(12, TJaml);

  }
  else if (digitalRead(btndown) == LOW) {
    TJaml--;
    if (TJaml < 0) TJaml = 23;
    EEPROM.write(12, TJaml);

  }
  delay(300);
  goto setTARHIM;

//============================================================
lcd.clear();
setMNTTl:
  lcd.setCursor(1, 0);
  lcd.print("SET MEN TARTIL");
   displayRTCl(TJaml, TMenl);

  if (digitalRead(btnset) == LOW) {
    delay(500);
    goto setENDDl;
  }
  else if (digitalRead(btnup) == LOW) {
    TMenl++;
    if (TMenl >= 59) TMenl = 0;
    EEPROM.write(13, TMenl);
  }
  else if (digitalRead(btndown) == LOW) {
    TMenl--;
    if (TMenl < 0) TMenl = 59;
    EEPROM.write(13, TMenl);

  }
  delay(300);
  goto setMNTTl;

//====================================================
setENDDl:
  TJam = EEPROM.read(12);
  TMen = EEPROM.read(13);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Data Tersimpan");
  delay(1000);
  lcd.clear();
  updateMenu();


}
void action5() {
//  lcd.clear();
//  setTRTLL:
//
//  lcd.setCursor(0,0);
//  lcd.print("SET SRH TARHIM");
//
//  if (digitalRead(btnset) == LOW) {
//    delay(500);
//    goto setENTRTLL;
//  }
//    else if (digitalRead(btnup) == LOW) {
//    trtl++;
//    if (trtl >= 5) trtl = 1;
//    EEPROM.write(14, trtl);
//  }
//  else if (digitalRead(btndown) == LOW) {
//    trtl--;
//    if (trtl < 1) trtl = 5;
//    EEPROM.write(14, trtl);
//
//  }
//
// switch (trtl){
//  case 1:
//    lcd.setCursor(0,0);
//    lcd.print("SET SRH TARHIM-1");
//    lcd.setCursor(3,1);
//    lcd.print("SRH-01");
//    mp3_play();
//    
//  break;
//  case 2:
//    lcd.setCursor(0,0);
//    lcd.print("SET SRH TARHIM-2");
//    lcd.setCursor(3,1);
//    lcd.print("SRH-02");
//    mp3_play();
//  break;
//  case 3:
//    lcd.setCursor(0,0);
//    lcd.print("SET SRH TARHIM-3");
//    lcd.setCursor(3,1);
//    lcd.print("SRH-03");
//    mp3_play();
//  break;
//  case 4:
//    lcd.setCursor(0,0);
//    lcd.print("SET SRH TARHIM-4");
//    lcd.setCursor(3,1);
//    lcd.print("SRH-04");
//    mp3_stop();
//    
//  break;
//    
//  
// }
//  delay(300);
//  goto setTRTLL;
//
////=====================================================================================
//setENTRTLL:
//  trtl = EEPROM.read(14);
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Data Tersimpan");
//  delay(1000);
//  lcd.clear();
//  updateMenu();

//======================================================================================

}
void action6() {
  lcd.clear();
  lcd.print(">Executing #4");
  delay(1500);

}
void action7() {
  lcd.clear();
  lcd.print(">Executing #4");
  delay(1500);

}
void action8() {
  lcd.clear();
  lcd.print(">Executing #4");
  delay(1500);

}
void action9() {

//============================================================
lcd.clear();
setMNTTl:
  lcd.setCursor(2, 0);
  lcd.print("SET SELESAI");

  if (digitalRead(btnset) == LOW) {
    delay(500);
    goto setSELESAI;
  }
    delay(300);
  goto setMNTTl;


setSELESAI:
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("OK");
  delay(1000);
  lcd.clear(); 
  menu = 0;
  settingl = false;

 }


uint8_t tmpnama;
void tampilnama(){
  
  switch(tmpnama) {
    case 0:
     tampiltanggal();    
      break;
    case 1:
        saya();
        break;

    case 2:
        tampiljadwalsholat();
        break;
   case 3:
    TampilAdzan();
     break;
   case 4:
     santai();
     break;
   case 5:
    iqomah();
      break;

   case 6:
    TampilSaatSholat();
     break;

  }
}

void santai(){
  
  static uint32_t pM;
  uint32_t cM = millis();
  static char hitungm[6];

  lcd.setCursor(0,0);
  lcd.print("TUNGGU WKT IQMH");

   if (detikiqmh == 60) {
    detikiqmh =0;
   }
   if (cM - pM >= 1000) {
    pM = cM;
    detikiqmh--;
    
    if (menitiqmh == 0 && detikiqmh == 0) {
      lcd.clear();
      detikiqmh = 59;
      tmpnama = 5;
    
   }
    if (detikiqmh < 0) {
    detikiqmh = 59;
    menitiqmh--;
   
   }
 }
 sprintf(hitungm, "%02d:%02d", menitiqmh, detikiqmh);
 lcd.setCursor(5,1);
 lcd.print(hitungm);
}

void BacaRTC() {

 DateTime now = RTC.now();

  rJam = now.hour();
  rMen = now.minute();
  rDet = now.second();
  rTgl = now.day();
  rHar = now.dayOfTheWeek();
  rBul = now.month();
  rTah = now.year();
}

void Tartil(){
  BacaRTC();
  if ( TJam == rJam && TMen == rMen ){
    delay(100);
    mp3_play(6);

  }
}
void Tarhim(){

  if ( TJaml == rJam  && TMenl == rMen ) { 
  delay(100);
  mp3_play(5);
  }
}
void tampiltanggal(){
 
 DateTime now = RTC.now();

  rTgl = now.day();
  rHar = now.dayOfTheWeek();
  rBul = now.month();
  rTah = now.year();
  
    char JAM[7];
    char Tanggal[7]; 
    char Hari [8];

    static uint32_t pM;
    uint32_t cM = millis();
    static uint8_t flag;

    if (cM - pM >2000) {
      pM = cM;
      flag++;

    sprintf(Hari, "%s", WeekDay[rHar]);
    lcd.setCursor(5,0);
    lcd.print(Hari);
    sprintf(Tanggal, "%02d/%s/%02d", rTgl,montheyear[rBul], rTah);
    lcd.setCursor(2,1);
    lcd.print(Tanggal);

    if(flag >= 2){
      flag = 0;
      lcd.clear();
      tmpnama = 1;
 
    }
   }
}


void saya(){

    static uint32_t pM;
    uint32_t cM = millis();
    static uint8_t flag;

    if (cM - pM >2000) {
      pM = cM;
      flag++;
      
  lcd.setCursor(2,0);
  lcd.print("Project JWS");
  lcd.setCursor(1,1);
  lcd.print("TamamNamikaze");
      if(flag >= 2){
      flag = 0;
      lcd.clear();
      tmpnama = 2;
    }
 }
}

void jadwalsholat(){
  
    /*CALCULATION METHOD
    ------------------
    Jafari,   // Ithna Ashari
    Karachi,  // University of Islamic Sciences, Karachi
    ISNA,     // Islamic Society of North America (ISNA)
    MWL,      // Muslim World League (MWL)
    Makkah,   // Umm al-Qura, Makkah
    Egypt,    // Egyptian General Authority of Survey
    Custom,   // Custom Setting

    JURISTIC
    --------
    Shafii,    // Shafii (standard)
    Hanafi,    // Hanafi

    ADJUSTING METHOD
    ----------------
    None,        // No adjustment
    MidNight,   // middle of night
    OneSeventh, // 1/7th of night
    AngleBased, // angle/60th of night

    TIME IDS
    --------
    Fajr,
    Sunrise,
    Dhuhr,
    Asr,
    Sunset,
    Maghrib,
    Isha
  
  */

  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);

  get_prayer_times(rTah, rBul, rTgl, clatitude, clongitude, zonawaktu, times);

}

void tampiljadwalsholat(){
  jadwalsholat();
  TampilJam(); 
  static uint8_t i;
  static uint32_t pM;
  uint32_t cM = millis();
  
  char sholat[7];
  char Jam1[5];
  char TimeName[][8] = {"SUBUH ","TERBIT ","DZUHUR ","ASHAR ","TRBNM ","MAGRIB "," ISYA' "};
  int hours, minutes;


  if (cM - pM >= 2000) {
    
    pM = cM;
//    lcd.clear();

   //if (i == 1) {i = 2;} // Abaikan Terbit
   //if (i == 4) {i = 5;} // Abaikan Terbenam

    get_float_time_parts(times[i], hours, minutes);
    minutes = minutes + ihti;

    if (minutes >= 60) {
      minutes = minutes - 60;
      hours ++;
    }

    String sholat = TimeName[i];
    sprintf(Jam1,"%02d:%02d", hours, minutes);        
    lcd.setCursor(10,0);
    lcd.print(sholat);
    lcd.setCursor(10,1);
    lcd.print(Jam1);
    i++;
    
    if (i > 7) {
      get_float_time_parts(times[0], hours, minutes);
      minutes = minutes + ihti;
      if (minutes < 11) {
        minutes = 60 - minutes;
        hours --;
      } else {
        minutes = minutes - 10 ;
      }
      sprintf(Jam1,"%02d:%02d", hours, minutes);
//      lcd.clear();
      lcd.setCursor(10,0);
      lcd.print("TANBIH");
      lcd.setCursor(10,1);
      lcd.print(Jam1);
      
      if (i > 8) {
        i = 0;
        lcd.clear();
        tmpnama = 0;
      }    
    }    
  }  
}
void TampilJam(){
 
 DateTime now = RTC.now();
 
    char JAM2[2];
    char JAM3[4];

    sprintf(JAM2, "%02d:%02d:%02d |", now.hour(), now.minute(), now.second());
    lcd.setCursor(0,0);
    lcd.print(JAM2);

    sprintf(JAM3, "%02d/%02d/%02d |", now.day(), now.month(), now.year()-2000);
    lcd.setCursor(0,1);
    lcd.print(JAM3);
    

}

//----------------------------------------------------------------------
// ALARM SHOLAT BERJALAN SAAT MASUK WAKTU SHOLAT

void AlarmSholat() {
 
 DateTime now = RTC.now();

  rJam = now.hour();
  rMen = now.minute();
  rDet = now.second();
  rTgl = now.day();
  rHar = now.dayOfTheWeek();
  rBul = now.month();
  rTah = now.year();
  jadwalsholat();
  int hours, minutes, seconds;

  // Tanbih Imsak
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + ihti;

  if (minutes < 10) {
    
    minutes = 60 - minutes;
    hours --;
    
  } else {
    
    minutes = minutes - 10 ;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 0;
    detikbeep = 0;
    lcd.clear();
    tmpnama = 3;

  }

  // Subuh
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 1;
    detikbeep = 0;
    mp3_play(2);
    lcd.clear();
    tmpnama = 3;
    
  }


  // Dzuhur
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0 && rHar !=5) { //&& Hari != 5
    
    tipealarm = 2;
    detikbeep = 0;
    mp3_play(1); 
    lcd.clear();
    tmpnama = 3;

  } else if (rJam == hours && rMen == minutes && rDet == 0 && rHar == 5 ) { //&& Hari == 5
    
    tipealarm = 3;
    detikbeep = 0;
    lcd.clear();
    tmpnama = 3;

  }


  // Ashar
  get_float_time_parts(times[3], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 4;
    detikbeep = 0;
    mp3_play(1);
    lcd.clear();
    tmpnama = 3;
    
  }

  // Maghrib
  get_float_time_parts(times[5], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 5;
    detikbeep = 0;
    mp3_play(1);
    lcd.clear();
    tmpnama = 3;
    
  }

  // Isya'
  get_float_time_parts(times[6], hours, minutes);
  minutes = minutes + ihti;

  if (minutes >= 60) {
    
    minutes = minutes - 60;
    hours ++;
    
  }

  if (rJam == hours && rMen == minutes && rDet == 0) {
    
    tipealarm = 6;
    detikbeep = 0;
    mp3_play(1);
    lcd.clear();
    tmpnama = 3;
  }
  
  
}

//----------------------------------------------------------------------
// TAMPILAN ADZAN

void TampilAdzan() {

  BunyiBeep(2,6);
  
  static uint32_t pM;
  uint32_t cM = millis();
  static uint16_t det;

  if (tipealarm == 0) {
      
    lcd.setCursor(4,0);
    lcd.print("TANBIH");
    lcd.setCursor(4,1);
    lcd.print("IMSAK");
    
  }
  
  if (tipealarm == 1) {


    lcd.setCursor(4,0);
    lcd.print("ADZAN");
    lcd.setCursor(4,1);
    lcd.print("SUBUH");
    
    menitiqmh = iqmhsl;
    menitiqmh = iqmhs;
    
  }
  
  if (tipealarm == 2) {
    
    lcd.setCursor(4,0);
    lcd.print("ADZAN");
    lcd.setCursor(4,1);
    lcd.print("DZUHUR");
   
    menitiqmh = iqmhdl;
    menitiqmh = iqmhd;
    
  }
  
  if (tipealarm == 3) {
    
    lcd.setCursor(4,0);
    lcd.print("ADZAN");
    lcd.setCursor(4,1);
    lcd.print("JUM'AT");
    
  }
  
  if (tipealarm == 4) {
  
    lcd.setCursor(4,0);
    lcd.print("ADZAN");
    lcd.setCursor(4,1);
    lcd.print("ASHAR");

    menitiqmh = iqmhal;    
    menitiqmh = iqmha;
    
  }
  
  if (tipealarm == 5) {
  
    lcd.setCursor(4,0);
    lcd.print("ADZAN");
    lcd.setCursor(4,1);
    lcd.print("MAGHRIB");

    menitiqmh = iqmhml;
    menitiqmh = iqmhm;
    
  } 
  
  if (tipealarm == 6) {
  
    lcd.setCursor(4,0);
    lcd.print("ADZAN");
    lcd.setCursor(4,1);
    lcd.print("ISYA");

    menitiqmh = iqmhil;
    menitiqmh = iqmhi;
    
  }  

  if (cM-pM >= 1000) {
    
    det++;   

    if (tipealarm == 0) {      
      
      if (det == 60) {
        lcd.clear();
        det = 0;
        detikbeep = 0;
        tmpnama = 0;
      }
      
    }

    
    if (tipealarm == 3) {
    
      if (det == durasiadzan * 60) {
        lcd.clear();
        det = 0;
        detikbeep = 0;
        tmpnama = 0;
      }
      
    }
    
    
    if (tipealarm == 1 or tipealarm == 2 or tipealarm == 4 or tipealarm == 5 or tipealarm == 6) {
          
      if (det == durasiadzan * 60) {
        lcd.clear();
        det = 0;
        detikbeep = 0;
        tmpnama = 4;
      }
      
    }
    
    pM = cM;
    
  }  
  
}


//----------------------------------------------------------------------
// TAMPILAN SAAT SHOLAT

void TampilSaatSholat() {

  BunyiBeep(1,4);

  static uint32_t pM;
  uint32_t cM = millis();
  static uint32_t durasi = 10; // Detik
  static uint32_t det;
  

  lcd.setCursor(2,0);
  lcd.print("LURUSKAN DAN");
  lcd.setCursor(2,1);
  lcd.print("RAPATKAN SHAF");

  if (cM - pM >= 1000) {
    pM = cM;
    det++;

    if (durasi == det) {
      
      detikbeep = 0;
      det = 0;
      lcd.clear();
      tmpnama = 0;
    }
  }    
}

  
void iqomah(){
  
  static uint32_t pM;
  uint32_t cM = millis();
  static char hitungm[6];

  lcd.setCursor(5,0);
  lcd.print("IQOMAH");

   if (detikiqmh == 60) {
    detikiqmh =0;
   }
   if (cM - pM >= 1000) {
    pM = cM;
    detikiqmh--;
    
    if (menitiqmh == 0 && detikiqmh == 0) {
      lcd.clear();
      detikiqmh = 59;
      tmpnama = 6;
    
   }
    if (detikiqmh < 0) {
    detikiqmh = 59;
    menitiqmh--;
   
   }
 }
 sprintf(hitungm, "%02d:%02d", menitiqmh, detikiqmh);
 lcd.setCursor(5,1);
 lcd.print(hitungm);

}

//----------------------------------------------------------------------
// BUNYI BEEP BUZZER

void BunyiBeep(uint8_t tipebeep, uint8_t durasibeep) {

  static uint32_t pMBuzT;
  static uint32_t pMBuzB;
  static boolean beep;
  static uint8_t dt;

  if (millis() - pMBuzB >= 3000) {   
    detikbeep++;
    pMBuzB = millis();
  }

  if (detikbeep < durasibeep) {
    tipebeep = tipebeep;
  } else {
    tipebeep = 0;
    durasibeep = 0;
    //db = 0;
  }

  if (tipebeep == 0) {
      digitalWrite(buzzer, LOW);
  }

  if (tipebeep == 1) {    
    if (millis() - pMBuzT >= 500) {   
      dt++;
      beep = !beep;
      pMBuzT = millis();        
    }
  
    if (dt == 6) {
      dt = 0;
      tipebeep = 0;       
    }
  
    if (beep) {
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }    
  }

  if (tipebeep == 2) {
    if (millis() - pMBuzT >= 1000) {   
      dt++;
      beep = !beep;
      pMBuzT = millis();     
    }
  
    if (dt == 6) {
      dt = 0;
      tipebeep = 0;       
    }
  
    if (beep) {
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }
  }
    
}
void menusetting(){
  DateTime now = RTC.now();
  ReadRTC();
  int tahun;


  //============================================================
setJAM:
  lcd.setCursor(0, 0);
  lcd.print("    Set  JAM    ");
  displayRTC(thn, bln, tgl, Jam, mnt);

  if (digitalRead(btnmenu) == LOW) {
    delay(500);
    goto setMNT;
  }
  else if (digitalRead(btnup) == LOW) {
    Jam++;
    delay(500);
    if (Jam >= 24) Jam = 0;
  }
  else if (digitalRead(btndown) == LOW) {
    Jam--;
    delay(500);
    if (Jam < 0) Jam = 23;
  }

  now = RTC.now();
  tahun = thn + 2000;
  RTC.adjust(DateTime(tahun, bln, tgl, Jam, mnt, now.hour()));
  goto setJAM;

  //============================================================
setMNT:
  lcd.setCursor(0, 0);
  lcd.print("    Set  MNT    ");
  displayRTC(thn, bln, tgl, Jam, mnt);

  if (digitalRead(btnmenu) == LOW) {
    delay(500);
    goto setTGL;
  }
  else if (digitalRead(btnup) == LOW) {
    mnt++;
    if (mnt >= 60) mnt = 0;
  }
  else if (digitalRead(btndown) == LOW) {
    mnt--;
    if (mnt < 0) mnt = 59;
  }

  now = RTC.now();
  tahun = thn + 2000;
  RTC.adjust(DateTime(tahun, bln, tgl, Jam, mnt, now.hour()));
  delay(300);

  goto setMNT;

  //============================================================
setTGL:
 
  lcd.setCursor(0, 0);
  lcd.print("    Set  TGL    ");
  displayRTC(thn, bln, tgl, Jam, mnt);

  if (digitalRead(btnmenu) == LOW) {
    delay(500);
    goto setBLN;
  }
  else if (digitalRead(btnup) == LOW) {
    tgl++;
    if (tgl >= 32) tgl = 1;
  }
  else if (digitalRead(btndown) == LOW) {
    tgl--;
    if (tgl < 1) tgl = 32;
  }

  now = RTC.now();
  tahun = thn + 2000;
  RTC.adjust(DateTime(tahun, bln, tgl, Jam, mnt, now.hour()));
  delay(300);
  goto setTGL;

  //============================================================
setBLN:
  lcd.setCursor(0, 0);
  lcd.print("    Set  BLN    ");
  displayRTC(thn, bln, tgl, Jam, mnt);

  if (digitalRead(btnmenu) == LOW) {
    delay(500);
    goto setTHN;
  }
  else if (digitalRead(btnup) == LOW) {
    bln++;
    if (bln >= 13) bln = 1;
  }
  else if (digitalRead(btndown) == LOW) {
    bln--;
    if (bln < 1) bln = 13;
  }

  now = RTC.now();
  tahun = thn + 2000;
  RTC.adjust(DateTime(tahun, bln, tgl, Jam, mnt, now.hour()));
  delay(300);
  goto setBLN;

  //============================================================
setTHN:
  lcd.setCursor(0, 0);
  lcd.print("    Set  THN    ");
  displayRTC(thn, bln, tgl, Jam, mnt);

  if (digitalRead(btnmenu) == LOW) {
    goto setEND;
  }
  else if (digitalRead(btnup) == LOW) {
    thn++;
    if (thn > 99) thn = 19;
  }
  else if (digitalRead(btndown) == LOW) {
    thn--;
    if (thn < 19) thn = 99;
  }

  now = RTC.now();
  tahun = thn + 2000;
  RTC.adjust(DateTime(tahun, bln, tgl, Jam, mnt, now.hour()));
  delay(300);
  goto setTHN;

setEND:
  setting = false;
  delay(500);
  lcd.clear();
} 
