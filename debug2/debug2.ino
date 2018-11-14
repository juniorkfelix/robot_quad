
int ENA = 10; // MCU PWM Pin 10 to ENA on L298n Board
int IN1 = 9;  // MCU Digital Pin 9 to IN1 on L298n Board 
int IN2 = 8;  // MCU Digital Pin 8 to IN2 on L298n Board
 
int ENB = 5;  // MCU PWM Pin 5 to ENB on L298n Board
int IN3 = 7;  // MCU Digital pin 7 to IN3 on L298n Board
int IN4 = 6;  // MCU Digital pin 6 to IN4 on L298n Board

int ledPin = 13;  // use the built in LED on pin 13 of the Uno
int state = 0;
int flag = 0;        // make sure that you return the state only once

int ledpin1 = 11;
int ledpin2 = 12;

//sonar sensor
// defines pins numbers
const int trigPin = 4;
const int echoPin = 3;
const int buzzer = 2;

// defines variables
long duration;
int distance;
int safetyDistance;

void setup() {
    pinMode(ENA, OUTPUT); //Set all the L298n Pin to output
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    // sets the hc-06 pins as outputs:
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(buzzer, OUTPUT);

    pinMode(ledpin1, OUTPUT);
    pinMode(ledpin2, OUTPUT);

safetyDistance = 30;

    Serial.begin(9600); // Default connection rate for my BT module
}
void DRIVESTOP()
{
  digitalWrite(IN1, LOW); // Turn the motor off
  digitalWrite(IN2, LOW); // Turn the motor off  
  digitalWrite(IN3, LOW); // Turn the motor off
  digitalWrite(IN4, LOW); // Turn the motor off  
}
void sonar()
{
  int dist = ultrasonic();

if (dist <= safetyDistance){
  tone(buzzer, 2500);
  delay(500);
  tone (buzzer, 2500);  
}
else{
  noTone (buzzer);
}

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(dist);
delay(200);
}

int ultrasonic(){
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

return distance;
}
void DRIVEONE()//reverse motion
{
  /*
 These function will turn the motors on the possible speeds, the maximum speed turns is determined
 by the motor specs and the operating voltage. The PWM(Pulse with modulation values will sent
 by analogWrite() function to drive the maxim speed. 
*/
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  sonar();
 
  for (int x = 0; x < 256; x++)   // Motor will accelerate from 0 to maximum speed
  {
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
    //delay(20);
  } 
}

void DRIVETWO()//foward motion
{
/*
 These function will turn the motors on the possible speeds, the maximum speed turns is determined
 by the motor specs and the operating voltage. The PWM(Pulse with modulation values will sent
 by analogWrite() function to drive the maxim speed. 
*/
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  sonar();
 
  for (int x = 0; x < 256; x++)   // Motor will accelerate from 0 to maximum speed
  {
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
    //delay(20);
  } 
 

}
void DRIVELEFT()
{
/*
 These function will turn the motors on the possible speeds, the maximum speed turns is determined
 by the motor specs and the operating voltage. The PWM(Pulse with modulation values will sent
 by analogWrite() function to drive the maxim speed. 
*/
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
 
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(ledpin1,HIGH);
  delay(1000);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  digitalWrite(ledpin1,LOW);
  
    sonar();
  
 

}
void DRIVERIGHT()
{
/*
 These function will turn the motors on the possible speeds, the maximum speed turns is determined
 by the motor specs and the operating voltage. The PWM(Pulse with modulation values will sent
 by analogWrite() function to drive the maxim speed. 
*/
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW); 
 
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(ledpin2,HIGH);
  delay(1000);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  digitalWrite(ledpin2,LOW);
  sonar();
    
  
 

}

void loop() {
    //if some data is sent, read it and save it in the state variable
    
    if(Serial.available() > 0){
      state = Serial.read();
      flag=0;
    }
    // if the state is 0 the led will turn off
    if (state == '0') {
       digitalWrite(ledPin, LOW);
        DRIVESTOP();
        if(flag == 0){
          Serial.println("LED: off");
          flag = 1;
        }
    }
    // if the state is 1 the led will turn on
    else if (state == '1') {
        digitalWrite(ledPin, HIGH);
       DRIVETWO();
        if(flag == 0){
          Serial.println("LED: on");
          flag = 1;
        }
    }
     // if the state is 1 the led will turn on
    else if (state == '2') {
        digitalWrite(ledPin, HIGH);
       DRIVEONE();
        if(flag == 0){
          Serial.println("LED: on");
          flag = 1;
        }
    }
      // if the state is 1 the led will turn on
    else if (state == '3') {
        digitalWrite(ledPin, HIGH);
       DRIVELEFT();
        if(flag == 0){
          Serial.println("LED: on");
          flag = 1;
        }
    }
     else if (state == '4') {
        digitalWrite(ledPin, HIGH);
       DRIVERIGHT();
        if(flag == 0){
          Serial.println("LED: on");
          flag = 1;
        }
    }
    sonar();
}
