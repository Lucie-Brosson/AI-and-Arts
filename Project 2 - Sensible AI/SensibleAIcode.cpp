// C++ code
//
//LCD screen
#include <LiquidCrystal.h>

//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 3;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Poem
String poem[] = {"Hello","I am here","how are you","good and you"};
long previousStep_text = 0;
long interval_text = 500;
int a = 0;

// Led
const int red_led = 10;
const int orange_led = 9;
const int green_led = 8;

// for blinking orange led
int lightState = LOW;
long previousStep = 0;
long interval = 300;

//button
const int death_button = 6;
int button_state = 0;



void setup()
{
  Serial.begin(9600);

  pinMode(red_led, OUTPUT);
  pinMode(orange_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  pinMode(death_button,INPUT);

   lcd.begin(16, 2);
  // Print a message to the LCD.

}

void loop()
{


  digitalWrite(orange_led, HIGH);

  unsigned long currentStep = millis();
  if (currentStep - previousStep > interval){
     previousStep = currentStep;
     if ( lightState == LOW) {
         lightState = HIGH;
     } else {
         lightState = LOW;
     }
     digitalWrite (red_led, lightState);
   }


  button_state = digitalRead(death_button);


  for(int i = 0; i < 4; i++){

   unsigned long currentMillis = millis();

   if(currentMillis - previousStep_text > interval_text) {
    	previousStep_text = currentMillis;

		lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(poem[a]);
        lcd.setCursor(0, 1);
        lcd.print(poem[a+1]);

        Serial.println(a);
      	a++;

     }
  }


  //button
   if (button_state == HIGH){
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Thank you");
     digitalWrite (orange_led, LOW);
     digitalWrite (red_led, HIGH);

     delay(300);
     lcd.clear();
     digitalWrite (red_led, LOW);
     exit(0);
   }

}
