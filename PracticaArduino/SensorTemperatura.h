/**
 * @file SensorTemperatura.h
 * @brief Sensor de temperatura que maneja lecturas tipo float
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorTemperatura
 * @brief Sensor concreto que gestiona lecturas de temperatura (float)
 * 
 * Este sensor almacena lecturas de tipo float en una lista enlazada.
 * Su procesamiento consiste en eliminar el valor más bajo y calcular
 * el promedio del resto.
 */
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> historial; ///< Lista de lecturas de temperatura
    
public:
    /**
     * @brief Constructor del sensor de temperatura
     * @param nom Identificador del sensor
     */
    SensorTemperatura(const char* nom);
    
    /**
     * @brief Destructor del sensor
     */
    ~SensorTemperatura();
    
    /**
     * @brief Registra una nueva lectura de temperatura
     * @param valor Valor de temperatura a registrar
     */
    void registrarLectura(float valor);
    
    /**
     * @brief Procesa las lecturas: elimina el mínimo y calcula promedio
     */
    void procesarLectura();
    
    /**
     * @brief Imprime la información del sensor
     */
    void imprimirInfo() const;
};

#endif // SENSOR_TEMPERATURA_H