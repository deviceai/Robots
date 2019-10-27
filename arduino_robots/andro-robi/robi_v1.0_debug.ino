//Andro-robi v1.0

// Control of 2WD-1 robot platform using Arduino UNO.
// with obstacle avoidance using HC-SR04 ultra sonic sensor.


//SOFTWARE SERIAL FOR BLUETOOTH VARIABLES
#include <SoftwareSerial.h>
SoftwareSerial bluetoothSerial(12, 2); // RX, TX
char bluetoothCommand;

//DISTANCE VARIABLES
const int trigPin = 3;
const int echoPin = 2;
int dist_check1, dist_check2, dist_check3;
long duration, distance, distance_all;
int dist_result;

//MOTORS VARIABLES
const int mot1f = 6;
const int mot1b = 5;
const int mot2f = 11;
const int mot2b = 10;
int mot_speed = 225; //motors speed
int k = 0; //BRAKE

//LOGICS VARIABLES
const int dist_stop = 25;
const int max_range = 800;
const int min_range = 0;
int ErrorLed = 13;

//INITIALIZATION
void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ErrorLed, OUTPUT);
  Serial.println("Initialization...");
}

//BASIC PROGRAM CYCLE
void loop() {
  delay(2000);
  Serial.println("Starting...");
    
if (bluetoothSerial.available() > 0){ 
  digitalWrite(ErrorLed, 0);
  bluetooth_check();
}
else {
  digitalWrite(ErrorLed, 1);
  Serial.println("Error! Bluetooth is not available!");
  delay(3000);
  loop();
}
}

void bluetooth_check(){ 
  Serial.println("Bluetooth is OK, checking...");
bluetoothCommand = bluetoothSerial.read();
    if (bluetoothCommand == 'X'){ //AUTOPILOT
      Serial.println("Going to AUTOPILOT mode...");
      delay(200);
      Serial.println("AUTOPILOT is ON");
      delay(200);
      autopilot();
    }
    if(bluetoothCommand == 'F') { //FORWARD
      motors_forward();
      Serial.print("Going forward ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'B') { //BACK
      motors_back();
      Serial.print("Going back ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'S') { //STOP
      motors_stop();
      Serial.print("STOP! ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'L') { //LEFT
      motors_left();
      Serial.print("Going left ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'R') { //RIGHT
      motors_right();
      Serial.print("Going right ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'G') { //FORWARD LEFT
      motors_foward_left();
      Serial.print("Going forward-left ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'I') { //FORWARD RIGHT
      motors_foward_right();
      Serial.print("Going forward-right ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'H') { //BACK LEFT
      motors_back_left();
      Serial.print("Going back-left ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'J') { //BACK RIGHT
      motors_back_right();
      Serial.print("Going back-right ");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '0') { //SET MOTORS SPEED TO 0
      mot_speed = 0;
      Serial.println("ROBI speed is 0");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '1') { //SET MOTORS SPEED TO 1
      mot_speed = 100;
      Serial.println("ROBI speed is 1");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '2') { //SET MOTORS SPEED TO 2
      mot_speed = 125;
      Serial.println("ROBI speed is 2");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '3') { //SET MOTORS SPEED TO 3
      mot_speed = 150;
      Serial.println("ROBI speed is 3");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '4') { //SET MOTORS SPEED TO 4
      mot_speed = 165;
      Serial.println("ROBI speed is 4");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '5') { //SET MOTORS SPEED TO 5
      mot_speed = 180;
      Serial.println("ROBI speed is 5");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '6') { //SET MOTORS SPEED TO 6
      mot_speed = 195;
      Serial.println("ROBI speed is 6");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '7') { //SET MOTORS SPEED TO 7
      mot_speed = 210;
      Serial.println("ROBI speed is 7");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '8') { //SET MOTORS SPEED TO 8
      mot_speed = 225;
      Serial.println("ROBI speed is 8");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == '9') { //SET MOTORS SPEED TO 9
      mot_speed = 240;
      Serial.println("ROBI speed is 9");
      Serial.println(mot_speed);
    }
    if(bluetoothCommand == 'q') { //SET MOTORS SPEED TO MAX
      mot_speed = 255;
      Serial.println("ROBI speed is 10 (MAX)");
      Serial.println(mot_speed);
    }
else {
  Serial.println("Waiting for command...");
  bluetooth_check();
}

}

void autopilot(){
Serial.print("Checking distance...");
int result = ping(); //Check distance
Serial.println(result);
bluetoothCommand = bluetoothSerial.read(); //Check autopilot OFF/ON
  if (bluetoothCommand == 'x'){
    Serial.println("AUTOPILOT is OFF");
    motors_stop();
    bluetooth_check();
  }
  if (result <= min_range){ //Check min range
    digitalWrite(ErrorLed, 1);
    Serial.println("Error! MIN range!");
    delay(500);
    autopilot();
  }
  if (result == max_range || result > max_range){ //Check max range
    digitalWrite(ErrorLed, 1);
    Serial.println("Error! MAX range!");
    delay(500);
    autopilot();
  }
  if (result == dist_stop || result < dist_stop){ //Check stop range
    digitalWrite(ErrorLed, 0);
    Serial.println("STOP!!!");
   // motors_back();
    delay(1000);
   // motors_stop();
    delay(200);
   // motors_left();
    delay(300);
    //motors_stop();
    delay(200);
    autopilot();
  }
  if (result > dist_stop){ //If all is OK, go forward
    Serial.println("ALL OK, going forward!");
    //motors_forward();
    delay(100);
    autopilot();
 }
else {
Serial.println("AUTOPILOT error!");
delay(2000);
autopilot();
}
}

////***********************FUNCTIONS*******************************\\\\

int ping(){ //CHECK DISTANCE FUNCTION (3x)
  digitalWrite(trigPin, 0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);
  delayMicroseconds(10);
  digitalWrite(trigPin, 0);
  duration = pulseIn(echoPin, 1);
  distance = duration/58;
  
  dist_check1 = distance;
  
  digitalWrite(trigPin, 0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);
  delayMicroseconds(10);
  digitalWrite(trigPin, 0);
  duration = pulseIn(echoPin, 1);
  distance = duration/58;
  
  dist_check2 = distance;
  
  digitalWrite(trigPin, 0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);
  delayMicroseconds(10);
  digitalWrite(trigPin, 0);
  duration = pulseIn(echoPin, 1);
  distance = duration/58;
  
  dist_check3 = distance;
  
  int dist_check_sum;
  dist_check_sum = dist_check1 + dist_check2 + dist_check3;
  dist_result = dist_check_sum/3;
  return dist_result;
}

void motors_forward(){ //MOTORS FORWARD FUNCTION
  analogWrite(mot1f, mot_speed);
  analogWrite(mot2f, mot_speed);
  digitalWrite(mot1b, 0);
  digitalWrite(mot2b, 0);
}
void motors_back(){ //MOTORS BACK FUNCTION
  digitalWrite(mot1f, 0);
  digitalWrite(mot2f, 0);
  analogWrite(mot1b, mot_speed);
  analogWrite(mot2b, mot_speed);
}
void motors_stop() { //MOTORS STOP FUNCTION
  digitalWrite(mot1f, 1);
  digitalWrite(mot2f, 1);
  digitalWrite(mot1b, 1);
  digitalWrite(mot2b, 1);
}
void motors_left() { //MOTORS LEFT FUNCTION
  analogWrite(mot1f, mot_speed);
  digitalWrite(mot2f, 0);
  digitalWrite(mot1b, 0);
  analogWrite(mot2b, mot_speed);
}
void motors_right() { //MOTORS RIGHT FUNCTION
  digitalWrite(mot1f, 0);
  analogWrite(mot2f, mot_speed);
  analogWrite(mot1b, mot_speed);
  digitalWrite(mot2b, 0);
}
void motors_foward_left() { //FORWARD LEFT FUNCTION
k = mot_speed*0.8;
  analogWrite(mot1f, mot_speed);
  analogWrite(mot2f, k);
  digitalWrite(mot1b, 0);
  digitalWrite(mot2b, 0);
}
void motors_foward_right() { //FORWARD RIGHT FUNCTION
k = mot_speed*0.8;
  analogWrite(mot1f, k);
  analogWrite(mot2f, mot_speed);
  analogWrite(mot1b, 0);
  analogWrite(mot2b, 0);
}
void motors_back_left() { //BACK LEFT FUNCTION
k = mot_speed*0.8;
  digitalWrite(mot1f, 0);
  digitalWrite(mot2f, 0);
  analogWrite(mot1b, k);
  analogWrite(mot2b, mot_speed);
}
void motors_back_right() { //BACK RIGHT FUNCTION
k = mot_speed*0.8;
  digitalWrite(mot1f, 0);
  digitalWrite(mot2f, 0);
  analogWrite(mot1b, mot_speed);
  analogWrite(mot2b, k);
}
