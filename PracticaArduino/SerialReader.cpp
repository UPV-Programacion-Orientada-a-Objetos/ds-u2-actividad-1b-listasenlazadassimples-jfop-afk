/**
 * @file SerialReader.cpp
 * @brief Implementación del lector del puerto serial
 */

#include "SerialReader.h"
#include <iostream>

using namespace std;

SerialReader::SerialReader(const char* nombrePuerto) {
    conectado = false;
    
#ifdef _WIN32
    // Código para Windows
    puerto = CreateFileA(nombrePuerto,
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         0,
                         OPEN_EXISTING,
                         0,
                         0);
    
    if (puerto == INVALID_HANDLE_VALUE) {
        cout << "[Error] No se pudo abrir el puerto " << nombrePuerto << endl;
        return;
    }
    
    DCB parametros = {0};
    parametros.DCBlength = sizeof(parametros);
    
    if (!GetCommState(puerto, &parametros)) {
        cout << "[Error] No se pudo obtener el estado del puerto" << endl;
        return;
    }
    
    parametros.BaudRate = CBR_9600;
    parametros.ByteSize = 8;
    parametros.StopBits = ONESTOPBIT;
    parametros.Parity = NOPARITY;
    
    if (!SetCommState(puerto, &parametros)) {
        cout << "[Error] No se pudieron configurar los parametros" << endl;
        return;
    }
    
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    
    if (!SetCommTimeouts(puerto, &timeouts)) {
        cout << "[Error] No se pudieron configurar los timeouts" << endl;
        return;
    }
    
    conectado = true;
    cout << "[OK] Puerto " << nombrePuerto << " abierto correctamente" << endl;
    
#else
    // Código para Linux/Mac
    puerto = open(nombrePuerto, O_RDWR | O_NOCTTY);
    
    if (puerto < 0) {
        cout << "[Error] No se pudo abrir el puerto " << nombrePuerto << endl;
        return;
    }
    
    struct termios opciones;
    tcgetattr(puerto, &opciones);
    
    cfsetispeed(&opciones, B9600);
    cfsetospeed(&opciones, B9600);
    
    opciones.c_cflag &= ~PARENB;
    opciones.c_cflag &= ~CSTOPB;
    opciones.c_cflag &= ~CSIZE;
    opciones.c_cflag |= CS8;
    opciones.c_cflag &= ~CRTSCTS;
    opciones.c_cflag |= CREAD | CLOCAL;
    
    opciones.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    opciones.c_oflag &= ~OPOST;
    opciones.c_iflag &= ~(IXON | IXOFF | IXANY);
    
    tcsetattr(puerto, TCSANOW, &opciones);
    
    conectado = true;
    cout << "[OK] Puerto " << nombrePuerto << " abierto correctamente" << endl;
#endif
}

SerialReader::~SerialReader() {
    if (conectado) {
#ifdef _WIN32
        Cl