/**
 * @file SensorPresion.h
 * @brief Sensor de presión que maneja lecturas tipo int
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorPresion
 * @brief Sensor concreto que gestiona lecturas de presión (int)
 * 
 * Este sensor almacena lecturas de tipo int en una lista enlazada.
 * Su procesamiento consiste en calcular el promedio de todas las lecturas.
 */
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> historial; ///< Lista de lecturas de presión
    
public:
    /**
     * @brief Constructor del sensor de presión
     * @param nom Identificador del sensor
     */
    SensorPresion(const char* nom);
    
    /**
     * @brief Destructor del sensor
     */
    ~SensorPresion();
    
    /**
     * @brief Registra una nueva lectura de presión
     * @param valor Valor de presión a registrar
     */
    void registrarLectura(int valor);
    
    /**
     * @brief Procesa las lecturas: calcula el promedio
     */
    void procesarLectura();
    
    /**
     * @brief Imprime la información del sensor
     */
    void imprimirInfo() const;
};

#endif // SENSOR_PRESION_H