#include <pcmRF.h>
#include <TMRpcm.h>

#include <SD.h>
const int eyesPin = 3;
const int dancePin = 5;
int danceSpeed = 254;
int eyesMin = 10;
int eyesMax = 150;
int eyesBright;
int dancing = 0;
TMRpcm tmrpcm;

void setup ()
{
  pinMode(eyesPin, OUTPUT);
  pinMode(dancePin, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(0, dance, RISING);
  pinMode(10, OUTPUT);
  if(!SD.begin(10))
  {
    Serial.println("SD Error!");
    return;
  }
  tmrpcm.speakerPin = 9;
}

void dance()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200)
  {
    if (dancing == 0)
    {
      dancing = 1;
    } else {
      dancing = 0;
    }
  }
//  Serial.print(dancing);
//  Serial.print(" ");
//  Serial.print(interruptTime);
//  Serial.print(" - ");
//  Serial.println(lastInterruptTime);
  lastInterruptTime = interruptTime;
}

void loop()
{
  while (dancing == 0)
  {
    eyesBright = eyesMin;
    for(eyesBright; eyesBright <= eyesMax; eyesBright++)
    {
      if (dancing == 1)
      {
        break;
      }
      analogWrite(eyesPin,eyesBright);
      delay(10);
//      Serial.print(dancing);
//      Serial.print(" ");
//      Serial.println(eyesBright);
    }
    delay(10);
    for(eyesBright; eyesBright >= eyesMin; eyesBright--)
    {
      if (dancing == 1)
      {
        break;
      }
      analogWrite(eyesPin,eyesBright);
      delay(10);
//      Serial.print(dancing);
//      Serial.print(" ");
//      Serial.println(eyesBright);
    }
    delay(10);
  }
  while (dancing == 1)
  {
    analogWrite(eyesPin,eyesMax);
    tmrpcm.play("music.wav");
    delay(2500);
    analogWrite(dancePin,danceSpeed);
    for (int t = 0; t < 10000; t++)
    {
      if (dancing == 0)
      {
        break;
      }
      delay(10);
    }
    tmrpcm.stopPlayback();
    analogWrite(dancePin,0);
    dancing = 0;
  }
}
  
  
