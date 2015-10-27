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
    
  
void loop() {
  unsigned long starttime = millis();
  
 right_motor_forwards();
 left_motor_forwards();  
  
  while(LeftClicks < 1062) {
    if (LeftClicks > RightClicks) {
    left_kill_switch();
    right_motor_forwards();  
    }
    if (RightClicks > LeftClicks) {
    right_kill_switch();
    left_motor_forwards();  
    }
    
    /* Test for clicks: 
    Serial.print (LeftClicks);
    Serial.print (",");
    Serial.print (RightClicks);
    Serial.println ();
    delay(10);*/
    
  }

  fast_stop();
  while(1);
  
}

