/**
 * @file SerialReader.h
 * @brief Clase para leer datos del puerto serial del Arduino
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef SERIAL_READER_H
#define SERIAL_READER_H

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <termios.h>
    #include <unistd.h>
#endif

/**
 * @class SerialReader
 * @brief Maneja la comunicación con el Arduino por puerto serial
 * 
 * Esta clase abstrae la lectura del puerto serial para Windows y Linux/Mac
 */
class SerialReader {
private:
#ifdef _WIN32
    HANDLE puerto;  ///< Handle del puerto en Windows
#else
    int puerto;     ///< File descriptor en Linux/Mac
#endif
    bool conectado; ///< Estado de la conexión
    
public:
    /**
     * @brief Constructor que intenta abrir el puerto
     * @param nombrePuerto Nombre del puerto (ej: "COM3" en Windows, "/dev/ttyUSB0" en Linux)
     */
    SerialReader(const char* nombrePuerto);
    
    /**
     * @brief Destructor que cierra el puerto
     */
    ~SerialReader();
    
    /**
     * @brief Verifica si el puerto está conectado
     * @return true si está conectado
     */
    bool estaConectado() const;
    
    /**
     * @brief Lee una línea del puerto serial
     * @param buffer Buffer donde se almacenará la línea
     * @param tamMax Tamaño máximo del buffer
     * @return Número de caracteres leídos, -1 si hay error
     */
    int leerLinea(char* buffer, int tamMax);
};

#endif // SERIAL_READER_H