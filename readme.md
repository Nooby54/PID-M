# PID Innobot

## Configuración de motores
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
```
```c++
//Para ir hacia atras (un motor)
    motorOn(M1, REVERSE);
```c++
//Para tomar a la izquierda
    turnLeft(M1,M4);
```
```c++
//Para tomar a la derecha
    turnRight(M1,M4);
```
