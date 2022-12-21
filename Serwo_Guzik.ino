#include <LiquidCrystal.h>
#include <Servo.h>

#define triggerPin 8
#define echoPin 9
#define DiodaLed 13;
#define wyzerowanie 0
#define ServoPin 10
#define Button 11

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
Servo serwomechanizm_1;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  serwomechanizm_1.attach(Button);
  serwomechanizm_1.write(0);
}

long int odleglosc(){
  long int czas, dystans;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58;
  return dystans;
}

void wyswietlanie_lcd(){
  long dystans;
  dystans = odleglosc();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Odle wynosi:");
  lcd.setCursor(0, 1);
  if(dystans < 50)
  {
    lcd.print(dystans);
    lcd.print(" cm");
  }
  else 
    lcd.print("Za daleko!");
}

void loop() {
  long int dystans;
  hile(digitalRead(Button) == HIGH){}
  dystans = odleglosc();
  if(dystans > 50)
  {
    Serial.println("Za daleko!");
    Serial.println("----------");
  }
  else
  {
    Serial.print(dystans);
    Serial.println(" cm");
    Serial.println("----------");
  }
  wyswietlanie_lcd();
}
