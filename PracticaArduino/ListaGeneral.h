/**
 * @file ListaGeneral.h
 * @brief Lista enlazada NO genérica para gestión polimórfica de sensores
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef LISTA_GENERAL_H
#define LISTA_GENERAL_H

#include "SensorBase.h"

/**
 * @brief Nodo para la lista de gestión de sensores
 */
struct NodoGeneral {
    SensorBase* sensor;      ///< Puntero a la clase base (polimorfismo)
    NodoGeneral* siguiente;  ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param s Puntero al sensor
     */
    NodoGeneral(SensorBase* s) {
        sensor = s;
        siguiente = 0;
    }
};

/**
 * @class ListaGeneral
 * @brief Lista enlazada para gestionar todos los sensores del sistema
 * 
 * Esta lista almacena punteros a SensorBase*, permitiendo gestionar
 * diferentes tipos de sensores de manera polimórfica.
 */
class ListaGeneral {
private:
    NodoGeneral* cabeza; ///< Primer nodo de la lista
    
public:
    /**
     * @brief Constructor por defecto
     */
    ListaGeneral();
    
    /**
     * @brief Destructor - libera memoria de nodos Y sensores
     */
    ~ListaGeneral();
    
    /**
     * @brief Inserta un sensor al final de la lista
     * @param sensor Puntero al sensor a insertar
     */
    void insertar(SensorBase* sensor);
    
    /**
     * @brief Busca un sensor por su nombre
     * @param nombreBuscar Nombre del sensor a buscar
     * @return Puntero al sensor encontrado o 0 si no existe
     */
    SensorBase* buscar(const char* nombreBuscar) const;
    
    /**
     * @brief Procesa todos los sensores de la lista (llama procesarLectura)
     */
    void procesarTodos();
    
    /**
     * @brief Imprime información de todos los sensores
     */
    void imprimirTodos() const;
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const;
};

#endif // LISTA_GENERAL_H