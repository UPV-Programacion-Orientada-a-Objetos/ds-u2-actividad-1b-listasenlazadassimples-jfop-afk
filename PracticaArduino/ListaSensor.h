/**
 * @file ListaSensor.h
 * @brief Lista enlazada simple genérica para almacenar lecturas de sensores
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef LISTA_SENSOR_H
#define LISTA_SENSOR_H

#include <iostream>
using namespace std;

/**
 * @brief Nodo genérico para la lista enlazada
 * @tparam T Tipo de dato que almacena el nodo
 */
template <typename T>
struct Nodo {
    T dato;              ///< Dato almacenado en el nodo
    Nodo<T>* siguiente;  ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param valor Valor a almacenar en el nodo
     */
    Nodo(T valor) {
        dato = valor;
        siguiente = 0; // Usamos 0 en lugar de nullptr (más básico)
    }
};

/**
 * @class ListaSensor
 * @brief Lista enlazada simple genérica para almacenar lecturas
 * @tparam T Tipo de dato de las lecturas (int, float, double, etc.)
 */
template <typename T>
class ListaSensor {
private:
    Nodo<T>* cabeza; ///< Puntero al primer nodo de la lista
    
public:
    /**
     * @brief Constructor por defecto
     */
    ListaSensor();
    
    /**
     * @brief Destructor - libera toda la memoria de los nodos
     */
    ~ListaSensor();
    
    /**
     * @brief Constructor de copia (Regla de los Tres)
     * @param otra Lista a copiar
     */
    ListaSensor(const ListaSensor<T>& otra);
    
    /**
     * @brief Operador de asignación (Regla de los Tres)
     * @param otra Lista a asignar
     * @return Referencia a esta lista
     */
    ListaSensor<T>& operator=(const ListaSensor<T>& otra);
    
    /**
     * @brief Inserta un elemento al final de la lista
     * @param valor Valor a insertar
     */
    void insertar(T valor);
    
    /**
     * @brief Calcula el promedio de todos los elementos
     * @return Promedio de tipo T
     */
    T calcularPromedio() const;
    
    /**
     * @brief Encuentra y elimina el valor más bajo de la lista
     * @return El valor más bajo encontrado
     */
    T eliminarMinimo();
    
    /**
     * @brief Cuenta cuántos elementos hay en la lista
     * @return Número de elementos
     */
    int contarElementos() const;
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const;
    
    /**
     * @brief Imprime todos los elementos de la lista
     */
    void imprimir() const;
};

template <typename T>
ListaSensor<T>::ListaSensor() {
    cabeza = 0;
}

template <typename T>
ListaSensor<T>::~ListaSensor() {
    cout << "  [Destructor ListaSensor] Liberando lista interna..." << endl;
    
    Nodo<T>* actual = cabeza;
    while (actual != 0) {
        Nodo<T>* siguiente = actual->siguiente;
        cout << "    [Log] Nodo<T> " << actual->dato << " liberado." << endl;
        delete actual;
        actual = siguiente;
    }
}

template <typename T>
ListaSensor<T>::ListaSensor(const ListaSensor<T>& otra) {
    cabeza = 0;
    
    if (otra.cabeza == 0) {
        return;
    }
    
    // Copiar primer nodo
    cabeza = new Nodo<T>(otra.cabeza->dato);
    
    // Copiar resto de nodos
    Nodo<T>* actualOtra = otra.cabeza->siguiente;
    Nodo<T>* actualEsta = cabeza;
    
    while (actualOtra != 0) {
        actualEsta->siguiente = new Nodo<T>(actualOtra->dato);
        actualEsta = actualEsta->siguiente;
        actualOtra = actualOtra->siguiente;
    }
}

template <typename T>
ListaSensor<T>& ListaSensor<T>::operator=(const ListaSensor<T>& otra) {
    if (this == &otra) {
        return *this;
    }
    
    // Liberar memoria actual
    Nodo<T>* actual = cabeza;
    while (actual != 0) {
        Nodo<T>* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    
    // Copiar nueva lista
    cabeza = 0;
    
    if (otra.cabeza == 0) {
        return *this;
    }
    
    cabeza = new Nodo<T>(otra.cabeza->dato);
    Nodo<T>* actualOtra = otra.cabeza->siguiente;
    Nodo<T>* actualEsta = cabeza;
    
    while (actualOtra != 0) {
        actualEsta->siguiente = new Nodo<T>(actualOtra->dato);
        actualEsta = actualEsta->siguiente;
        actualOtra = actualOtra->siguiente;
    }
    
    return *this;
}

template <typename T>
void ListaSensor<T>::insertar(T valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    
    cout << "[Log] Insertando Nodo<T> con valor: " << valor << endl;
    
    if (cabeza == 0) {
        cabeza = nuevoNodo;
        return;
    }
    
    // Buscar el último nodo
    Nodo<T>* actual = cabeza;
    while (actual->siguiente != 0) {
        actual = actual->siguiente;
    }
    
    actual->siguiente = nuevoNodo;
}

template <typename T>
T ListaSensor<T>::calcularPromedio() const {
    if (cabeza == 0) {
        return 0;
    }
    
    T suma = 0;
    int contador = 0;
    
    Nodo<T>* actual = cabeza;
    while (actual != 0) {
        suma = suma + actual->dato;
        contador = contador + 1;
        actual = actual->siguiente;
    }
    
    return suma / contador;
}

template <typename T>
T ListaSensor<T>::eliminarMinimo() {
    if (cabeza == 0) {
        return 0;
    }
    
    // Buscar el mínimo
    T minimo = cabeza->dato;
    Nodo<T>* actual = cabeza;
    
    while (actual != 0) {
        if (actual->dato < minimo) {
            minimo = actual->dato;
        }
        actual = actual->siguiente;
    }
    
    // Eliminar el nodo con el valor mínimo
    if (cabeza->dato == minimo) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return minimo;
    }
    
    actual = cabeza;
    while (actual->siguiente != 0) {
        if (actual->siguiente->dato == minimo) {
            Nodo<T>* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            return minimo;
        }
        actual = actual->siguiente;
    }
    
    return minimo;
}

template <typename T>
int ListaSensor<T>::contarElementos() const {
    int contador = 0;
    Nodo<T>* actual = cabeza;
    
    while (actual != 0) {
        contador = contador + 1;
        actual = actual->siguiente;
    }
    
    return contador;
}

template <typename T>
bool ListaSensor<T>::estaVacia() const {
    return cabeza == 0;
}

template <typename T>
void ListaSensor<T>::imprimir() const {
    Nodo<T>* actual = cabeza;
    
    cout << "[ ";
    while (actual != 0) {
        cout << actual->dato;
        if (actual->siguiente != 0) {
            cout << ", ";
        }
        actual = actual->siguiente;
    }
    cout << " ]" << endl;
}

#endif // LISTA_SENSOR_H