#include <QTRSensors.h>
QTRSensorsAnalog qtrrc((unsigned char[]) {
  0, 1, 2, 2, 4, 5, 6
}, 6);

unsigned int IR[6];

// siguelíneas con algoritmo PID
// utiliza 6 sensores en la parte frontal Pololu QTR8-RC

int forward = 70;  // Velocidad hacia adelante
float kp = 0.018;  // Constante proporcional del PID
float ki = 0.00018;  // Constante integral del PID
float kd = 0.15;  // Constante derivativa del PID
int p, d;  // Variables utilizadas en el PID
float i = 0;  // Variable integral del PID
float p_old = 0;  // Valor anterior de la variable p
int u;  // Variable de control del PID

int ContadorInterseccion = 0;

void setup() {

  Serial.begin(9600);

}

void loop()
{
  qtrrc.read(IR);

  int p = -3 * IR[0] - 2 * IR[1] - IR[2] + IR[3];
  p = p + 2 * IR[4] + 3 * IR[5]; // integrar error

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

  if ((p * i) < 0) i = 0; // corrige el overshooting - integral windup

  Serial.print(forward + u);
  Serial.print(" ; ");
  Serial.println(forward - u);

  u = kp * p + ki * i + kd * d;
  drive(forward - u, forward + u);
  controlsalidas();
  intersecciones();
}

void drive(int speedl, int speedr)
{

  if (speedl > 0) {
    motorOn(M4, FORWARD);

    motorSpeed(M4, constrain(speedl, 0, forward));

  } else {
    motorOn(M4, REVERSE);

    motorSpeed(M4, constrain(-speedl, 0, forward));
  }
  if (speedr > 0) {
    motorOn(M1, FORWARD);

    motorSpeed(M1, constrain(speedr, 0, forward));
  } else {
    motorOn(M1, REVERSE);

    motorSpeed(M4, constrain(-speedr, 0, forward));
  }
}

void controlsalidas() {

  qtrrc.read(IR);

  if (IR[0] > 300) {
    do {
      qtrrc.read(IR);
      motorSpeed(M1, 60);
      motorSpeed(M4, 60);
      turnRight(M4, M1);
    } while (IR[2] < 400);
  } else {
  }



  if (IR[5] > 300) {
    do {
      qtrrc.read(IR);
      motorSpeed(M1, 60);
      motorSpeed(M2, 60);
      turnLeft(M4, M1);
    } while (IR[4] < 400);
  } else { }
}

void TestAdelante()
{
  goForward(M1, M2);
}


void intersecciones()
{
  qtrrc.read(IR);
  if (IR[5] > 600 && IR[4] > 600 && IR[3] > 600)
  {
    ContadorInterseccion += 1;

    switch (ContadorInterseccion)
    {
      case 1:
        forward = 60;
        motorSpeed(M1, 50);
        motorSpeed(M4, 50);
        motorsOff(M1, M4);
        delay(200);

        goForward(M1, M4);
        delay(100);

        do
        {
          motorSpeed(M1, 50);
          motorSpeed(M4, 50);
          qtrrc.read(IR);
          turnRight(M4, M1);
        } while (IR[2] < 200 && IR[3] < 200);
        motorsOff(M1, M4);
        delay(100);
        forward = 70;
        break;

      case 2:
        motorSpeed(M1, 50);
        motorSpeed(M4, 50);
        motorsOff(M1, M4);
        motorOn(M2, REVERSE);
        delay(650);
        motorOn(M2, FORWARD);
        delay(650);
        goReverse(M1, M4);
        delay(300);
        motorSpeed(M1, 45);
        motorSpeed(M4, 45);
        motorOn(M1, REVERSE);
        motorOn(M4, FORWARD);
        delay(400);
        do
        {
          qtrrc.read(IR);
          motorSpeed(M1, 45);
          motorSpeed(M4, 45);

          motorOn(M1, REVERSE);
          motorOn(M4, FORWARD);
        } while (IR[4] < 250 && IR[3] < 250);
        motorsOff(M1, M4);
        delay(100);
        forward = 70;
        break;
      case 3:
        motorsOff(M1, M4);
        delay(1000);
        motorSpeed(M1, 45);
        motorSpeed(M4, 45);
        goForward(M1, M4);
        delay(50);

        motorSpeed(M1, 45);
        motorSpeed(M4, 45);
        motorOn(M4, REVERSE);
        motorOn(M1, FORWARD);
        delay(300);
        do
        {
          qtrrc.read(IR);
          motorSpeed(M1, 45);
          motorSpeed(M4, 45);

          motorOn(M4, REVERSE);
          motorOn(M1, FORWARD);
        } while (IR[2] < 200 && IR[3] < 200);
        forward = 80;
        break;
      default:

        break;
    }
  }
}

//Copiado por DG y Jaider, asesorado por Kevin Yurgaky
