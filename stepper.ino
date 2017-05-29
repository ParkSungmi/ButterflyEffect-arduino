#include <StepperMulti.h>
//#include <Stepper.h> 

// 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
#define IN1_1 22
#define IN1_2 24
#define IN1_3 26
#define IN1_4 28

#define IN2_1 34
#define IN2_2 36
#define IN2_3 38
#define IN2_4 40

// 2048:한바퀴(360도), 1024:반바퀴(180도)...
// 1이 오른쪽 0이 왼쪽
int stepsPerRevolution = 370;
int count=0;
//Stepper stepper(stepsPerRevolution, IN1_4, IN1_2, IN1_3, IN1_1);
//Stepper stepper2(stepsPerRevolution, IN2_4, IN2_2, IN2_3, IN2_1);

StepperMulti stepper(stepsPerRevolution, IN1_4, IN1_2, IN1_3, IN1_1);
StepperMulti stepper2(stepsPerRevolution, IN2_4, IN2_2, IN2_3, IN2_1);

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(50);
  stepper2.setSpeed(50);
  
}

void loop() {
  if (Serial.available()) {
    if(Serial.read() == '1'){ // RIGHT
      stepper.setStep(-stepsPerRevolution);
      stepper2.setStep(stepsPerRevolution);
      //Serial.println("right: ");
      //Serial.println(stepsPerRevolution);
      
      if(count>4){
        stepsPerRevolution -=10;
      }else if(count<=4){
        stepsPerRevolution +=15;
      }
      count++;
      
    } else { // LEFT
        if(count>5){
          stepsPerRevolution +=10;
        }else if(count<=5){
          stepsPerRevolution -=15;
        }
        stepper.setStep(stepsPerRevolution);
        stepper2.setStep(-stepsPerRevolution); 
        //Serial.println("left: ");
        //Serial.println(stepsPerRevolution);
        count--;
    }
  }
  stepper.moveStep();
  stepper2.moveStep();
  //delay(1000);
}
