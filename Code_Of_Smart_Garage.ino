byte seg[]={B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11100110};
#include <Servo.h>
#define doorPin 11
#define IR1 13
#define IR2 12
#define LDR A0
#define buzz 9


#define ThermistorPin  A1
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

Servo door;
int previousRead1=1;
int currentRead1=1;
int previousRead2=1;
int currentRead2=1;
int freePlace=0;
int doorPosition=0;


void segment(int i);///name of  function to print free places

void setup()
{
  pinMode(buzz,OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(IR1, INPUT) ;
pinMode(IR2, INPUT) ;
pinMode(ThermistorPin,INPUT);
DDRD=B11111110;
door.attach(doorPin) ;
door. write(doorPosition);
}

void loop()
{



  
Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  
  previousRead1=currentRead1;
currentRead1=digitalRead(IR1) ;
previousRead2=currentRead2;
currentRead2=digitalRead(IR2) ;

if(previousRead1==1&&currentRead1==0) 
{
freePlace++;
}
if(previousRead2==1&&currentRead2==0)
{
freePlace--;
}
if (currentRead1==0||currentRead2==0)
{
for ( ;doorPosition <=100;doorPosition++)
{
door.write(doorPosition);
delay(5);
}
}
else if (currentRead1==1&&currentRead2==1)
{
for(;doorPosition>=0;doorPosition--) 
{
door.write(doorPosition);
delay(5);
} 
}
segment(freePlace);

if(T>=50)
{
  digitalWrite(buzz,HIGH);
}
else
{
  digitalWrite(buzz,LOW);
}

}


void segment(int i)// function to display 
{
 switch(i)
 {
   case 0:
   PORTD=seg[0];
   break;
   case 1:
   PORTD=seg[1];
   break;
   case 2:
   PORTD=seg[2];
   break;
   case 3:
   PORTD=seg[3];
   break;
   case 4:
   PORTD=seg[4];
   break;
   case 5:
   PORTD=seg[5];
   break;
   case 6:
   PORTD=seg[6];
   break;
   case 7:
   PORTD=seg[7];
   break;
   case 8:
   PORTD=seg[8];
   break;
   case 9:
   PORTD=seg[9];
   break;
   
 }
}
