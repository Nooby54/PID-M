# PID Innobot

## Índice
1. [PID](#pid)
    1. [QTR](#qtr)
    2. [Variables](#variables)
2. [Motores](#motores)

## PID
### QTR
Utiliza la librería [QTR Sensors by Pololu](https://github.com/pololu/qtr-sensors-arduino) en su versión 3.0.

![Sensor QTR](https://i.postimg.cc/s2yjDdMg/qtr8.png)

Conecta los pines `2`, `3`, `4`, `5`, `6` y `7` a los pines analógicos del Innobot en el siguiente orden respectivamente: `A0`, `A1`, `A2`, `A3`, `A4` y `A5` (por confirmar). Conecta el pin `Vcc` a `5V` (es el tercero de derecha a izquierda) del Innobot y el pin `GND` a `GND` del Innobot.

### Variables

A continuación, se describirá la función de cada variable, junto a su comentario correspondiente. Si se requiere una explicación más detallada, se proporcionará después del fragmento de código.

```c++
int forward = 70;  // Velocidad hacia adelante
float kp = 0.018;  // Constante proporcional del PID
float ki = 0.00018;  // Constante integral del PID
float kd = 0.15;  // Constante derivativa del PID
int p, d;  // Variables utilizadas en el PID
float i = 0;  // Variable integral del PID
float p_old = 0;  // Valor anterior de la variable p
int u;  // Variable de control del PID
```
---
## Motores
A continuación se describe la ubicación de los motores y se proporcionan los códigos necesarios para que estos funcionen en [Pygmalion IDE](https://pygmalion.tech/software/).

Cuando el código esté separado por `/*----------------------------*/`, indica que hay dos o más formas de realizar la misma acción.

### Ubicación

- **M4**: Motor izquierdo
- **M1**: Motor derecho

```c++
// Cambiar velocidades
motorSpeed(M1, 100);
```

```c++
// Ir hacia adelante (dos motores)
goForward(M1, M4);
```

```c++
// Ir hacia adelante (un motor)
motorOn(M1, FORWARD);
```

```c++
// Ir hacia atrás (dos motores)
goReverse(M1, M4);
/*---------------------------*/
motorOn(M4, FORWARD);
motorOn(M1, FORWARD);
```

```c++
// Ir hacia atrás (un motor)
motorOn(M1, REVERSE);
/*------------------------*/
motorOn(M4, REVERSE);
motorOn(M1, REVERSE);
```

```c++
// Girar a la izquierda
turnLeft(M4, M1);
/*-------------------*/
motorOn(M4, REVERSE);
motorOn(M1, FORWARD);
```

```c++
// Girar a la derecha
turnRight(M4, M1);
/*-----------------*/
motorOn(M1, REVERSE);
motorOn(M4, FORWARD);
```
---
> "Los que dicen que es imposible no deberían molestar ni interrumpir a los que lo estamos haciendo"
> Thomas Alva Edinson