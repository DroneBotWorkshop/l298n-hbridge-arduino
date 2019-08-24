/*
  L298N 4 Motor Control with Joystick
  L298N-4-Motor-Control-Joystick.ino
  Control 4 motors with 2 L298N controllers

  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Motor A

int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B

int enB = 3;
int in3 = 5;
int in4 = 4;

// Motor C

int enC = 10;
int in12 = 1;
int in22 = 2;

// Motor D

int enD = 11;
int in32 = 12;
int in42 = 13;

// Joystick 1 Input

int joyVert = A0; // Vertical
int joyHorz = A1; // Horizontal

// Joystick 2 Input

int joyVert2 = A2; // Vertical
int joyHorz2 = A3; // Horizontal


// Motor Speed Values - Start at zero

int MotorSpeed1 = 0;
int MotorSpeed2 = 0;
int MotorSpeed3 = 0;
int MotorSpeed4 = 0;

// Joystick Values - Start at 512 (middle position)

int joyposVert = 512;
int joyposHorz = 512;
int joyposVert2 = 512;
int joyposHorz2 = 512;


void setup()

{

  // Set all the motor control pins to outputs

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(enD, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in12, OUTPUT);
  pinMode(in22, OUTPUT);
  pinMode(in32, OUTPUT);
  pinMode(in42, OUTPUT);


  // Start with motors disabled and direction forward

  // Motor A

  digitalWrite(enA, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Motor B

  digitalWrite(enB, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Motor C

  digitalWrite(enC, LOW);
  digitalWrite(in12, HIGH);
  digitalWrite(in12, LOW);

  // Motor D

  digitalWrite(enD, LOW);
  digitalWrite(in32, HIGH);
  digitalWrite(in42, LOW);

}

void loop() {

  // Read the Joystick X and Y positions

  joyposVert = analogRead(joyVert);
  joyposHorz = analogRead(joyHorz);

  // Determine if this is a forward or backward motion
  // Do this by reading the Verticle Value
  // Apply results to MotorSpeed and to Direction

  if (joyposVert < 460)
  {
    // This is Backward

    // Set Motor A backward

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    // Set Motor B backward

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    //Determine Motor Speeds

    // As we are going backwards we need to reverse readings

    joyposVert = joyposVert - 460; // This produces a negative number
    joyposVert = joyposVert * -1;  // Make the number positive

    MotorSpeed1 = map(joyposVert, 0, 460, 0, 255);
    MotorSpeed2 = map(joyposVert, 0, 460, 0, 255);

  }
  else if (joyposVert > 564)
  {
    // This is Forward

    // Set Motor A forward

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    // Set Motor B forward

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    //Determine Motor Speeds

    MotorSpeed1 = map(joyposVert, 564, 1023, 0, 255);
    MotorSpeed2 = map(joyposVert, 564, 1023, 0, 255);

  }
  else
  {
    // This is Stopped

    MotorSpeed1 = 0;
    MotorSpeed2 = 0;

  }

  // Now do the steering
  // The Horizontal position will "weigh" the motor speed
  // Values for each motor

  if (joyposHorz < 460)
  {
    // Move Left

    // As we are going left we need to reverse readings

    joyposHorz = joyposHorz - 460; // This produces a negative number
    joyposHorz = joyposHorz * -1;  // Make the number positive

    // Map the number to a value of 255 maximum

    joyposHorz = map(joyposHorz, 0, 460, 0, 255);


    MotorSpeed1 = MotorSpeed1 - joyposHorz;
    MotorSpeed2 = MotorSpeed2 + joyposHorz;

    // Don't exceed range of 0-255 for motor speeds

    if (MotorSpeed1 < 0)MotorSpeed1 = 0;
    if (MotorSpeed2 > 255)MotorSpeed2 = 255;

  }
  else if (joyposHorz > 564)
  {
    // Move Right

    // Map the number to a value of 255 maximum

    joyposHorz = map(joyposHorz, 564, 1023, 0, 255);


    MotorSpeed1 = MotorSpeed1 + joyposHorz;
    MotorSpeed2 = MotorSpeed2 - joyposHorz;

    // Don't exceed range of 0-255 for motor speeds

    if (MotorSpeed1 > 255)MotorSpeed1 = 255;
    if (MotorSpeed2 < 0)MotorSpeed2 = 0;

  }


  // Read the 2nd Joystick X and Y positions

  joyposVert2 = analogRead(joyVert2);
  joyposHorz2 = analogRead(joyHorz2);

  // Determine if this is a forward or backward motion
  // Do this by reading the Verticle Value
  // Apply results to MotorSpeed and to Direction

  if (joyposVert2 < 460)
  {
    // This is Backward

    // Set Motor C backward

    digitalWrite(in12, LOW);
    digitalWrite(in22, HIGH);

    // Set Motor D backward

    digitalWrite(in32, LOW);
    digitalWrite(in42, HIGH);

    //Determine Motor Speeds

    // As we are going backwards we need to reverse readings

    joyposVert2 = joyposVert2 - 460; // This produces a negative number
    joyposVert2 = joyposVert2 * -1;  // Make the number positive

    MotorSpeed3 = map(joyposVert2, 0, 460, 0, 255);
    MotorSpeed4 = map(joyposVert2, 0, 460, 0, 255);

  }
  else if (joyposVert2 > 564)
  {
    // This is Forward

    // Set Motor C forward

    digitalWrite(in12, HIGH);
    digitalWrite(in22, LOW);

    // Set Motor D forward

    digitalWrite(in32, HIGH);
    digitalWrite(in42, LOW);

    //Determine Motor Speeds

    MotorSpeed3 = map(joyposVert2, 564, 1023, 0, 255);
    MotorSpeed4 = map(joyposVert2, 564, 1023, 0, 255);

  }
  else
  {
    // This is Stopped

    MotorSpeed3 = 0;
    MotorSpeed4 = 0;

  }

  // Now do the steering
  // The Horizontal position will "weigh" the motor speed
  // Values for each motor

  if (joyposHorz2 < 460)
  {
    // Move Left

    // As we are going left we need to reverse readings

    joyposHorz2 = joyposHorz2 - 460; // This produces a negative number
    joyposHorz2 = joyposHorz2 * -1;  // Make the number positive

    // Map the number to a value of 255 maximum

    joyposHorz2 = map(joyposHorz2, 0, 460, 0, 255);


    MotorSpeed3 = MotorSpeed3 - joyposHorz2;
    MotorSpeed4 = MotorSpeed4 + joyposHorz2;

    // Don't exceed range of 0-255 for motor speeds

    if (MotorSpeed3 < 0)MotorSpeed3 = 0;
    if (MotorSpeed4 > 255)MotorSpeed4 = 255;

  }
  else if (joyposHorz2 > 564)
  {
    // Move Right

    // Map the number to a value of 255 maximum

    joyposHorz2 = map(joyposHorz2, 564, 1023, 0, 255);


    MotorSpeed3 = MotorSpeed3 + joyposHorz;
    MotorSpeed4 = MotorSpeed4 - joyposHorz;

    // Don't exceed range of 0-255 for motor speeds

    if (MotorSpeed3 > 255)MotorSpeed3 = 255;
    if (MotorSpeed4 < 0)MotorSpeed4 = 0;

  }


  // Adjust to prevent "buzzing" at very low speed

  if (MotorSpeed1 < 8)MotorSpeed1 = 0;
  if (MotorSpeed2 < 8)MotorSpeed2 = 0;
  if (MotorSpeed3 < 8)MotorSpeed3 = 0;
  if (MotorSpeed4 < 8)MotorSpeed4 = 0;

  // Set the motor speeds

  analogWrite(enA, MotorSpeed1);
  analogWrite(enB, MotorSpeed2);
  analogWrite(enC, MotorSpeed3);
  analogWrite(enD, MotorSpeed4);

}
