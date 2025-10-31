/**
 * @file ListaGeneral.cpp
 * @brief Implementación de la lista de gestión polimórfica
 */

#include "ListaGeneral.h"
#include <iostream>

using namespace std;

ListaGeneral::ListaGeneral() {
    cabeza = 0;
}

ListaGeneral::~ListaGeneral() {
    cout << "\n--- Liberacion de Memoria en Cascada ---" << endl;
    
    NodoGeneral* actual = cabeza;
    while (actual != 0) {
        NodoGeneral* siguiente = actual->siguiente;
        
        cout << "[Destructor General] Liberando Nodo: " << actual->sensor->obtenerNombre() << endl;
        
        // IMPORTANTE: Esto llama al destructor virtual, que invoca
        // el destructor correcto de la clase derivada
        delete actual->sensor;
        
        delete actual;
        actual = siguiente;
    }
    
    cout << "Sistema cerrado. Memoria limpia." << endl;
}

void ListaGeneral::insertar(SensorBase* sensor) {
    NodoGeneral* nuevoNodo = new NodoGeneral(sensor);
    
    if (cabeza == 0) {
        cabeza = nuevoNodo;
        return;
    }
    
    // Buscar el último nodo
    NodoGeneral* actual = cabeza;
    while (actual->siguiente != 0) {
        actual = actual->siguiente;
    }
    
    actual->siguiente = nuevoNodo;
}

SensorBase* ListaGeneral::buscar(const char* nombreBuscar) const {
    NodoGeneral* actual = cabeza;
    
    while (actual != 0) {
        const char* nombreActual = actual->sensor->obtenerNombre();
        
        // Comparar cadenas manualmente
        bool iguales = true;
        int i = 0;
        while (nombreActual[i] != '\0' || nombreBuscar[i] != '\0') {
            if (nombreActual[i] != nombreBuscar[i]) {
                iguales = false;
                break;
            }
            i++;
        }
        
        if (iguales) {
            return actual->sensor;
        }
        
        actual = actual->siguiente;
    }
    
    return 0;
}

void ListaGeneral::procesarTodos() {
    cout << "\n--- Ejecutando Polimorfismo ---" << endl;
    
    NodoGeneral* actual = cabeza;
    while (actual != 0) {
        // POLIMORFISMO: Llama al método correcto según el tipo real
        actual->sensor->procesarLectura();
        cout << endl;
        actual = actual->siguiente;
    }
}

void ListaGeneral::imprimirTodos() const {
    cout << "\n--- Lista de Sensores Registrados ---" << endl;
    
    if (cabeza == 0) {
        cout << "No hay sensores registrados." << endl;
        return;
    }
    
    NodoGeneral* actual = cabeza;
    int contador = 1;
    while (actual != 0) {
        cout << contador << ". ";
        actual->sensor->imprimirInfo();
        cout << endl;
        contador = contador + 1;
        actual = actual->siguiente;
    }
}

bool ListaGeneral::estaVacia() const {
    return cabeza == 0;
}