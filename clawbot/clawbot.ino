#include <ezButton.h>
#include <Servo.h>

Servo ServoX;
Servo ServoY;
Servo ServoButton;

int Pin_X = 4;
int Pin_Y = 5;
int Pin_Button = 6;

int joy_X = A0;
int joy_Y = A1;
int sw = 2;

#define LEFT_THRESHOLD 300
#define RIGHT_THRESHOLD 700
#define UP_THRESHOLD 300
#define DOWN_THRESHOLD 700

ezButton button(sw);

void setup()
{
  Serial.begin(9600);
  button.setDebounceTime(50);
  ServoX.attach(Pin_X);
  ServoY.attach(Pin_Y);
  ServoButton.attach(Pin_Button);
}

void loop()
{
  button.loop();
  int val_X = analogRead(joy_X);
  int val_Y = analogRead(joy_Y);
  int swValue = digitalRead(sw);
  int bvalue = button.getState();

  int angle_X = ServoX.read();
  int angle_Y = ServoY.read();
  int angle_Z = ServoButton.read();

  if(val_X < LEFT_THRESHOLD)
  {
    while(angle_X > 0)
    {
      ServoX.write(angle_X);
      angle_X--;
      delay(15);
    }
  }
  
  if(val_X > RIGHT_THRESHOLD)
  {
    while(angle_X < 180)
    {
      ServoX.write(angle_X);
      angle_X++;
      delay(15);
    }
  }
  
  if(val_Y < UP_THRESHOLD)
  {
    while(angle_Y > 0)
    {
      ServoY.write(angle_Y);
      angle_Y--;
      delay(15);
    }
  }
  
  if(val_Y > DOWN_THRESHOLD)
  {
    while(angle_Y < 180)
    {
      ServoY.write(angle_Y);
      angle_Y++;
      delay(15);
    }
  }

  if(button.isPressed())
  {
    while(angle_Z < 180)
    {
      ServoButton.write(angle_Z);
      angle_Z++;
      delay(15);
    }
  }
  if(button.isReleased())
  {
    while(angle_Z > 0)
    {
      ServoButton.write(angle_Z);
      angle_Z--;
      delay(15);
    }
  }
Serial.print("Value X: ");
Serial.println(val_X);
Serial.print("Value Y: ");
Serial.println(val_Y);
Serial.print("Value Z: ");
Serial.println(swValue);

}