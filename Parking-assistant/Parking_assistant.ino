//*********************************************************************************
//************************ Define global variables ****************************
//*********************************************************************************
#define trigPin1 13
#define echoPin1 12
#define buzzerPin1 6
#define trigPin2 11
#define echoPin2 10
#define buzzerPin2 7

//*********************************************************************************
// ************ This code will run once at the beginning ********************
//*********************************************************************************
void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(2, OUTPUT);         // We will use the pin 2 as ground. We need to make sure it 
  digitalWrite(2,LOW);             // is in LOW position.
}

//*********************************************************************************
//*** This will iterate as long as there is power applied to the Arduino **
//*********************************************************************************
void loop() {
  calculateDistance(echoPin1, trigPin1,buzzerPin1);  //Get the distance for the left
  calculateDistance(echoPin2, trigPin2,buzzerPin2);  //Get the distance for the right
}

//**********************************************************************************
//***Function to measure time of return of an ultrasound echo.************
//***Set up for distances shorter than 2 m, which is enough for parking** 
//***Beyond that HC-SR04 is not reliable ***********************************
//**********************************************************************************
void calculateDistance(int echo, int trigger, int buzzer){
  long duration, distance;
 
  digitalWrite(trigger, LOW);              // Set the trigger pin of the HC-SR04 to LOW
  delayMicroseconds(2);                   // Wait a little to stabilize the sensor
  digitalWrite(trigger, HIGH);             // Set the trigger HIGH and send a pulse

  delayMicroseconds(10);                 // Wait for 10us till the wave comes back 
  digitalWrite(trigger, LOW);              // Set the trigger pin of the HC-SR04 to LOW again

  duration = pulseIn(echo, HIGH);   // Arduino’s builtin function pulseIn reads a pulse
             // (either HIGH or LOW) on a pin. Returns the length of 
 // the pulse in microseconds or 0 if no complete pulse 
 // was received within the timeout. 

  distance = (duration/2) / 29.1;       // The speed of sound is 340 m/s or 29 microseconds 
// per centimeter. 
// The ping travels out and back, so to find the distance 
// if the object we take half of the distance travelled.

  if (distance >= 200 || distance <= 0){
Serial.println("Out of range");     // Use some feedback in the serial port for 
        // debugging
  }
  else {
    tone(buzzer,2000,25);             // Arduino’s builtin function tone generates a square
               // wave of the specified frequency (2000Hz) for the 
               // indication time (25 ms)
    delay(distance*10);        // The delay gives feedback beeping faster the closer
                    // we get to an object
    Serial.print(distance);    // Use some feedback in the serial port for 
// debugging
    Serial.println(" cm");
  }
}
