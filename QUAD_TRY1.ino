// import pixy and servo libraries 
#include <Pixy2.h>
#include <Servo.h>

// This is the main Pixy object
Pixy2 pixy;

// initialize servos, pin connections and variables for calculating distance
long duration; 
int distance; 

Servo myservo1;
Servo myservo2;

const int trigPin = 9;
const int echoPin = 3; 

// set up attach pins and serial connection 

void setup()
{
  myservo1.attach(6);
  myservo2.attach(5);

  myservo1.write(90);
  myservo2.write(90);

  pixy.init();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 

  Serial.begin(115200);
  Serial.print("Starting...\n");


}

// bool function returns true if distance is within 130 cm, false otherwise 

bool ultraRead() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // CAPITALIZE PIN
  distance = duration * 0.034 / 2;
  Serial.println(distance);

  if (distance < 130) {
    return true; //LOWERCASE TRUE AND FALSE

  }
  else {
    return false;
  }
}


// loop continuously checks ultraread and tests if it returns true, then it checks color and which color 

void loop()
{
  if (ultraRead()){
  int i;
  // grab blocks!
  pixy.ccc.getBlocks();

  // If it detects blocks, detect color 
  if (pixy.ccc.numBlocks) {

    if (pixy.ccc.blocks[i].m_signature == 1) {
      for (int pos = 0; pos <= 180; pos ++) {
        myservo1.write(pos);
        delay(15);
      }

    }

    else if (pixy.ccc.blocks[i].m_signature == 2) {
      for (int pos = 90; pos <= 180; pos ++) {
        myservo2.write(pos);
        delay(15);
      }
    }


  }
}
}
