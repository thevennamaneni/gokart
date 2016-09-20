#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED
#define BuzzerPin 6
#define echoPin1 4 // Echo Pin
#define trigPin1 5 // Trigger Pin
#define LED1 10

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int incomingByte;   // for incoming serial data
const int RelayPin = 9; // set pin 9 for relay input

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(RelayPin, OUTPUT);
 pinMode(BuzzerPin, OUTPUT);
 pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 
 
 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 Serial.println("-1");
 digitalWrite(LEDPin, HIGH); 
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 Serial.println(distance);
 digitalWrite(LEDPin, LOW); 
 }
 if (distance < 100)
 {
  digitalWrite(BuzzerPin, HIGH);
  digitalWrite(LED1, HIGH);
  
 }
 else if (distance > 100)
 {
  digitalWrite(BuzzerPin, LOW);
  digitalWrite(LED1, LOW);
 }
 //Delay 50ms before next reading.
 //delay(50);
 
  if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                //Serial.print("I received: ");
                //Serial.println(incomingByte);
                if (incomingByte == 1) {
                  digitalWrite(RelayPin, HIGH);
                  Serial.println("Received 1");
                  
                }
                else if (incomingByte == 2) {
                  digitalWrite(RelayPin, LOW);
                  Serial.println("Received 2");
                  }
                else {
                  Serial.println("Received nothing");
                  }
        }
}
