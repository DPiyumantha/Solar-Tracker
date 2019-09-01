//******************************
//  Group B
//  Solar Tracker
//
//  Submitted by:
//
//  AS2016938 : KADP Perera
//  AS2016920 : MGC Janaranga
//  AS2016917 : SGVST Gunasekara
//*******************************


#include <Servo.h> 


Servo horizontal , vertical; 
int ThermistorPin = A5;
int Vo; //Thermistor reading
float R1 = 220; //Resistor that we used
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int servoh = 90;  //initial position horizontal 

int servohLimitHigh = 180;
int servohLimitLow = 65;


  
int servov = 45;   //initial position vertical  

int servovLimitHigh = 80;
int servovLimitLow = 15;



int ldrlt = A3; 
int ldrrt = A4; 
int ldrld = A0; 
int ldrrd = A1; 

void setup()
{
  Serial.begin(9600);

  horizontal.attach(10); 
  vertical.attach(9); 

  horizontal.write(90);
  vertical.write(45);

  delay(3000);
}

void loop() 
{
  int lt = analogRead(ldrlt); 
  int rt = analogRead(ldrrt); 
  int ld = analogRead(ldrld); 
  int rd = analogRead(ldrrd); 
  
  
  int dtime = 10;
  int tol = 10;// Decides how much difference should be considered to turn the cell

  //Reading the temperature
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
 

  Serial.print("Temperature: "); 
  Serial.print(Tc);
  Serial.println(" C");
  

  
  int avt = (lt + rt) / 2; // average value top
  int avd = ld; // average value down
  int avl = (rd + ld) / 2; // average value left
  int avr = rt; // average value right

  int dvert = avt - avd; 
  int dhoriz = avl - avr;
  
 
  
    
  if(Tc>65){
    horizontal.write(servohLimitLow);
    vertical.write(servovLimitLow);
  }else{
    if (-1*tol > dvert || dvert > tol) 
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd) //Check if the top intensity is less than the down intensity
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) 
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr) //Check if the left intensity is less than the right intensity
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    
  }
  horizontal.write(servoh);
  }
  }
  
  
  
   delay(dtime);

}
