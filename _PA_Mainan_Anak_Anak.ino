/*Project ini dibuat untuk pembelajaran dan
 * project ini bisa di kembangkan lebih lanjut 
 * dan juga semoga bermanfaat dan barokah.
  
 * project ini di buat oleh [M.badruttamam].
 * fb*M.Badruttamam.
 * iG*zhuge_liang_tamami.
 * Gmail*TamamNamikaze15@gmail.com.
 */
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define btn_AE    A0
#define btn_FJ    A1
#define btn_KO    A2
#define btn_PQ    A3

#define Buzzer    3

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

LiquidCrystal_I2C lcd(0x27, 16, 2);

MD_Parola T = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

uint8_t Tampil = 0;

void setup() {

  lcd.begin();
  lcd.backlight();
  Serial.begin (9600);
  mp3_set_serial (Serial);   
  opening();

  pinMode(btn_AE,   INPUT);
  pinMode(btn_FJ,   INPUT);
  pinMode(btn_KO,   INPUT);
  pinMode(btn_PQ,   INPUT);

  pinMode(Buzzer,   OUTPUT);
  pinMode(Buzzer,   HIGH);

  T.begin();
  T.setFont(0);
  T.setIntensity(10);
//  T.displayText("PROJECT MAINAN ANAK ANAK KARYA: PRODI TEKNOLOGI INFORMASI[ ATP ]", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
//  delay(1000);
//  T.displayClear();
}
void opening(){
  lcd.begin();
  lcd.setCursor(1,0);
  lcd.print("P");delay(300); lcd.print("R");delay(300);
  lcd.print("O");delay(300); lcd.print("J");delay(300);
  lcd.print("E");delay(300); lcd.print("C");delay(300);
  lcd.print("T");delay(300); lcd.print("  ");delay(300);
  lcd.print("M");delay(300); lcd.print("A");delay(300);
  lcd.print("I");delay(300); lcd.print("N");delay(300);
  lcd.print("A");delay(300); lcd.print("N");delay(300);

  lcd.setCursor(0,1);
  lcd.print("A");delay(200); lcd.print("N");delay(200);
  lcd.print("A");delay(200); lcd.print("K");delay(200);
  lcd.print(" ");delay(200); lcd.print("A");delay(200);
  lcd.print("N");delay(200); lcd.print("A");delay(200);
  lcd.print("K");delay(200); lcd.print("  ");delay(200);
  lcd.print("A");delay(200); lcd.print("T");delay(200);
  lcd.print("P");delay(200); lcd.print(".");delay(2000);
  lcd.clear();
}
void loop() {
  mp3_set_volume (15);
  Serial.println(analogRead(btn_AE)); 
  Serial.println(analogRead(btn_FJ)); 
if (T.displayAnimate())
if (analogRead(btn_AE) ){
  A_E();

}
else if(analogRead(btn_FJ)){
  FJ();

}
else{
  TampilAwal();
 }
}

void TampilAwal(){
  lcd.setCursor(2,0);
  lcd.print("PILIH HURUF");
  lcd.setCursor(0,1);
  lcd.print("DAN TEKAN TOMBOL");
}
void A_E(){
//    
    
    if(analogRead(btn_AE)>1011 && analogRead(btn_AE) <1015){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW);

    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print("A");
    lcd.setCursor(5,1);
    lcd.print("AYAM");
    delay(1000); 
    mp3_play (1);
    T.displayText("AYAM", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    

  }
  else if(analogRead(btn_AE)>319 && analogRead(btn_AE)<322){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW);

    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print("B");
    lcd.setCursor(5,1);
    lcd.print("BEBEK");
    delay(1000);
    mp3_play (2);  
    T.displayText("BEBEK", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
  else if(analogRead(btn_AE)>969 && analogRead(btn_AE)<971){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW);

    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print("C"); 
    lcd.setCursor(5,1);
    lcd.print("CICAK");
    delay(1000);
    mp3_play (3);
    T.displayText("CICAK", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_AE)>949 && analogRead(btn_AE)<953){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("D");
    lcd.setCursor(5,1);
    lcd.print("DOMBA");
    delay(1000);
    mp3_play (4); 
    T.displayText("DOMBA", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_AE)>930 && analogRead(btn_AE)<932){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("E");
    lcd.setCursor(5,1);
    lcd.print("ELANG");
    delay(1000);
    mp3_play (5); 
    T.displayText("ELANG", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_AE)>770 && analogRead(btn_AE)<773){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("F");
    lcd.setCursor(5,1);
    lcd.print("FLAMINGO");
    delay(1000);
    mp3_play (6); 
    T.displayText("FLAMINGO", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_AE)>1021 && analogRead(btn_AE)<1023){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("G");
    lcd.setCursor(5,1);
    lcd.print("GAJAH");
    delay(1000);
    mp3_play (7); 
    T.displayText("GAJAH", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_AE)>986 && analogRead(btn_AE)<990){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("H");
    lcd.setCursor(5,1);
    lcd.print("HARIMAU");
    delay(1000);
    mp3_play (8); 
    T.displayText("HARIMAU", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_AE)>512 && analogRead(btn_AE)<514){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("I");
    lcd.setCursor(3,1);
    lcd.print("IKAN PAUS");
    delay(1000);
    mp3_play (9); 
    T.displayText("IKAN PAUS", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_AE)>507 && analogRead(btn_AE)<510){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("J");
    lcd.setCursor(3,1);
    lcd.print("JANGKRIk");
    delay(1000);
    mp3_play (10); 
    T.displayText("JANGKRIK", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}
void FJ(){
    if(analogRead(btn_FJ)>358 && analogRead(btn_FJ)<360){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("K");
    lcd.setCursor(5,1);
    lcd.print("KERA");
    delay(1000);
    mp3_play (11); 
    T.displayText("KERA", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>489 && analogRead(btn_FJ)<500){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("L");
    lcd.setCursor(5,1);
    lcd.print("LALAT");
    delay(1000);
    mp3_play (12); 
    T.displayText("LALAT", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>315 && analogRead(btn_FJ)<317){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("M");
    lcd.setCursor(5,1);
    lcd.print("MONYET");
    delay(1000);
    mp3_play (13); 
    T.displayText("MONYET", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>1020 && analogRead(btn_FJ)<1022){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("N");
    lcd.setCursor(5,1);
    lcd.print("NYAMUK");
    delay(1000);
    mp3_play (14); 
    T.displayText("NYAMUK", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>1022 && analogRead(btn_FJ)<1024){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("O");
    lcd.setCursor(3,1);
    lcd.print("ORANG HUTAN");
    delay(1000);
    mp3_play (15); 
    T.displayText("ORANG UTAN", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>836 && analogRead(btn_FJ)<838){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("P");
    lcd.setCursor(5,1);
    lcd.print("PINGUIN");
    delay(1000);
    mp3_play (16); 
    T.displayText("PINGUIN", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>687 && analogRead(btn_FJ)<689){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("Q");
    lcd.setCursor(5,1);
    lcd.print("QUOKKA");
    delay(1000);
    mp3_play (17); 
    T.displayText("QUOKKA", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>336 && analogRead(btn_FJ)<338){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("R");
    lcd.setCursor(5,1);
    lcd.print("RUSA");
    delay(1000);
    mp3_play (18); 
    T.displayText("RUSA", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>681 && analogRead(btn_FJ)<684){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("S");
    lcd.setCursor(5,1);
    lcd.print("SAPI");
    delay(1000);
    mp3_play (19); 
    T.displayText("SAPI", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  } 
    else if(analogRead(btn_FJ)>1000 && analogRead(btn_FJ)<1002){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("T");
    lcd.setCursor(5,1);
    lcd.print("TOKEK");
    delay(1000);
    mp3_play (20); 
    T.displayText("TOKEK", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>954 && analogRead(btn_FJ)<956){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("U");
    lcd.setCursor(5,1);
    lcd.print("ULAR");
    delay(1000);
    mp3_play (21); 
    T.displayText("ULAR", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>40 && analogRead(btn_FJ)<42){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("V");
    lcd.setCursor(5,1);
    lcd.print("VIKUNA");
    delay(1000);
    mp3_play (22); 
    T.displayText("VIKUNA", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>977 && analogRead(btn_FJ)<979){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("W");
    lcd.setCursor(5,1);
    lcd.print("WALLET");
    delay(1000);
    mp3_play (23); 
    T.displayText("WALLET", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>98 && analogRead(btn_FJ)<100){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("X");
    lcd.setCursor(5,1);
    lcd.print("XENOPS");
    delay(1000);
    mp3_play (24); 
    T.displayText("XENOPS", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>121 && analogRead(btn_FJ)<123){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("Y");
    lcd.setCursor(5,1);
    lcd.print("YUHINA");
    delay(1000);
    mp3_play (25); 
    T.displayText("YUHINA", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
    else if(analogRead(btn_FJ)>1007 && analogRead(btn_FJ)<1009){
    digitalWrite(Buzzer, HIGH);
    delay(200); 
    digitalWrite(Buzzer, LOW); 

    lcd.clear();  
    lcd.setCursor(7,0);
    lcd.print("Z");
    lcd.setCursor(5,1);
    lcd.print("ZEBRA");
    delay(1000);
    mp3_play (26); 
    T.displayText("ZEBRA", PA_CENTER, 50, 50, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}
