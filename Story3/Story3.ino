
int EA = 9; //Left Green
int EB = 10; //Right Green
int In1 = 8; //Left Red
int In2 = 7; //Left Yellow
int In3 = 12; //Right Red
int In4 = 11; //Right Yellow

void setup() { 
  //Initalise all the pins  
  pinMode(EA, OUTPUT); 
  pinMode(EB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
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
    
    
    
void loop() {
  //Forward 10 seconds
  right_motor_forwards();
  left_motor_forwards();
  delay(10000);
  //Turn off the motors for 1 second
  left_kill_switch();
  right_kill_switch();
  delay(1000);
  //Reverse 1 second
  left_motor_reverse();
  right_motor_reverse();
  delay(1000);
  //Turn off everything
  left_kill_switch();
  right_kill_switch();
  while (1); 
}
