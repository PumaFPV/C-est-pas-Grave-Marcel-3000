int pin1 = 12; //up N 
int pin2 = 13; //up 1
int pin3 = 32; //up 2
int pin4 = 33; //up 3
int pin5 = 25; //up 4
int pin6 = 26; //up 5
int pin13 = 21;
int pin7 = 27; //
int pin8 = 14;
int pin9 = 34;
int pin10 = 35;
int pin11 = 17; //up
int pin12 = 16; //up
int pin14 = 0;
int pin15 = 5;



bool beq, oil, grad, left, right;
bool prev_beq, prev_oil, prev_grad, prev_left, prev_right = -1;
int cas, i, speed, prev_speed, light, prev_light = -1;

int temp = 0;

void pins_begin()
{
  
  pinMode(pin1, INPUT_PULLUP);  //N
  pinMode(pin2, INPUT_PULLUP);  //1
  pinMode(pin3, INPUT_PULLUP);  //2
  pinMode(pin4, INPUT_PULLUP);  //3
  pinMode(pin5, INPUT_PULLUP);  //4
  pinMode(pin6, INPUT_PULLUP);  //5
  pinMode(pin13, INPUT_PULLUP);
  pinMode(pin7, INPUT);         //right
  pinMode(pin8, INPUT);         //left
  pinMode(pin9, INPUT);         //road
  pinMode(pin10, INPUT);        //crossing
  pinMode(pin11, INPUT_PULLUP); //oil        
  pinMode(pin12, INPUT); //beq
  pinMode(pin14, INPUT);
  pinMode(pin15, INPUT);
  
}

void read_pins()
{

  if(digitalRead(pin7))
  {
    right = 1;
  }
  else
  {
    right = 0;
  }

  if(digitalRead(pin8))
  {
    left = 1;
  }
  else
  {
    left = 0;
  }

  if(digitalRead(pin9)) //road
  {
    light = 2;
  }
  else if(digitalRead(pin10))  //crossing
  {
    light = 1;
  }
  else
  {
    light = 0;
  }

  if(!digitalRead(pin11))
  {
    oil = 1;
  }
  else
  {
    oil = 0;
  }

  if(!digitalRead(pin12))
  {
    beq = 1;
  }
  else
  {
    beq = 0;
  }

  if(!digitalRead(pin2))
  {
    speed = 1;
    //Serial.println(speed);
  }
  else
  if(!digitalRead(pin3))
  {
    speed = 2;
    //Serial.println(speed);
  }
  else 
  if(!digitalRead(pin4))
  {
    speed = 3;
    //Serial.println(speed);
  }
  else
  if(!digitalRead(pin5))
  {
    speed = 4;
    //Serial.println(speed);
  }
  else
  if(!digitalRead(pin6))
  {
    speed = 5;
    //Serial.println(speed);
  }
  else
  if(!digitalRead(pin1))
  {
    speed = 0;  //N
    //Serial.println(speed);
  }
  
}
