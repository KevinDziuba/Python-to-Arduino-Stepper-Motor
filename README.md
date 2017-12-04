# Python-to-Arduino-Stepper-Motor

Goal: Moving a stepper motor based on direction and number of steps by
communicating arduino with python.
---------------------------------------------------------------------------------------------

Files:

1) ARDUINOPYTHONMOTOR.py - Python code that contains communication with Arduino and list
2) ModifiedMotor_Final.ino - current arduino code that reads list and moves stepper motors accordingly
3) FriendSuggestion.ino - Showed friend my problem and he made some changes. STILL NEED TO TEST

Background:

Python initially has a list that contains ["<Direction, Number of Steps>"]
where direction is either "Forward", "Left", or "Right" and steps can be any integer value.
Python communicates these values with Arduino via serial communication and uses
the direction string to call a motor function that goes straight, turns left or turns right
and uses the number of steps value to move the stepper motors that many steps.

Sequence of Steps:
1) Communication of data from python ["<Direction, Number of Steps>"] to Arduino
2) Talk to Python kernel so that I can see what data it is receiving
3) Run motor code based on direction and number of steps

-----------------------------------------------------------------------------------------------------------------------
References:
Most of the code is a modified version of Robin2's demo found here:
http://forum.arduino.cc/index.php?topic=225329.msg1810764#msg1810764



