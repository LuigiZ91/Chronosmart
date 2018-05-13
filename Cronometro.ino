#include <f401reMap.h>
#include <SPI.h>   
// pinNucleo = pinArduinio + 1, nel programma bisogna inserire i pin dell'arduino  
const int triggerPort1 =  pinMap(7); 
const int echoPort1 = pinMap(1); 
const int triggerPort2 = pinMap(6);
const int echoPort2 = pinMap(3); 
const int led =  pinMap(12);
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


float temp = 0;   
boolean isConnected = false;    
char messaggio[30]; 
char c;   

void setup() 
{
pinMode(triggerPort1, OUTPUT);
pinMode(echoPort1, INPUT);
pinMode(triggerPort2, OUTPUT);
pinMode(echoPort2, INPUT);

Serial.begin(9600);   

}

void loop() 
{
  
  if (flagA == 1) //flag che attiva il sistema tramite app, il sistema "vede"
  {
    
   //porta bassa l'uscita del trigger
   digitalWrite( triggerPort1, LOW );
   //invia un impulso di 10microsec su trigger
   digitalWrite( triggerPort1, HIGH );
   delayMicroseconds( 10 );
   digitalWrite( triggerPort1, LOW );
   long durata1 = pulseIn(echoPort1, HIGH );
    digitalWrite(led, HIGH);
   if ( durata1 < 1000) // quando il sensore non vede più attiva il FlagB
   {
    flagB = 1;
    flagA = 0;
      Serial.println("Cronometro avviato");
      Serial.println("\n");
      
      
    if (flagB == 1) // quando non vede più e il flagB è attivo, parte il crono
     {
      tempo_base = millis();
      flagB = 0;
      flagC = 1;
      tempoBaseSec= tempo_base/1000;
      Serial.println("Inizio:   ");
      Serial.print(tempoBaseSec); 
      Serial.println("\n");
      digitalWrite(led, LOW);
 
     
     }
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
   tempoI = millis();
   tempoF = tempoI/1000;
   Serial.println("Fine:");
   Serial.print(tempoF); 
   Serial.println("\n");
   tempo = tempoI - tempo_base;
   tempoCronometrato = tempo/1000;
   flagC = 0; 
   Serial.println("Tempo:");
   Serial.print(tempoCronometrato); 
   Serial.println("\n");
 }

  
}
}
