// SCARA.cpp
#include "SCARA.h"
#include <math.h>

// Constructor para inicializar las longitudes y ángulos iniciales
SCARA::SCARA(float longitud1, float longitud2) {
  l1 = longitud1;
  l2 = longitud2;
  theta1 = 0.0;  // Posición inicial en 0 grados
  theta2 = 0.0;
}

// Método para normalizar ángulos en el rango [-pi, pi]
float SCARA::normalizarAngulo(float angulo) {
  return atan2(sin(angulo), cos(angulo));
}

// Método para calcular la cinemática inversa
void SCARA::calcularCinematicaInversa(float x, float y) {
  // Calculamos theta2 usando la fórmula de cinemática inversa
  float cos_theta2 = (x * x + y * y - l1 * l1 - l2 * l2) / (2 * l1 * l2);

  // Aseguramos que cos_theta2 esté en el rango [-1, 1]
  if (cos_theta2 > 1.0) cos_theta2 = 1.0;
  if (cos_theta2 < -1.0) cos_theta2 = -1.0;

  // Solución para theta2 (ángulo del segundo brazo)
  float theta2_1 = acos(cos_theta2);
  float theta2_2 = -acos(cos_theta2);

  // Calculamos theta1 para ambas soluciones de theta2
  float theta1_1 = atan2(y, x) - atan2(l2 * sin(theta2_1), l1 + l2 * cos(theta2_1));
  float theta1_2 = atan2(y, x) - atan2(l2 * sin(theta2_2), l1 + l2 * cos(theta2_2));

  // Normalizamos los ángulos entre [-pi, pi]
  theta1_1 = normalizarAngulo(theta1_1);
  theta1_2 = normalizarAngulo(theta1_2);
  theta2_1 = normalizarAngulo(theta2_1);
  theta2_2 = normalizarAngulo(theta2_2);

  // Elegimos la solución que minimiza el recorrido angular
  float delta_theta1_1 = fabs(theta1_1 - theta1);
  float delta_theta2_1 = fabs(theta2_1 - theta2);
  float delta_theta1_2 = fabs(theta1_2 - theta1);
  float delta_theta2_2 = fabs(theta2_2 - theta2);

  if ((delta_theta1_1 + delta_theta2_1) < (delta_theta1_2 + delta_theta2_2)) {
    theta1 = theta1_1;
    theta2 = theta2_1;
  }
  else {
    theta1 = theta1_2;
    theta2 = theta2_2;
  }
}

// Métodos para obtener los ángulos actuales
float SCARA::obtenerTheta1() {
  return theta1 * 180.0 / PI; // Convertimos a grados
}

float SCARA::obtenerTheta2() {
  return theta2 * 180.0 / PI; // Convertimos a grados
}

// Método para mostrar ángulos por el puerto serie
void SCARA::mostrarAngulos() {
  Serial.print("Theta1: ");
  Serial.println(obtenerTheta1());
  Serial.print("Theta2: ");
  Serial.println(obtenerTheta2());
}
