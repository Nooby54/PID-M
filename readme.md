<center> <h1><b>PID Innobot</b></h1> </center>

<center> <h2><b>Configuración de motores</b></h2> </center>

A continuación se describe la ubicación de los motores y los codigos para que estos funcionen en [Pygmalion IDE](https://pygmalion.tech/software/) h

<center> <h3><b>Ubicación</b></h3> </center>
**M4** = Izquierdo

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
