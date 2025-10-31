/**
 * @file SensorBase.cpp
 * @brief Implementación de la clase base SensorBase
 */

#include "SensorBase.h"
#include <iostream>

using namespace std;

SensorBase::SensorBase(const char* nom) {
    // Copia el nombre carácter por carácter de forma manual
    int i = 0;
    while (nom[i] != '\0' && i < 49) {
        nombre[i] = nom[i];
        i++;
    }
    nombre[i] = '\0'; // Termina la cadena
}

SensorBase::~SensorBase() {
    cout << "[Destructor Base] Liberando sensor: " << nombre << endl;
}

const char* SensorBase::obtenerNombre() const {
    return nombre;
}