//Stuff not to forget:
//1 Meter = 531 clicks
#include <NewPing.h>

#define TRIGGER_PIN  4
#define ECHO_PIN     5
#define MAX_DISTANCE 200

#define TRIGGER_PIN_1  13  
#define ECHO_PIN_1     17
#define MAX_DISTANCE_1 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar_1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE_1);

const int EA = 9; //Left Green
const int EB = 10; //Right Green
const int In1 = 8; //Left Red
const int In2 = 7; //Left Yellow
const int In3 = 12; //Right Red
const int In4 = 11; //Right Yellow

volatile int LeftClicks = 0;
volatile int RightClicks = 0;

void leftmove_counter() {
  LeftClicks ++;
}

void rightmove_counter() {
  RightClicks ++;
}


void setup() { 
  //Initalise all the pins
  Serial.begin(9600);  
  pinMode(EA, OUTPUT); 
  pinMode(EB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  attachInterrupt(0, leftmove_counter, RISING);
  attachInterrupt(1, rightmove_counter, RISING);
  sonar.ping_cm();
}

void left_motor_forwards() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(EA, HIGH);
}

void right_motor_forwards() {
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  digitalWrite(EB, HIGH);
}

void left_motor_reverse() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(EA, HIGH);
}

void right_motor_reverse() {
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(EB, HIGH);
}

void right_kill_switch() {
   digitalWrite(EB, LOW);
   digitalWrite(In3, LOW);
   digitalWrite(In4, LOW);
}

void left_kill_switch() {
  digitalWrite(EA, LOW);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);  
}

void fast_stop() {
  digitalWrite(EA, HIGH);
  digitalWrite(EB, HIGH);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);  
}

//Detects at 200cm 
void detect_object() {
  NewPing(4, 5, 200);
}

  
  
void test_clicks_print() {
    //Test for clicks: 
    Serial.print (LeftClicks);
    Serial.print (",");
    Serial.print (RightClicks);
    Serial.println ();
    delay(10);
}


void ninety_degree_turn_right() {
    //Turn by 90 Degrees right
    LeftClicks = 0;
    while(LeftClicks < 300){
      left_motor_forwards();
      right_kill_switch();
      test_clicks_print();
    } 
    
    fast_stop();
}


void ninety_degree_turn_left() {
    //Turn by 90 Degrees right
    RightClicks =  0;
    while(RightClicks < 150){
      right_motor_forwards();
      left_kill_switch();
      test_clicks_print();
    } 
    
    fast_stop();
}

//--------------------------------------------------------------------------------
//REVERSE FUNCTIONS vvv

void ninety_degree_turn_right_reverse() {
    //Turn by 90 Degrees right
    LeftClicks = 0;
    while(LeftClicks < 300){
      left_motor_reverse();
      right_kill_switch();
      test_clicks_print();
    } 
    
    fast_stop();
}


void ninety_degree_turn_left_reverse() {
    //Turn by 90 Degrees right
    RightClicks =  0;
    while(RightClicks < 300){
      right_motor_reverse();
      left_kill_switch();
      test_clicks_print();
    } 
    
    fast_stop();
}


void direction_correction() 
{
  if (LeftClicks == RightClicks) {
    right_motor_forwards();
    left_motor_forwards();
  }
  if (LeftClicks > RightClicks) {
    left_kill_switch();
    right_motor_forwards();  
  }
  if (RightClicks > LeftClicks) {
    right_kill_switch();
    left_motor_forwards();  
  } 
  
}


//---------------------------------------------------------

void straight_line(int distance) {
   
  RightClicks = 0;  
  LeftClicks = 0;
    right_motor_forwards();
    left_motor_forwards();    
  
    //Corrections to move straight.  
    while(LeftClicks < distance) {
      direction_correction();
    }
}
void straight_line_reverse(int distance) {
   
  RightClicks = 0;  
  LeftClicks = 0;
    right_motor_reverse();
    left_motor_reverse();  
     
    //Corrections to move straight.  
    while(LeftClicks < distance) {
      if (LeftClicks > RightClicks) {
        left_kill_switch();
        right_motor_reverse();  
      }
      if (RightClicks > LeftClicks) {
        right_kill_switch();
        left_motor_reverse();  
      }

    }
}

//-----------------------------------------------------------------------------------//
//--Calling of functions (stage directions)------------------------------------------//

void loop() {

  direction_correction();

  delay(50);
 
  int DistanceDownCM = sonar_1.ping_cm();
  
  if(DistanceDownCM > 13 && DistanceDownCM != 0) {
    fast_stop();
    delay(50);
    straight_line_reverse(169);
    fast_stop();
    while(1);
    }
}

