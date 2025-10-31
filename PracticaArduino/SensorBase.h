/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los sensores del sistema IoT
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

/**
 * @class SensorBase
 * @brief Clase abstracta que define la interfaz común para todos los sensores
 * 
 * Esta clase base establece el contrato que deben cumplir todos los sensores
 * del sistema mediante métodos virtuales puros.
 */
class SensorBase {
protected:
    char nombre[50]; ///< Identificador único del sensor
    
public:
    /**
     * @brief Constructor que inicializa el nombre del sensor
     * @param nom Nombre identificador del sensor
     */
    SensorBase(const char* nom);
    
    /**
     * @brief Destructor virtual para permitir polimorfismo
     */
    virtual ~SensorBase();
    
    /**
     * @brief Método virtual puro para procesar las lecturas del sensor
     * 
     * Cada sensor implementa su propia lógica de procesamiento:
     * - SensorTemperatura: elimina el valor más bajo
     * - SensorPresion: calcula el promedio
     */
    virtual void procesarLectura() = 0;
    
    /**
     * @brief Método virtual puro para imprimir información del sensor
     */
    virtual void imprimirInfo() const = 0;
    
    /**
     * @brief Obtiene el nombre del sensor
     * @return Puntero al nombre del sensor
     */
    const char* obtenerNombre() const;
};

#endif // SENSOR_BASE_H