#include <QTRSensors.h>
QTRSensorsAnalog qtrrc((unsigned char[]){ 0, 1, 2, 2, 4, 5, 6 }, 6);

unsigned int IR[8];

// siguelíneas con algoritmo PID
// utiliza 8 sensores en la parte frontal Pololu QTR8-RC

int forward = 90;
float kp = .018;
float ki = 0.00018;
float kd = 0.15;
int p, d;
float i = 0;
float p_old = 0;
int u;

void setup() {

  Serial.begin(9600);
}

void loop() {
  qtrrc.read(IR);  // read raw sensor values

  int p = -3 * IR[0] - 2 * IR[1] - IR[2] + IR[3];
  p = p + 2 * IR[4] + 3 * IR[5];  // integrar error

  //  for (int i=0 ; i<8 ; i++)
  //  {
  //    Serial.print(IR[i]);
  //    Serial.print(" ");
  //  }
  //
  //  Serial.println();
  //  delay(200);

  i = i + p;
  d = p - p_old;
  p_old = p;

  if ((p * i) < 0) i = 0;  // corrige el overshooting - integral windup

  Serial.print(forward + u);
  Serial.print(" ; ");
  Serial.println(forward - u);

  u = kp * p + ki * i + kd * d;
  drive(forward + u, forward - u);
}

void drive(int speedl, int speedr) {

  if (speedl > 0) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    // change high for low if wheel doesnt spin forward
    analogWrite(PWMA, constrain(speedl, 0, forward));
  } else {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    // change high for low if wheel doesnt spin backward
    analogWrite(PWMA, constrain(-speedl, 0, forward));
  }
  if (speedr > 0) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    // change high for low if wheel doesnt spin forward
    analogWrite(PWMB, constrain(speedr, 0, forward));
  } else {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    // change high for low if wheel doesnt spin backward
    analogWrite(PWMB, constrain(-speedr, 0, forward));
  }
}

void TestAdelante() {
  goForward(M1, M2);
}