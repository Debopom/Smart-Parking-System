
#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);
String rfidCard;
int stats = 0;
int attempts;
Servo myservo;
#define echoPin 2
#define trigPin 3

#define servoPin 6

long duration; // variable for the duration of sound wave travel
int distance; 


int angle = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting the RFID Reader...");
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  SPI.begin();
  rfid.init();
  myservo.attach(servoPin);
  myservo.write(0);
  pinMode(4, OUTPUT);//rfid green led
  pinMode(7, OUTPUT);//ultrasound led
   pinMode(8, OUTPUT);
   digitalWrite(8,LOW);
}
void loop() {
    String card = "169 9 84 211";
     String master1="234 103 207 46";
     String master2="249 31 212 43";
  
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {      
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      delay(10);
      Serial.println(rfidCard);
      if (rfidCard == card||rfidCard == master1||rfidCard == master2 ) {
        if(stats == 0){
          stats = 1;
          digitalWrite(4, HIGH);
          delay(500);
          digitalWrite(4, LOW);
          Serial.println("open");
          for (angle = 0; angle <= 90; angle += 1) {
             myservo.write(angle);
             delay(10);
          }
          
        }
        else{
          stats = 0;
          Serial.println("closed");
          digitalWrite(4, HIGH);
          delay(500);
          digitalWrite(4, LOW);
          for (angle = 90; angle >= 0; angle -= 1) {
              myservo.write(angle);
              delay(10);
          }
          
        }
        
        
        
      } else {
        digitalWrite(8, HIGH);
        delay(100);
        digitalWrite(8, LOW);
        delay(100);
        digitalWrite(8, HIGH);
        delay(100);
        digitalWrite(8, LOW);
        delay(100);
        digitalWrite(8, HIGH);
        delay(100);
        digitalWrite(8, LOW);
        delay(100);
        attempts++;
        if(attempts>=3){
          Serial.println("Chotolok, bikechor");
          digitalWrite(8, HIGH);
          delay(5000);
          digitalWrite(8, LOW);
          attempts = 0;
        }
        
      }
    }
    
  }
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
   if(distance<5){
    digitalWrite(7, HIGH);
  }
  else{
    digitalWrite(7, LOW);
    }

  
    
}
