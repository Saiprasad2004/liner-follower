int leftIR = 2;
int rightIR = 4;
int en1 = 5;
int en2 = 6;
int sensor1,sensor2 ,sensor3;
int m1a = 7;
int m1b = 8;
int m2a = 9;
int m2b = 10;
int baseSpeed=80;
int turnSpeed=80;
int error=0;
int kp=15;
int lastError = 0;


void setup(){
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(m1a,OUTPUT);
  pinMode(m1b,OUTPUT);
  pinMode(m2a,OUTPUT);
  pinMode(m2b,OUTPUT);
  pinMode(leftIR,INPUT);
  //pinMode(centerIR,INPUT);
  pinMode(rightIR,INPUT);
  Serial.begin(9600);
  
}

void loop()
{
  sensor1 = digitalRead(leftIR);   // Left sensor
  sensor2 = digitalRead(rightIR);  // Right sensor

  Serial.print(sensor1);
  Serial.print(" ");
  Serial.println(sensor2);

  // Both sensors on white -> line lost
  if(sensor1 == 0 && sensor2 == 0)
  {
    if(lastError > 0)
      right();

    else if(lastError < 0)
      left();

    else
      front();
  }

  // Left sensor on white, Right on black
  else if(sensor1 == 0 && sensor2 == 1)
  {
    error = 1;
    lastError = error;
    right();
  }

  // Left sensor on black, Right on white
  else if(sensor1 == 1 && sensor2 == 0)
  {
    error = -1;
    lastError = error;
    left();
  }

  // Both sensors on black -> robot centered
  else if(sensor1 == 1 && sensor2 == 1)
  {
    error = 0;
    lastError = error;
    front();
  }

  delay(10);
}


void front(){

  analogWrite(en1,baseSpeed);
  analogWrite(en2,baseSpeed);
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  Serial.println("front");
  //delay(15);
}

void right(){
  int speed1=baseSpeed+error*kp;
  int speed2=baseSpeed-error*kp;
  speed1= constrain(speed1,0,150);
  speed2= constrain(speed2,0,150);
  analogWrite(en1,speed1);
  analogWrite(en2,speed2);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  
  digitalWrite(m2a,HIGH);
  digitalWrite(m2b,LOW);
  Serial.print("M1=");
  Serial.print(speed1);

  Serial.print(" M2=");
  Serial.println(speed2);
  Serial.println("right");
  //delay(20);
}

void left(){
  int speed1=baseSpeed-error*kp;
  int speed2=baseSpeed+error*kp;
  speed1= constrain(speed1,0,150);
  speed2= constrain(speed2,0,150);
  analogWrite(en1,speed1);
  analogWrite(en2,speed2);
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);
  
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  Serial.print("M1=");
  Serial.print(speed1);

  Serial.print(" M2=");
  Serial.println(speed2);
  Serial.println("left");
  //delay(20);
}

void stop(){
  analogWrite(en1,0);
  analogWrite(en2,0);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);
  
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,LOW);
  Serial.println("stop");
}

void back (){
  analogWrite(en1,baseSpeed);
  analogWrite(en2,baseSpeed);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,HIGH);
  
  digitalWrite(m2a,LOW);
  digitalWrite(m2b,HIGH);
  Serial.println("back");
}
