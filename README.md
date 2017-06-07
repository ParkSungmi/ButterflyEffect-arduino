# ButterflyEffect-server
## Software Capstone Design (F028-1) Project

### Title : Touchable Memory
### Team Name : ButterflyEffect

Team Member
====================
+ 201323162 Minjung Sim
+ 201420995 Sungmi Park
+ 201120862 Sungsoo Ahn 
+ 201220920 Ganghyeok Lee

# Discription
The system of this project has server component, arduino component, and android application component.  
This repository is related with arduino component.  
Other repositories URL is as follows:
> server component : https://github.com/ParkSungmi/ButterflyEffect-server  
> android application component : https://github.com/ParkSungmi/ButterflyEffect

This is Arduino Code for Touchable Memory Machine.  
The stored codes are divided into code for transferring the data received from the connected server to Arduino,  
and codes for actually entering the Arduino to move the servo motor and the stepper motor.

# Notice

Requires Node.js.

It works when you run the arduino.js file

The .ino file is placed on the Arduino Board and the .js file is run on the connected computer.

The .ino file only works when receiving data in serial.

 --- causion! ---  
This code requires a computer with an attached board and a serial connection,  
and when running the code, the two connected boards must be connected in serial.

# Function

## Arduino.js

Receives an integer array of 12 x 9 from the server.

Continuously transmit data to the connected add-on board until all the received arrays are executed.

In order to prevent malfunction, the execution time is determined more freely than the time when the motor moves.

## sweep.ino
Requires FS90R Servo Motor(Can be replaced by other 360 ° continuous rotation servo motor)

9 servomotors can be controlled (can be added)

It does not malfunction when it receives 4 bytes of data.  
Number of motor (order required) / direction of rotation (0: clockwise, 1: counterclockwise) / rotation time

Since the time is controlled, a slight error may occur in the rotation angle.

## stepper.ino
Requires 28BYJ-48 Stepper Motor (Can be replaced by other 4-pin stepper motors)  
Requires StepperMulti.h header file

It does not malfunction when it receives 1 bytes of data.  
0 : clockwise, 1 : counterclockwise

Adjust the number of revolutions of the motor by adjusting stepsPerRevolution in the code

The parameter value of setSpeed () should not exceed 60 (it is most likely not to work)

# Reference

Stepper Motor Multi-Control - StepperMulti.h  
http://blog.danggun.net/2092

License
====================
[MIT][License]

[License]: https://en.wikipedia.org/wiki/MIT_License
