#include <QTRSensors.h>
QTRSensorsAnalog qtrrc((unsigned char[]) {
  0, 1, 2, 3, 4, 5
}, 6);

unsigned int IR[6];

// siguelíneas con algoritmo PID
// utiliza 8 sensores en la parte frontal Pololu QTR8-RC

int forward = 70;
float kp = .018;
float ki = 0.00018;
float kd = 0.15;
int p, d;
float i = 0;
float p_old = 0;
int u;

int ContadorInterseccion = 0;
const int boton = 7; // Botón asignado en el pin 2.

const int led = 13;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
  qtrrc.read(IR); // read raw sensor values

  int p = -4 * IR[0] - 3 * IR[1] - 2 * IR[2] + IR[3] + 2 * IR[4] + 3 * IR[5]; // integrar error



  i = i + p;
  d = p - p_old;
  p_old = p;

  if ((p * i) < 0) i = 0; // corrige el overshooting - integral windup

  /*Serial.print(forward+u);
    Serial.print(" ; ");
    Serial.println(forward-u);*/

  // Serial.print(digitalRead(boton));

  int sensorVal = digitalRead(2);
  //print out the value of the pushbutton
  // Serial.println(sensorVal);

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  u = kp * p + ki * i + kd * d;

  if (sensorVal == HIGH) {

    forward = 65;

    ControlSalidas();
    InterseccionesSinCarga();
  } else {

    forward = 85;

    controlsalidaslleno();
    InterseccionesConCarga();
  }

  drive(forward - u, forward + u);
  //vista();

}

void vista()
{
  qtrrc.read(IR); // read raw sensor values
  for (int i = 0 ; i < 6 ; i++)
  {
    Serial.print(IR[i]);
    Serial.print(" ");
  }
  //
  Serial.println();
  delay(200);
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
    motorSpeed(M1, constrain(-speedr, 0, forward));
  }
}


void ControlSalidas() {
  qtrrc.read(IR);  // read raw sensor values

  if (IR[0] > 350) {
    do {
      qtrrc.read(IR);
      motorSpeed(M1, 40);
      motorSpeed(M4, 75);
      turnRight(M4, M1);
    } while (IR[1] < 350);
  } else {
  }



  if (IR[5] > 350) {
    do {
      qtrrc.read(IR);
      motorSpeed(M1, 75);
      motorSpeed(M4, 40);
      turnLeft(M4, M1);
    } while (IR[4] < 350);
  } else {
  }
}

void controlsalidaslleno() {
  qtrrc.read(IR);

  // Control de las salidas en base a los valores de los sensores
  if (IR[0] > 350) {
    do {
      qtrrc.read(IR);
      motorSpeed(M1, 45);
      motorSpeed(M4, 70);
      turnRight(M4, M1);
    } while (IR[1] < 350);
  } else {
  }

  if (IR[5] > 350) {
    do {
      qtrrc.read(IR);
      motorSpeed(M1, 75);
      motorSpeed(M4, 40);
      turnLeft(M4, M1);
    } while (IR[4] < 350);
  } else {
  }
}

void InterseccionesSinCarga()
{
  qtrrc.read(IR); // read raw sensor values

  //if (IR[4] > 100 && IR[3] > 100)
  if (IR[5] > 300 && IR[3] > 300)
  {
    ContadorInterseccion += 1;


    switch (ContadorInterseccion)
    {
      case 1:
        digitalWrite(led, HIGH);
        forward = forward;
        motorSpeed(M1, 70);
        motorSpeed(M4, 70);
        motorsOff(M1, M4);
        delay(200);
        goForward(M1, M4);
        delay(70);
        do {
          motorSpeed(M1, 60);
          motorSpeed(M4, 60);
          qtrrc.read(IR);
          turnRight(M4, M1);
        } while (IR[2] < 300 && IR[3] < 300);

        turnRight(M1, M4);
        delay(200);


        forward = forward;
        digitalWrite(led, LOW);
        break;

      case 2:
        digitalWrite(led, HIGH);
        motorsOff(M1, M4);
        delay(200);

        motorSpeed(M1, 40);
        motorSpeed(M4, 40);

        goForward(M1, M4);
        delay(100);

        do {
          qtrrc.read(IR);
          motorSpeed(M1, 80);
          motorSpeed(M4, 80);
          turnLeft(M4, M1);
        } while (IR[3] < 250);
        digitalWrite(led, LOW);
        break;

      case 3:
        digitalWrite(led, HIGH);
        motorSpeed(M1, 70);
        motorSpeed(M4, 70);
        motorSpeed(M3, 80);
        motorsOff(M1, M4);
        motorOn(M3, FORWARD);
        delay(700);
        motorOff(M3);
        motorOn(M3, REVERSE);
        delay(600);

        motorsOff(M1, M4);
        delay(300);
        goReverse(M1, M4);
        delay(300);
        motorSpeed(M1, 60);
        motorSpeed(M4, 60);
        motorOn(M4, REVERSE);
        motorOn(M1, FORWARD);
        delay(300);
        do {
          qtrrc.read(IR);
          motorSpeed(M1, 60);
          motorSpeed(M4, 60);
          motorOn(M4, REVERSE);
          motorOn(M1, FORWARD);
        } while (IR[2] < 200 && IR[3] < 200);
        forward = forward;
        digitalWrite(led, LOW);
        break;

      case 4:
        digitalWrite(led, HIGH);
        digitalWrite(led, LOW);
        motorsOff(M1, M4);
        delay(100);
        motorSpeed(M1, 45);
        motorSpeed(M4, 45);
        goForward(M1, M4);
        delay(100);

        motorSpeed(M1, 65);
        motorSpeed(M4, 65);
        motorOn(M4, REVERSE);
        motorOn(M1, FORWARD);
        delay(300);
        do
        {
          qtrrc.read(IR); // read raw sensor values
          motorSpeed(M1, 65);
          motorSpeed(M4, 65);

          motorOn(M4, REVERSE);
          motorOn(M1, FORWARD);
        } while (IR[2] < 200 && IR[3] < 200);
        motorSpeed(M1, 75);
        motorSpeed(M4, 75);
        digitalWrite(led, LOW);
        break;

      default:

        break;


    }
  }
}

void intersecciones2() {
  qtrrc.read(IR);

  // Lógica para detectar intersecciones y realizar acciones específicas
  if (IR[5] > 200 && IR[3] > 200)
    ContadorInterseccion += 1;

  switch (ContadorInterseccion) {
    case 1:
      digitalWrite(led, HIGH);
      forward = forward;
      motorSpeed(M1, 70);
      motorSpeed(M4, 70);
      motorsOff(M1, M4);
      delay(200);
      goForward(M1, M4);
      delay(70);
      do {
        motorSpeed(M1, 60);
        motorSpeed(M4, 60);
        qtrrc.read(IR);
        turnRight(M4, M1);
      } while (IR[2] < 300 && IR[3] < 300);

      turnRight(M1, M4);
      delay(200);


      forward = forward;
      digitalWrite(led, LOW);
      break;

    case 2:
      digitalWrite(led, HIGH);
      motorsOff(M1, M4);
      delay(200);

      motorSpeed(M1, 70);
      motorSpeed(M4, 70);

      goForward(M1, M4);
      delay(100);

      do {
        qtrrc.read(IR);
        motorSpeed(M1, 80);
        motorSpeed(M4, 80);
        turnLeft(M4, M1);
      } while (IR[3] < 250);
      digitalWrite(led, LOW);
      break;

    case 3:
      digitalWrite(led, HIGH);
      motorSpeed(M1, 70);
      motorSpeed(M4, 70);
      motorSpeed(M3, 90);
      motorsOff(M1, M4);
      motorOn(M3, FORWARD);
      delay(700);
      motorOff(M3);
      delay(600);

      for (int i = 0; i < 30; i++) {
        motorSpeed(M1, 80);
        motorSpeed(M4, 80);
        goReverse(M1, M4);
        delay(40);
        goForward(M1, M4);
        delay(70);
      }

      digitalWrite(led, LOW);
      break;


  }
}


void InterseccionesConCarga()
{
  qtrrc.read(IR); // read raw sensor values

  //if (IR[4] > 100 && IR[3] > 100)
  if (IR[5] > 150 && IR[3] > 150)
  {
    ContadorInterseccion += 1;


    switch (ContadorInterseccion)
    {
      case 1:
        digitalWrite(led, HIGH);
        forward = forward;
        motorSpeed(M1, 70);
        motorSpeed(M4, 70);
        motorsOff(M1, M4);
        delay(200);
        goForward(M1, M4);
        delay(70);
        do {
          motorSpeed(M1, 60);
          motorSpeed(M4, 60);
          qtrrc.read(IR);
          turnRight(M4, M1);
        } while (IR[2] < 300 && IR[3] < 300);

        turnRight(M1, M4);
        delay(200);


        forward = forward;
        digitalWrite(led, LOW);
        break;

      case 2:
        digitalWrite(led, HIGH);
        motorsOff(M1, M4);
        delay(200);

        motorSpeed(M1, 40);
        motorSpeed(M4, 40);

        goForward(M1, M4);
        delay(100);

        do {
          qtrrc.read(IR);
          motorSpeed(M1, 80);
          motorSpeed(M4, 80);
          turnLeft(M4, M1);
        } while (IR[3] < 250);
        digitalWrite(led, LOW);
        break;

      case 3:
        digitalWrite(led, HIGH);
        motorSpeed(M1, 70);
        motorSpeed(M4, 70);
        motorSpeed(M3, 90);
        motorsOff(M1, M4);
        motorOn(M3, FORWARD);
        delay(1000);
        motorOff(M3);


        for (int i = 0; i < 50; i++) {
          motorSpeed(M1, 70);
          motorSpeed(M4, 70);

          goForward(M1, M4);
          delay(100);
          goReverse(M1, M4);
          delay(80);

        }

        digitalWrite(led, LOW);
        break;


      default:

        break;


    }
  }
}


