#include <f401reMap.h>
#include <SPI.h>   
// pinNucleo = pinArduinio + 1, nel programma bisogna inserire i pin dell'arduino  
const int triggerPort1 =  pinMap(7); 
const int echoPort1 = pinMap(1); 
const int triggerPort2 = pinMap(6);
const int echoPort2 = pinMap(3); 
const int led1 =  pinMap(12);
const int led2 =  pinMap(11);
int flagA = 1;
int flagB = 0;
int flagC = 0;
long durata1=0;
float tempo_base;
float tempo;
float tempoCronometrato; 
float tempoBaseSec;
float tempoI;
float tempoF;


void setup() 
{
pinMode(triggerPort1, OUTPUT);
pinMode(echoPort1, INPUT);
pinMode(triggerPort2, OUTPUT);
pinMode(echoPort2, INPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
Serial.begin(9600);   

}

void loop() 
{
  delayMicroseconds( 100 );
  if (flagA == 1) //flag che attiva il sistema tramite app, il sistema "vede"
  {  
   digitalWrite( triggerPort1, LOW );
   digitalWrite( triggerPort1, HIGH );
   delayMicroseconds( 10 );
   digitalWrite( triggerPort1, LOW );
   long durata1 = pulseIn(echoPort1, HIGH );
   if (durata1 < 1000) // quando il sensore vede inizialmente 
   {
      flagA = 0;
      Serial.println("I detect, when I stop detecting, the chronometer starts");
      Serial.println("\n");
      digitalWrite(led1, HIGH); 
      while (flagB==0)
      {
        delayMicroseconds( 10000);
        digitalWrite( triggerPort1, LOW );
        digitalWrite( triggerPort1, HIGH );
        delayMicroseconds( 10 );
        digitalWrite( triggerPort1, LOW );
        durata1 = pulseIn(echoPort1, HIGH );
       
        if (durata1 > 1000)
        {
          digitalWrite(led1, HIGH);
          flagB=1;
         }
            
      }
      
      tempo_base = millis();
      flagB = 0;
      flagC = 1;
      tempoBaseSec= tempo_base/1000;
      Serial.println("Begin:   ");
      Serial.print(tempoBaseSec); 
      Serial.println("\n");
      digitalWrite(led1, LOW);
    }
   }

if (flagC == 1)
 {
  digitalWrite( triggerPort2, LOW );
  digitalWrite( triggerPort2, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort2, LOW );
  long durata2 = pulseIn(echoPort2, HIGH );
  if (durata2 < 1000)
  {
   digitalWrite(led2, HIGH);
   tempoI = millis();
   tempoF = tempoI/1000;
   Serial.println("End:");
   Serial.print(tempoF); 
   Serial.println("\n");
   tempo = tempoI - tempo_base;
   tempoCronometrato = tempo/1000;
   flagC = 0; 
   Serial.println("Time:");
   Serial.print(tempoCronometrato); 
   Serial.println("\n");
   flagA = 1;
   
 } 
}
delay(500);
digitalWrite(led2, LOW);

}
