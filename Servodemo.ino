#include <Servo.h>
#define ascii 48
#define numOfMotor 9

#define debounce1 210
#define debounce2 300
#define debounce3 50
#define debounce4 100
//1 올리기 0 내리기 1,2,3,4 level
#define pin1 22
#define pin2 24
#define pin3 26
#define pin4 28
#define pin5 30
#define pin6 32
#define pin7 34
#define pin8 36
#define pin9 38

Servo servo[numOfMotor];
int sleep[numOfMotor] = {0, };
unsigned long timer[numOfMotor];
boolean isActive[numOfMotor] = {false, };

void setup() {
  Serial.begin(57600);
  servo[0].attach(pin1);
  servo[1].attach(pin2);
  servo[2].attach(pin3);
  servo[3].attach(pin4);
  servo[4].attach(pin5);
  servo[5].attach(pin6);
  servo[6].attach(pin7);
  servo[7].attach(pin8);
  servo[8].attach(pin9);
  
  for(int i = 0; i < numOfMotor; i++){
    servo[i].write(90);
    timer[i] = millis();
  }
}

int table[numOfMotor] = {0,};
int rotateDirection[numOfMotor] = {0,};
bool onInput = false;
void loop() {
  while(Serial.available() > 0){
    char buf[5];
    Serial.readBytes(buf, 4);
    //int motorNum = buf[1] - ascii;
    int motorNum = (buf[0] - ascii) * 10 + buf[1] - ascii;
    rotateDirection[motorNum - 1] = buf[2] - ascii;
    if(motorNum < numOfMotor + 1 && motorNum > 0)
      table[motorNum - 1] = buf[3] - ascii;
    if(Serial.available() <= 0) onInput = true;
  }
  
  if(onInput){
    for(int i = 0; i < numOfMotor; i++){
      if(table[i] == 0) continue;
      MoveMotor(i, table[i], rotateDirection[i]);
      table[i] = 0;
    }
    onInput = false;  
  }
  
  DebounceCheck();
}

void MoveMotor(int motorIndex, int height, int way){
  int debounce;
  // action
  isActive[motorIndex] = true;
  switch(motorIndex+1){
    case 1:
      switch(height){
        case 1:  debounce = 230;  break;
        case 2:  debounce = 320;  break;
        case 3:  debounce = 40;  break;
        case 4:  debounce = 80;  break;
        default:  debounce = 0;
      }
      if (way == 1) sleep[motorIndex] = debounce;
      else sleep[motorIndex] = debounce;
    break;
    case 2:
      switch(height){
        case 1:  debounce = 260;  break;
        case 2:  debounce = 315;  break;
        case 3:  debounce = 40;  break;
        case 4:  debounce = 80;  break;
        default:  debounce = 0;
      }
      if (way == 1) sleep[motorIndex] = debounce;
      else sleep[motorIndex] = debounce-5;
    break;
    case 3:
      switch(height){
        case 1:  debounce = 220; 
          if (way == 1) sleep[motorIndex] = debounce;
          else sleep[motorIndex] = debounce - 5;
        break; 
        case 2:  debounce = 300;  
          if (way == 1) sleep[motorIndex] = debounce;
          else sleep[motorIndex] = debounce+10;
        break; 
        case 3:  debounce = 40; sleep[motorIndex] = debounce;  break;
        case 4:  debounce = 80; sleep[motorIndex] = debounce;  break;
        default:  debounce = 0; sleep[motorIndex] = debounce;
      }
       
    break;
    case 4:
      switch(height){
        case 1:  debounce = 210;  break;
        case 2:  debounce = 300;  break;
        case 3:  debounce = 50;  break;
        case 4:  debounce = 100;  break;
        default:  debounce = 0;
      }
      if (way == 1) sleep[motorIndex] = debounce;
      else sleep[motorIndex] = debounce - 20; 
    break;
    case 5:
      switch(height){
        case 1:  debounce = 210;  break;
        case 2:  debounce = 300;  break;
        case 3:  debounce = 50;  break;
        case 4:  debounce = 100;  break;
        default:  debounce = 0;
      }
      if (way == 1) sleep[motorIndex] = debounce-10;
      else sleep[motorIndex] = debounce - 20; 
    break;
    case 6:
      switch(height){
        case 1:  debounce = 200;  break;
        case 2:  debounce = 270;  break;
        case 3:  debounce = 20;  break;
        case 4:  debounce = 60;  break;
        default:  debounce = 0;
      }
      if (way == 1) sleep[motorIndex] = debounce;
      else sleep[motorIndex] = debounce+5; 
    break;
    case 7:
      switch(height){
        case 1:  debounce = 210;  break;
        case 2:  debounce = 300;  break;
        case 3:  debounce = 40;  break;
        case 4:  debounce = 80;  break;
        default:  debounce = 0;
      }
      if (way == 1) sleep[motorIndex] = debounce;
      else sleep[motorIndex] = debounce - 5; 
    break;
    case 8:
      switch(height){
        case 1:  debounce = 210;  break;
        case 2:  debounce = 300;  break;
        case 3:  debounce = 40;  break;
        case 4:  debounce = 80;  break;
        default:  debounce = 0;
      }
      if (way == 1) sleep[motorIndex] = debounce;
      else sleep[motorIndex] = debounce; 
    break;
    case 9:
      switch(height){
        case 1:  debounce = 210;  break;
        case 2:  debounce = 300;  break;
        case 3:  debounce = 50;  break;
        case 4:  debounce = 90;  break;
        default:  debounce = 0;
      }
      if (way == 1) sleep[motorIndex] = debounce;
      else sleep[motorIndex] = debounce - 10; 
    break;
  }
  timer[motorIndex] = millis();

  // way가 1이면 오른쪽 회전, 0이면 왼쪽 회전
  //if(motorIndex == 7 || motorIndex == 6 || motorIndex == 5){
    if(way == 1) servo[motorIndex].write(0);
    else servo[motorIndex].write(120); 
  //} else {
  //  if(way == 1) servo[motorIndex].write(180);
  //  else servo[motorIndex].write(0);
  //}
  
  /*
  switch(motorNum){
    case 1:  isActive1 = true; delay1 = debounce; timer1 = millis(); servo1.write(180);  break;
    case 2:  isActive2 = true; delay2 = debounce; timer2 = millis(); servo2.write(180);  break;
    case 3:  isActive3 = true; delay3 = debounce; timer3 = millis(); servo3.write(180);  break;
    case 4:  isActive4 = true; delay4 = debounce; timer4 = millis(); servo4.write(180);  break;
    case 5:  isActive5 = true; delay5 = debounce; timer5 = millis(); servo5.write(180);  break;
    case 6:  isActive6 = true; delay6 = debounce; timer6 = millis(); servo6.write(180);  break;
    case 7:  isActive7 = true; delay7 = debounce; timer7 = millis(); servo7.write(180);  break;
    case 8:  isActive8 = true; delay8 = debounce; timer8 = millis(); servo8.write(180);  break;
    case 9:  isActive9 = true; delay9 = debounce; timer9 = millis(); servo9.write(180);  break;
    case 10:  isActive10 = true; delay10 = debounce; timer10 = millis(); servo10.write(180);  break;
    case 11:  isActive11 = true; delay11 = debounce; timer11 = millis(); servo11.write(180);  break;
    case 12:  isActive12 = true; delay12 = debounce; timer12 = millis(); servo12.write(180);  break;
    case 13:  isActive13 = true; delay13 = debounce; timer13 = millis(); servo13.write(180);  break;
    case 14:  isActive14 = true; delay14 = debounce; timer14 = millis(); servo14.write(180);  break;
    case 15:  isActive15 = true; delay15 = debounce; timer15 = millis(); servo15.write(180);  break;
    case 16:  isActive16 = true; delay16 = debounce; timer16 = millis(); servo16.write(180);  break;
    default:
      Serial.print("error : ");
      Serial.println(motorNum);
  }
  */
}

// debounce
void DebounceCheck(){
  unsigned long mils = millis();
  for(int i = 0; i < numOfMotor; i++){
    if(mils - timer[i] >= sleep[i]){
      isActive[i] = false;
      servo[i].write(90);
    }
  }
}


