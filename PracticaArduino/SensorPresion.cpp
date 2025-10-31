/**
 * @file SensorPresion.cpp
 * @brief Implementación del sensor de presión
 */

#include "SensorPresion.h"
#include <iostream>

using namespace std;

SensorPresion::SensorPresion(const char* nom) : SensorBase(nom) {
    cout << "[Sensor Presion] Sensor '" << nombre << "' creado." << endl;
}

SensorPresion::~SensorPresion() {
    cout << "  [Destructor Sensor " << nombre << "] Liberando sensor de presion..." << endl;
}

void SensorPresion::registrarLectura(int valor) {
    cout << "[Sensor " << nombre << "] Registrando lectura: " << valor << " (int)" << endl;
    historial.insertar(valor);
}

void SensorPresion::procesarLectura() {
    cout << "-> Procesando Sensor " << nombre << "..." << endl;
    
    if (historial.estaVacia()) {
        cout << "[Sensor Presion] No hay lecturas para procesar." << endl;
        return;
    }
    
    int promedio = historial.calcularPromedio();
    int numLecturas = historial.contarElementos();
    
    cout << "[Sensor Presion] Promedio calculado sobre " << numLecturas << " lectura(s) (" << promedio << ")." << endl;
}

void SensorPresion::imprimirInfo() const {
    cout << "Sensor: " << nombre << " [Tipo: Presion]" << endl;
    cout << "Numero de lecturas: " << historial.contarElementos() << endl;
}