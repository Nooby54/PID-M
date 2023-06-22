#include <QTRSensors.h>
QTRSensorsAnalog qtrrc((unsigned char[]) {
  0, 1, 2, 2, 4, 5, 6
}, 6);

//A = Izquierdo (M4)
//B = Derecho (M1)

unsigned int IR[6];

int forward = 45;
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
  qtrrc.read(IR);

  int p = -3 * IR[0] - 2 * IR[1] - IR[2] + IR[3];
  p = p + 2 * IR[4] + 3 * IR[5];

  i = i + p;
  d = p - p_old;
  p_old = p;

  if ((p * i) < 0) i = 0;

  Serial.print(forward + u);
  Serial.print(" ; ");
  Serial.println(forward - u);

  u = kp * p + ki * i + kd * d;
  drive(forward - u, forward + u);
}

void drive(int speedl, int speedr)
{
  if (speedl > 0) {
    motorOn(M4, FORWARD);
    // change high for low if wheel doesnt spin forward
    motorSpeed(M4, constrain(speedl, 0, forward));

  } else {
    motorOn(M4, REVERSE);
    // change high for low if wheel doesnt spin forward
    motorSpeed(M4, constrain(-speedl, 0, forward));
  }
  if (speedr > 0) {
    motorOn(M1, FORWARD);
    // change high for low if wheel doesnt spin forward
    motorSpeed(M1, constrain(speedr, 0, forward));
  } else {
    motorOn(M1, REVERSE);
    // change high for low if wheel doesnt spin forward
    motorSpeed(M4, constrain(-speedr, 0, forward));
  }
}

void TestAdelante() {
  goForward(M1, M2);
}
