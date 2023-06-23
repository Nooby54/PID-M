# PID Innobot

## Indice
1. [PID.](#pid)
    1. [QTR.](#qtr)
        1. [Librerias.](Librerias)
        2. [Conexiones.](#conexiones)
    2. [Variables.](#variables)
2. [Motores.](#motores)

## PID
### QTR
#### Librerias
#### Conexiones
![](https://i.postimg.cc/s2yjDdMg/qtr8.png)

Conectar los pines `2 3 4 5 6 7` a los pines análogos del Innobot en el siguiente orden respectivamente `A0 A1 A2 A3 A4 A5`

### Variables

---
## Motores
A continuación se describe la ubicación de los motores y los códigos para que estos funcionen en [Pygmalion IDE.](https://pygmalion.tech/software/)

Cuando el codigo este separado por `/*----------------------------*/` indica que hay dos o más formas de realizar la misma acción.

### Ubicación

**M4** = Izquierdo <br>
**M1** = Derecho

```c++
//Para cambiar velocidades
    motorSpeed(M1,100);
```
```c++
//Para ir hacia adelante (dos motores)
    goForward(M1,M4);
```
```c++
//Para ir hacia adelante (un motor)
    motorOn(M1, FORWARD);
```
```c++
//Para ir hacia atras (dos motores)
    goReverse(M1, M4);
/*-------------------------------*/
    motorOn(M4, FORWARD);
    motorOn(M1, FORWARD);
```
```c++
//Para ir hacia atras (un motor)
    motorOn(M1, REVERSE);
/*----------------------------*/
    motorOn(M4, REVERSE);
    motorOn(M1, REVERSE);
```
```c++
//Para tomar a la izquierda
    turnLeft(M4,M1);
/*-----------------------*/
    motorOn(M4, REVERSE);
    motorOn(M1, FORWARD);
```
```c++
//Para tomar a la derecha
    turnRight(M4,M1);
/*----------------------*/
    motorOn(M1, REVERSE);
    motorOn(M4, FORWARD);
```
---
> "Los que dicen que es imposible no deberían molestar ni interrumpir a los que lo estamos haciendo"
> Thomas Alva Edinson