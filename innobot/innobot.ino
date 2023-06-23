#include <QTRSensors.h>
QTRSensorsAnalog qtrrc((unsigned char[]) {
  0, 1, 2, 2, 4, 5, 6
}, 6); //Pines de los sensores

unsigned int IR[6]; //Cantidad de sensores

int forward = 70;  // Velocidad hacia adelante
float kp = 0.018;  // Constante proporcional del PID
float ki = 0.00018;  // Constante integral del PID
float kd = 0.15;  // Constante derivativa del PID
int p, d;  // Variables utilizadas en el PID
float i = 0;  // Variable integral del PID
float p_old = 0;  // Valor anterior de la variable p
int u;  // Variable de control del PID
int ContadorInterseccion = 0; // Variable para saber en qué intersección está.

void setup() {
  Serial.begin(9600);
}

void loop() {
  qtrrc.read(IR); // Función de la librería para leer los valores de cada sensor, para leer cada sensor es con IR[x]

  // Cálculo del valor de p mediante una combinación lineal de los sensores
  int p = -3 * IR[0] - 2 * IR[1] - IR[2] + IR[3];
  p = p + 2 * IR[4] + 3 * IR[5]; // Integrar error

  i = i + p; // Actualiza la acumulación de la componente integral (I) 
  d = p - p_old; // Calcula la componente derivativa (D)
  p_old = p; // Actualiza el valor anterior del componente error anterior (p_old)

  if ((p * i) < 0) i = 0; // Corrige el overshooting - integral windup

  Serial.print(forward + u);
  Serial.print(" ; ");
  Serial.println(forward - u);

  u = kp * p + ki * i + kd * d; // Calcula la salida del controlador PID en función de las componentes P, I y D
  drive(forward - u, forward + u); // Función que controla las velocidades de cada motor con el PID
  controlsalidas();
  intersecciones();
}

void drive(int speedl, int speedr) {
  // Control de los motores para avanzar o retroceder con diferentes velocidades
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

  // Control de las salidas en base a los valores de los sensores
  if (IR[0] > 300) {
    do {
      qtrrc.read(IR);
      motorSpeed(M1, 60);
      motorSpeed(M4, 60);
      turnRight(M4, M1);
    } while (IR[2] < 400);
  } else {
    // ...
  }

  if (IR[5] > 300) {
    do {
      qtrrc.read(IR);
      motorSpeed(M1, 60);
      motorSpeed(M2, 60);
      turnLeft(M4, M1);
    } while (IR[4] < 400);
  } else {
    // ...
  }
}

void intersecciones() {
  qtrrc.read(IR);

  // Lógica para detectar intersecciones y realizar acciones específicas
  if (IR[5] > 600 && IR[4] > 600 && IR[3] > 600) {
    ContadorInterseccion += 1;

    switch (ContadorInterseccion) {
      case 1:
        forward = 60;
        motorSpeed(M1, 50);
        motorSpeed(M4, 50);
        motorsOff(M1, M4);
        delay(200);
        goForward(M1, M4);
        delay(100);
        do {
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
        do {
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
        do {
          qtrrc.read(IR);
          motorSpeed(M1, 45);
          motorSpeed(M4, 45);
          motorOn(M4, REVERSE);
          motorOn(M1, FORWARD);
        } while (IR[2] < 200 && IR[3] < 200);
        forward = 80;
        break;

      default:
        // Acciones a realizar en caso de que no se cumpla ningún caso anterior
        break;
    }
  }
}

void TestAdelante() {
  goForward(M1, M2);
}


//Escrito por Daniel Godoy y Jaider Valencia
//Asesorados por Kevin Yurgaky
//Comentado por ChatGPT con correciones menores por parte de Jaider Valencia y Daniel Godoy