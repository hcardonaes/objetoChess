/*
 Name:		objetoChess.ino
 Created:	15/09/2024 20:04:57
 Author:	Ofel
*/

// main.ino
#include <Arduino.h>
#include "SCARA.h"

// Definimos las longitudes de los brazos del SCARA
const float l1 = 10.0;  // Longitud del primer brazo en mm
const float l2 = 10.0;  // Longitud del segundo brazo en mm

// Creamos una instancia de la clase SCARA
SCARA scara(l1, l2);

void setup() {
    Serial.begin(115200);
    Serial.println("Ingrese las coordenadas x e y (en mm):");
}

void loop() {
    // Si hay datos disponibles en el puerto serie
    if (Serial.available() > 0) {
        // Leer las coordenadas x e y desde el puerto serie
        float x = Serial.parseFloat();
        float y = Serial.parseFloat();

        // Calcular la cinemática inversa
        scara.calcularCinematicaInversa(x, y);

        // Mostrar los resultados en el puerto serie
        scara.mostrarAngulos();
    }
}
