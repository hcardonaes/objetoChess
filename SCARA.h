// SCARA.h
#ifndef SCARA_H
#define SCARA_H

#include <Arduino.h>

class SCARA {
private:
  float l1;        // Longitud del primer brazo
  float l2;        // Longitud del segundo brazo
  float theta1;    // Último ángulo theta1
  float theta2;    // Último ángulo theta2

  // Método para normalizar ángulos entre [-pi, pi]
  float normalizarAngulo(float angulo);

public:
  // Constructor
  SCARA(float longitud1, float longitud2);

  // Método para calcular la cinemática inversa
  void calcularCinematicaInversa(float x, float y);

  // Método para obtener los ángulos actuales
  float obtenerTheta1();
  float obtenerTheta2();

  // Método para mostrar resultados por puerto serie
  void mostrarAngulos();
};

#endif


