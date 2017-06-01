
#include <Servo.h> 
 
 const int trigPin = 6;
 const int echoPin = 7;

 // create servo object to control a servo
 // a maximum of eight servo objects can be created
Servo myservo; 
                 
// variable to store the servo position 
int pos = 0;    

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
// attaches the servo on pin 9 to the servo object
  myservo.attach(9);  
  
}

void loop()
{

  long duration, inches, cm;
  
 
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  //Tell the Arduino to print the measurement in the serial console
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  // This if-else statement tells the Arduino at what distance 
  // it should trigger the servo, what the servo should do,
  // and what it should do if the distance is too far away.
   if (inches <= 24)  {sweep(2);
     
   }
   else if (inches >= 24) {myservo.write(pos);
   }
   
   // Tell the Arduino to wait 0.10 seconds before pinging the 
   // Ultrasonic Sensor again.
   delay(100);
}

// Converts the microseconds reading to Inches
long microsecondsToInches(long microseconds)
{

  return microseconds / 74 / 2;
}

//Converts the Microseconds Reading to Centimeters
long microsecondsToCentimeters(long microseconds)
{

  return microseconds / 29 / 2;
}

//This sub-routein is what dictates the movement of the servo
void sweep(int NUM_OF_CYCLES) 
  
{ 
// Tells the Arduino to start this loop at 0 and incriment it by 1
// each time the loop completes. This is how the Arduino knows to 
// stop the loop when a specific number of the Sweep routein has been ran.
  for (int j=0; j<NUM_OF_CYCLES; j++)
   
 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

} 
