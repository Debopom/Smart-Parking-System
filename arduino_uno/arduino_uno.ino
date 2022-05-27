#include <Servo.h>
#define LDR_PIN 0
#define MAX_ADC_READING 1023
#define ADC_REF_VOLTAGE 5.0
#define REF_RESISTANCE 5030 // measure this for best results
#define LUX_CALC_SCALAR 12518931
#define LUX_CALC_EXPONENT -1.405
#define buttonPin 2
#define rain_input A3
Servo myservo;
Servo myservo1;
#define servoPin 6

int angle = 140;
/****/
/*
Configure the LCD to be 16 char by 2 rows.
Background is set to white.
LCD says
/*****/
/*
Arduino setup function (automatically called at startup)
*/
/*****/
void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Light Sensor Test")); 
  Serial.println("");
  pinMode(buttonPin, INPUT);
  myservo.attach(servoPin);
  
  
  myservo.write(0);
}
/******/
/****/
void loop(void)
{
  
  int ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;
  int button_input=0;
  int buttonState = 0; 
  ldrRawData = analogRead(LDR_PIN);
  buttonState = digitalRead(buttonPin);
  int rainValue=analogRead(rain_input);
  //Serial.println(buttonState);
  // Serial.println(angle);
  
  //resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
  
  //ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
  
  //ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
 
  //ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
  Serial.println(ldrRawData);
  
  //Serial.print("LDR Illuminance: "); Serial.print(ldrRawData); Serial.println(" lux");
while(buttonState==1){
  buttonState = digitalRead(buttonPin);
  if(angle>80){
      myservo.write(angle);
      
      angle--;
      delay(10);
      }
  
}
  

  if (ldrRawData>700&&rainValue>700){
    
    if(angle<=140){
      myservo.write(angle);
      
      
      delay(10);

      angle++;
      }
    
  }
   
  
  else if (ldrRawData<700||rainValue<700){
    if(angle>70){
      myservo.write(angle);
      
      angle--;
      delay(10);
      }
    
  }
  
  
}
