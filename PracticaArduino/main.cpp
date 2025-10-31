/**
 * @file main.cpp
 * @brief Programa principal del Sistema IoT de Gestión de Sensores
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 * 
 * Este programa gestiona sensores de temperatura y presión mediante
 * una jerarquía polimórfica, listas enlazadas genéricas y lectura
 * del puerto serial de Arduino.
 */

#include <iostream>
#include "SensorBase.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ListaGeneral.h"
#include "SerialReader.h"

using namespace std;

/**
 * @brief Convierte una cadena a número float de forma manual
 * @param cadena Cadena a convertir
 * @return Valor float
 */
float cadenaAFloat(const char* cadena) {
    float resultado = 0.0;
    float decimal = 0.0;
    int i = 0;
    bool negativo = false;
    bool enDecimal = false;
    float divisor = 10.0;
    
    if (cadena[0] == '-') {
        negativo = true;
        i = 1;
    }
    
    while (cadena[i] != '\0') {
        if (cadena[i] == '.') {
            enDecimal = true;
            i = i + 1;
            continue;
        }
        
        int digito = cadena[i] - '0';
        
        if (!enDecimal) {
            resultado = resultado * 10.0 + digito;
        } else {
            decimal = decimal + digito / divisor;
            divisor = divisor * 10.0;
        }
        
        i = i + 1;
    }
    
    resultado = resultado + decimal;
    
    if (negativo) {
        resultado = -resultado;
    }
    
    return resultado;
}

/**
 * @brief Convierte una cadena a número entero de forma manual
 * @param cadena Cadena a convertir
 * @return Valor entero
 */
int cadenaAInt(const char* cadena) {
    int resultado = 0;
    int i = 0;
    bool negativo = false;
    
    if (cadena[0] == '-') {
        negativo = true;
        i = 1;
    }
    
    while (cadena[i] != '\0') {
        int digito = cadena[i] - '0';
        resultado = resultado * 10 + digito;
        i = i + 1;
    }
    
    if (negativo) {
        resultado = -resultado;
    }
    
    return resultado;
}

/**
 * @brief Busca un carácter en una cadena
 * @param cadena Cadena donde buscar
 * @param caracter Carácter a buscar
 * @return Posición del carácter, -1 si no se encuentra
 */
int buscarCaracter(const char* cadena, char caracter) {
    int i = 0;
    while (cadena[i] != '\0') {
        if (cadena[i] == caracter) {
            return i;
        }
        i = i + 1;
    }
    return -1;
}

/**
 * @brief Copia parte de una cadena
 * @param destino Cadena destino
 * @param origen Cadena origen
 * @param inicio Posición inicial
 * @param fin Posición final
 */
void subcadena(char* destino, const char* origen, int inicio, int fin) {
    int j = 0;
    for (int i = inicio; i < fin && origen[i] != '\0'; i++) {
        destino[j] = origen[i];
        j = j + 1;
    }
    destino[j] = '\0';
}

/**
 * @brief Muestra el menú principal
 */
void mostrarMenu() {
    cout << "\n========================================" << endl;
    cout << "  Sistema IoT de Monitoreo Polimorfico" << endl;
    cout << "========================================" << endl;
    cout << "1. Crear Sensor de Temperatura" << endl;
    cout << "2. Crear Sensor de Presion" << endl;
    cout << "3. Leer datos desde Arduino (automatico)" << endl;
    cout << "4. Registrar lectura manual" << endl;
    cout << "5. Ejecutar procesamiento polimorfico" << endl;
    cout << "6. Mostrar todos los sensores" << endl;
    cout << "7. Salir" << endl;
    cout << "Opcion: ";
}

/**
 * @brief Función principal
 */
int main() {
    ListaGeneral listaSensores;
    SerialReader* serial = 0;
    
    cout << "===========================================\n";
    cout << "  SISTEMA IOT DE GESTION DE SENSORES\n";
    cout << "===========================================\n" << endl;
    
    // Preguntar si desea conectar Arduino
    cout << "Desea conectar con Arduino? (s/n): ";
    char respuesta;
    cin >> respuesta;
    cin.ignore(); // Limpiar buffer
    
    if (respuesta == 's' || respuesta == 'S') {
        cout << "\nIngrese el nombre del puerto serial:" << endl;
        cout << "  Windows: COM3, COM4, etc." << endl;
        cout << "  Linux: /dev/ttyUSB0, /dev/ttyACM0, etc." << endl;
        cout << "Puerto: ";
        
        char nombrePuerto[50];
        cin.getline(nombrePuerto, 50);
        
        serial = new SerialReader(nombrePuerto);
        
        if (!serial->estaConectado()) {
            cout << "[Advertencia] Continuando sin Arduino..." << endl;
            delete serial;
            serial = 0;
        }
    }
    
    // Crear sensores iniciales
    cout << "\n--- Creando sensores iniciales ---" << endl;
    SensorTemperatura* temp1 = new SensorTemperatura("T-001");
    listaSensores.insertar(temp1);
    
    SensorPresion* pres1 = new SensorPresion("P-105");
    listaSensores.insertar(pres1);
    
    bool continuar = true;
    int contadorLecturas = 0;
    
    while (continuar) {
        // Leer automáticamente del Arduino si está conectado
        if (serial != 0 && serial->estaConectado()) {
            char buffer[100];
            int bytesLeidos = serial->leerLinea(buffer, 100);
            
            if (bytesLeidos > 0) {
                cout << "\n[Arduino] Dato recibido: " << buffer << endl;
                
                // Procesar dato recibido
                int posDospuntos = buscarCaracter(buffer, ':');
                
                if (posDospuntos != -1) {
                    char tipo[10];
                    char valor[20];
                    
                    subcadena(tipo, buffer, 0, posDospuntos);
                    subcadena(valor, buffer, posDospuntos + 1, 100);
                    
                    // Comparar tipo
                    bool esTemp = true;
                    const char* tempStr = "TEMP";
                    for (int i = 0; i < 4; i++) {
                        if (tipo[i] != tempStr[i]) {
                            esTemp = false;
                            break;
                        }
                    }
                    
                    if (esTemp) {
                        float valorFloat = cadenaAFloat(valor);
                        temp1->registrarLectura(valorFloat);
                        contadorLecturas = contadorLecturas + 1;
                    } else {
                        int valorInt = cadenaAInt(valor);
                        pres1->registrarLectura(valorInt);
                        contadorLecturas = contadorLecturas + 1;
                    }
                    
                    // Procesar automáticamente cada 5 lecturas
                    if (contadorLecturas >= 5) {
                        cout << "\n[Sistema] Procesando automaticamente..." << endl;
                        listaSensores.procesarTodos();
                        contadorLecturas = 0;
                    }
                }
            }
        }
        
        mostrarMenu();
        
        int opcion;
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                cout << "\nIngrese el ID del sensor de temperatura: ";
                char id[50];
                cin.getline(id, 50);
                
                SensorTemperatura* nuevoTemp = new SensorTemperatura(id);
                listaSensores.insertar(nuevoTemp);
                cout << "Sensor creado e insertado en la lista de gestion." << endl;
                break;
            }
            
            case 2: {
                cout << "\nIngrese el ID del sensor de presion: ";
                char id[50];
                cin.getline(id, 50);
                
                SensorPresion* nuevoPres = new SensorPresion(id);
                listaSensores.insertar(nuevoPres);
                cout << "Sensor creado e insertado en la lista de gestion." << endl;
                break;
            }
            
            case 3: {
                if (serial == 0 || !serial->estaConectado()) {
                    cout << "\n[Error] No hay conexion con Arduino." << endl;
                } else {
                    cout << "\n[Info] El sistema esta leyendo automaticamente del Arduino." << endl;
                    cout << "Las lecturas se procesan cada 5 datos recibidos." << endl;
                }
                break;
            }
            
            case 4: {
                cout << "\nIngrese el ID del sensor: ";
                char id[50];
                cin.getline(id, 50);
                
                SensorBase* sensor = listaSensores.buscar(id);
                
                if (sensor == 0) {
                    cout << "Sensor no encontrado." << endl;
                    break;
                }
                
                cout << "Tipo de sensor (1=Temperatura, 2=Presion): ";
                int tipo;
                cin >> tipo;
                
                if (tipo == 1) {
                    cout << "Ingrese valor (float): ";
                    float valor;
                    cin >> valor;
                    
                    SensorTemperatura* tempSensor = (SensorTemperatura*)sensor;
                    tempSensor->registrarLectura(valor);
                } else {
                    cout << "Ingrese valor (int): ";
                    int valor;
                    cin >> valor;
                    
                    SensorPresion* presSensor = (SensorPresion*)sensor;
                    presSensor->registrarLectura(valor);
                }
                break;
            }
            
            case 5: {
                listaSensores.procesarTodos();
                break;
            }
            
            case 6: {
                listaSensores.imprimirTodos();
                break;
            }
            
            case 7: {
                cout << "\nCerrando sistema..." << endl;
                continuar = false;
                break;
            }
            
            default: {
                cout << "\nOpcion invalida." << endl;
                break;
            }
        }
    }
    
 
    if (serial != 0) {
        delete serial;
    }
    
    return 0;
}