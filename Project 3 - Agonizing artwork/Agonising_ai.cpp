// C++ code
//

// sensor
// FRSPin - pressure sensor
int fsrPin = 0;
int fsrReading;

// emmeter
//Led
int red_led_pin = 6 ;
int green_led_pin = 3;
int blue_led_pin = 5;


// motor
int motor_pin = 11;
// ronrronnement
int motorState = LOW;
long previousStep_green = 0;
long interval_green = 400;

// annoying buzzing
long previousStep_red = 0;
long interval_red = 100;

//piezo buzzer
const int piezo = 10;
// annoying sound
int tone_state = 0;
long previousStep_sound = 0;
long interval_sound = 200;


void setup()
{

 Serial.begin(9600);

  // Led
  pinMode(red_led_pin,OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(blue_led_pin,OUTPUT);

  // motor
  pinMode(motor_pin, OUTPUT);

  //piezo
  pinMode(piezo,OUTPUT);

}

void loop()
{

  digitalWrite(motor_pin, LOW);
  //pressure sensor
  fsrReading = analogRead(fsrPin);


  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // print the raw analog reading

  // To little **************************************
  if (fsrReading < 20) {

    Serial.println(" - No pressure");

    // Led
    analogWrite(red_led_pin, 255);
    analogWrite(green_led_pin, 100);
    analogWrite(blue_led_pin, 0);

    //piezo
      unsigned long currentStep_sound = millis();
  	 if (currentStep_sound - previousStep_sound > interval_sound){
            previousStep_sound = currentStep_sound;
           if ( tone_state == 0) {
                tone_state = 100;
           } else {
                tone_state = 0;
           }
         tone(piezo,tone_state);
      }




  }   else if (fsrReading < 900) {

 // Perfect *****************************************

    Serial.println(" - Medium squeeze");

       // Led
    analogWrite(red_led_pin, 0);
    analogWrite(green_led_pin, 255);
    analogWrite(blue_led_pin, 0);

    // motor
     unsigned long currentStep_green = millis();
  	 if (currentStep_green - previousStep_green > interval_green){
            previousStep_green = currentStep_green;
           if ( motorState == LOW) {
                motorState = HIGH;
           } else {
                motorState = LOW;
           }
         digitalWrite (motor_pin, motorState);
      }
    //piezo
    noTone(piezo);


  } else {

  // Too much ***************************************

    Serial.println(" - Big squeeze");

      	 // Led
    analogWrite(red_led_pin, 255);
    analogWrite(green_led_pin, 0);
    analogWrite(blue_led_pin, 0);

    	// Motor

   unsigned long currentStep_red = millis();
       if (currentStep_red - previousStep_red > interval_red){
          previousStep_red = currentStep_red;
         if ( motorState == LOW) {
              motorState = HIGH;
         } else {
              motorState = LOW;
         }
          digitalWrite (motor_pin, motorState);
       }
    //piezzo
    tone(piezo, 1000);

  }

  delay(1000);

}
