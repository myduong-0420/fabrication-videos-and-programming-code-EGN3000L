//Install Ultrasonic library ver 3.0.0.

#include <Ultrasonic.h> /*This calls upon the library for the Ultrasonic sensor*/

Ultrasonic ultrasonic (9, 10);/*The Trig pin is pin 9 and the Echo pin is pin 10. It also gives the sensor a name. In this case, the name is ultrasonic.*/

const int right_irsensor = 8;/*The right IR sensor is connected to pin 8.*/
const int left_irsensor = 7; /*The left IR sensor is connected to pin 7.*/
const int motor_rightFront = 3;/*the wire of the right motor which controls its forward motion is connected to pin 3*/
const int motor_rightBack = 2;/*the wire of the right motor which controls its backward motion is connected to pin 2*/
const int motor_leftFront = 5; /*the wire of the left motor which controls its forward motion is connected to pin 5*/
const int motor_leftBack = 4; /*the wire of the left motor which controls its backward motion is connected to pin 4*/
const int en_left = 6; /* define the pin number of the speed control for the left motor as pin 6 */
const int en_right = 11; /* define the pin number of the speed control for the left motor as pin 11*/
int motorSpeed_right = 100; // Set the motor speed of the right motor as 100
int motorSpeed_left = motorSpeed_right*2; // Set motor speed of the left motor to be twice that of the right motor 
int x; /*define x and y as integer pin variables */
int y;


void setup() {
/* the void setup function only runs once throughout the whole program:*/
Serial.begin(9600);
for(x = 2; x<6; x++){ /*This is a basic for loop that iterates through all integer values of x from 2 to (and including) 5. This means that pin x starts at 2 and increases by 1 each time and remains less than 6. In other words, pins 1 to 5, which are the pins for motor control.*/
pinMode(x, OUTPUT);/*Then, declare x as an output. The pinMode()function is used to do this. In short, pins 2 to 5 are outputs. This makes sense   since motors are control devices, to which commands are given.*/
}
for(y=7; y<9 ; y++){
pinMode(y, INPUT);/*Declare y as the input. Again, the for loop iterates through all integer values of y from 7 to 8 including 8, so the 2 IR sensor pins 7 and 8 are inputs. The sensors give values, so this also makes sense.*/
}
pinMode(en_left, OUTPUT);
pinMode(en_right, OUTPUT);
}


void right(){  //void is used to define functions. This function will make the robot turn right.
/*digitalWrite() is used to make things work or stop based on digital signals given to it in the form of HIGH and LOW.HIGH is to make something work while LOW is to stop it.*/
digitalWrite(motor_rightFront,LOW); //make the right motor stop moving forward
digitalWrite(motor_rightBack,LOW); //make the right motor stop moving backward
digitalWrite(motor_leftFront,LOW); //make the left motor stop moving forward
digitalWrite(motor_leftBack,HIGH); //make the left motor stop moving backward
}


void left(){
digitalWrite(motor_rightFront, LOW);
digitalWrite(motor_rightBack, HIGH);
digitalWrite(motor_leftFront, LOW);
digitalWrite(motor_leftBack, LOW);
}


void forward(){
digitalWrite(motor_rightFront, LOW);
digitalWrite(motor_rightBack,   HIGH);
digitalWrite(motor_leftFront, LOW);
digitalWrite(motor_leftBack, HIGH);
}


void backward(){
digitalWrite(motor_rightFront, HIGH);
digitalWrite(motor_rightBack, LOW);
digitalWrite(motor_leftFront, HIGH);
digitalWrite(motor_leftBack, LOW);
}


void yay(){ //This is to make the robot stop. stop is a function on its own, so this function cannot be named ‘stop’.
digitalWrite(motor_rightFront, LOW);
digitalWrite(motor_rightBack, LOW);
digitalWrite(motor_leftFront, LOW);
digitalWrite(motor_leftBack, LOW);
}

void loop() {
/* This is where the main code is put, so it runs over and over in the program. That is why it is called a loop.*/
analogWrite(en_right, motorSpeed_right); // set up the speed for the right motor
analogWrite(en_left, motorSpeed_left); // set up the speed for the left motor
int right_sensor = digitalRead(right_irsensor);/*declaring the variable called right_sensor to take the reading from the right IR sensor. We are using digitalRead() since it is only a white and black surface. It will read LOW for black and HIGH for white.*/
int left_sensor = digitalRead(left_irsensor);
int reading = ultrasonic.read();/*Declaring a variable for the Ultrasonic sensor to read. Here, the name given to the sensor at the beginning has to be used for the command, hence, ultrasonic.read()*/
/* Here, we need the conditional statements to instruct the robot on when to perform which movements. */
if(reading>29){ /*If the reading is more than 29 cm, meaning an obstacle is more than 29 cm away from the sensor, then the robot can run.*/
if(right_sensor == HIGH && left_sensor == LOW){  /*The right sensor detects white and the left sensor detects black.*/
left();  /*If this condition is met, the robot turns left.*/
}

/* the 3 following if statements are similar in performing their corresponding movements */
if(right_sensor == LOW && left_sensor == HIGH){
right();
}

if(right_sensor == LOW && left_sensor == LOW){
yay(); /*if it is not more than 29 cm, then the robot will stop. yay() is defined as a function for the robot to stop as below. */
}

if(right_sensor == HIGH && left_sensor == HIGH){
forward();
}
}

else{  /* This else statement corresponds with the if(reading>29), meaning that if reading<29, the robot will also stop.*/
yay();
}
}

