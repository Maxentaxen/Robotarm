#include <Servo.h>


float target_point[3] = { -1, 1.3, 2 };
float cylindrical_coordinates[3];
float thetas[2];
float current_position[3];
float baseAngle;
float l1 = 1;
float l2 = 2;
const unsigned long pi = 3.141592653589793238462643383279502884197169399;


Servo myServo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  get_cylindrical();
  get_thetas();
  for (int i = 0; i < 2; i++) {
    Serial.println(thetas[i] * 180 / PI);
  }
  Serial.println(cylindrical_coordinates[1] * 180 / PI);
  myServo.attach(8);
  myServo.write(0);
  delay(2000);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  myServo.write(cylindrical_coordinates[1] * 180 / PI);
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
  thetas[0] = atan(cylindrical_coordinates[2] / cylindrical_coordinates[0]) - atan( l2 * sin(thetas[1]) / ( l1 + l2 * cos(thetas[1])));
}

