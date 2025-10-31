/**
 * @file SensorTemperatura.cpp
 * @brief Implementación del sensor de temperatura
 */

#include "SensorTemperatura.h"
#include <iostream>

using namespace std;

SensorTemperatura::SensorTemperatura(const char* nom) : SensorBase(nom) {
    cout << "[Sensor Temp] Sensor '" << nombre << "' creado." << endl;
}

SensorTemperatura::~SensorTemperatura() {
    cout << "  [Destructor Sensor " << nombre << "] Liberando sensor de temperatura..." << endl;
}

void SensorTemperatura::registrarLectura(float valor) {
    cout << "[Sensor " << nombre << "] Registrando lectura: " << valor << " (float)" << endl;
    historial.insertar(valor);
}

void SensorTemperatura::procesarLectura() {
    cout << "-> Procesando Sensor " << nombre << "..." << endl;
    
    if (historial.estaVacia()) {
        cout << "[Sensor Temp] No hay lecturas para procesar." << endl;
        return;
    }
    
    int numLecturas = historial.contarElementos();
    
    if (numLecturas == 1) {
        float promedio = historial.calcularPromedio();
        cout << "[Sensor Temp] Promedio calculado sobre " << numLecturas << " lectura (" << promedio << ")." << endl;
        return;
    }
    
    // Eliminar el valor más bajo
    float minimo = historial.eliminarMinimo();
    cout << "[" << nombre << "] (Temperatura): Lectura mas baja (" << minimo << ") eliminada." << endl;
    
    // Calcular promedio del resto
    if (!historial.estaVacia()) {
        float promedio = historial.calcularPromedio();
        int restantes = historial.contarElementos();
        cout << "Promedio restante sobre " << restantes << " lectura(s): " << promedio << "." << endl;
    }
}

void SensorTemperatura::imprimirInfo() const {
    cout << "Sensor: " << nombre << " [Tipo: Temperatura]" << endl;
    cout << "Numero de lecturas: " << historial.contarElementos() << endl;
}