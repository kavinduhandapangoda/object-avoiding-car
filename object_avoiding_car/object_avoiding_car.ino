/*  object avoiding car
    created by kavindu handapangoda
    2019:03:04
    
*/

  // including servo motor
#include <Servo.h>
Servo servo1;
int servoPin = 10;

  // including wheel motors
#include <AFMotor.h>
AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor2(2, MOTOR12_64KHZ); 

   // define pins to ultrasound sensor
#define trig  9
#define echo  7


void setup() {
    // define pins as input and output
 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);

   // stating data transmission
 Serial.begin(9600);

  // attaching servo to a pin
  servo1.attach(servoPin);
  servo1.write(40);
  delay(1000);
  
}

void loop() {
  
      forward();                  // car is running forward

                                 // checking barriers
     delay(40);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long t=pulseIn(echo, HIGH);
    long cm = (t/2)/29.1;                                   //display distance at serial moniter
    Serial.print(cm);
       
    if (cm > 35){                        // checking distances
      forward();                         // if the distance is large than 35 allow car to run forward
      Serial.println ("forward");
        }
          
     if (cm < 35){
      backward();                        // if the distance is lower than 35, run backward and stop the car 
      delay(500);
      Serial.println ("block");
      st();                              

                                          //getting right distance
      servo1.write(0);
      delay(1000);
     digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long t1=pulseIn(echo, HIGH);
    long cm1 = (t1/2)/29.1;
    Serial.print(cm1);
    Serial.println("right cm ");

                                           //grtting left distance    
      servo1.write(110);
      delay(1000);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long l=pulseIn(echo, HIGH);
    long cm3 = (l/2)/29.1;
    Serial.print(cm3);
    Serial.println("left cm ");
      
      servo1.write(40);

      if (cm1 > 20 ){                     // checking right distance
         Tright();
         Serial.println("Tright");
                                           //turning car right
      }
      else if(cm3 > 20){
        Tleft();                         // checking left distance
        Serial.println("Tleft");
                                         //turning car right
        }
              }
                     }

 //----------------------------------------car moving functions----------------------------------------                    

void backward(){
motor1.setSpeed(100);
motor2.setSpeed(100);

 motor1.run(FORWARD);
 motor2.run(FORWARD);
   }

  void forward(){
motor1.setSpeed(100);
motor2.setSpeed(100);

 motor1.run(BACKWARD);
 motor2.run(BACKWARD);
   }

void Tleft(){
  motor1.setSpeed(100);
  motor2.setSpeed(80);
  
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(200);
   }  

  void Tright(){
  motor1.setSpeed(80);
  motor2.setSpeed(100);
  
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(200);
     }

  void st(){
  motor1.setSpeed(00);
  motor2.setSpeed(00);
    }

