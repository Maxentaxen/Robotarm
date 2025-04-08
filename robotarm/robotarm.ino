#include <Servo.h>

const byte numChars = 32;
char receivedChars[numChars];

bool newData = false;

int dataNumber = 0;
int index;

float target_point[3] = { -3, 4, 5 };
float cylindrical_coordinates[3];
float thetas[2];
float current_position[3];
float baseAngle;
float l1 = 5;
float l2 = 7;
const unsigned long radToDeg = 180 * 1 / PI;


Servo myServo;
Servo armServo;
Servo elbowServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hej");
  delay(1000);


  get_cylindrical();
  get_thetas();

  for (int i = 0; i < 2; i++) {
    Serial.println(thetas[i] * 180 / PI);
  }

  Serial.println(cylindrical_coordinates[1] * 180 / PI);
  myServo.attach(8);
  armServo.attach(9);
  elbowServo.attach(10);
  myServo.write(0);
  armServo.write(0);
  elbowServo.write(0);
  delay(2000);
  //myServo.write(cylindrical_coordinates[1] * 180 / PI);
  //armServo.write((thetas[0] * 180 / PI));
}

void loop() {
  recvWithEndMarker();
  showNewData();
}


void get_cylindrical() {
  cylindrical_coordinates[0] = hypot(target_point[0], target_point[1]);
  if (target_point[0] > 0) {
    cylindrical_coordinates[1] = atan(target_point[1] / target_point[0]);

  } else {
    cylindrical_coordinates[1] = PI + atan(target_point[1] / target_point[0]);
  }
  cylindrical_coordinates[2] = target_point[2];
}

void get_thetas() {
  thetas[1] = -acos((pow(cylindrical_coordinates[0], 2) + pow(cylindrical_coordinates[2], 2) - pow(l1, 2) - pow(l2, 2)) / (2 * l1 * l2));
  thetas[0] = atan(cylindrical_coordinates[2] / cylindrical_coordinates[0]) - atan(l2 * sin(thetas[1]) / (l1 + l2 * cos(thetas[1])));
}



void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  if (Serial.available() > 0) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0';  // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {               // new for this version
    dataNumber = atoi(receivedChars);  // new for this version
    int previous_value = target_point[index];
    Serial.println(dataNumber);
    target_point[index] = dataNumber;
    get_cylindrical();
    get_thetas();
    if (pow(target_point[0], 2) + pow(target_point[1], 2) + pow(target_point[2], 2) > pow(hypot(l1, l2), 2)) {
      Serial.println("Invalid point");
      target_point[index] = previous_value;
      delay(500);
    }
    index = (index + 1) % 3;
    writeRadians(cylindrical_coordinates[1]);
    armServo.write(thetas[0] * 180 / PI);
    elbowServo.write(thetas[0] * 180 / PI);
    Serial.println("Current position: " + String(target_point[0]) + ", " + String(target_point[1]) + ", " + String(target_point[2]));
    newData = false;
  }
}


void writeRadians(float angle) {
  myServo.write(angle * radToDeg);
}
