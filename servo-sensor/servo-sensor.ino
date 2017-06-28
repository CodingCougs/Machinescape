#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position
float deg = 0.0;
float inc = 0.06;   // Moter Incrementer
boolean forward =  true;
boolean goodToGo = false;
long target = 5;
long values[3] = {-1, -1, -1};

//PIN Definitions
const int trigPin = 6;
const int echoPin = 7;
const int servoPin = 9;
#define aggressive 3;
#define afraid 2;
#define calm 1;

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 

  debug("Inital Value: ");

  // Set Motor to starting state
  if ( myservo.read() != 0) {
    myservo.write(0);
  }

  debug("Motor Should be 0, reads: ");

}

void loop() {
  long inches;
  inches = checkEnv();
  
  checkErrors(inches);

} 

void debug(String msg){
    Serial.print(msg);
    Serial.println( myservo.read());
}

long checkEnv(){
  
  long duration, inches, cm;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Converts microseconds to inches and cm
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  // Prints output
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  return inches;
}

void checkErrors(long value){
  int i;
  
  int castedTarget;
  castedTarget = (int) target;
    
    if(values[0] == -1){
      target = value;
      values[0] = target;
    }    
    else if((value >= target-1) && (value <= target+1)){

      for (i = 1;  i < 3; i++){

        if(values[i] == -1){
          values[i] = value;
        }
      }
    }
    else{
      //Clear array
      memset(values,-1,sizeof(values));
    }
  
    servorState();

 }

 
 void servorState(){
  long inches;
  if(values[2] != -1){
    inches = target;
    
   if (inches <= 12 && inches >= 0) {
    // Aggressive
    Move( 0, 160, 10);
     
  } else if (inches > 12 && inches <= 24) {
    // Scared
    Move(30,60, 3.5);
   
  } else {
    // Default (Relaxed)
    Move( 110, 140, 1);  
     
      }
   memset(values,-1,sizeof(values)); 
    }
 }


long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void Move( int lowerRange, int UpperRange, float inc){

  pos = myservo.read();

  if (forward){
    //debug("Pos is: ");
    deg += inc;
    myservo.write(deg);
  }

  if (deg >= UpperRange) {
    forward = false;
    deg = UpperRange;
    myservo.write(deg);
  }

  if (!forward) {
    //debug("Pos is: ");
    deg -= inc;
    myservo.write(deg);
  }

  if (deg <= lowerRange) {
    forward = true; 
    deg = lowerRange;
    myservo.write(deg);
  }
 
}