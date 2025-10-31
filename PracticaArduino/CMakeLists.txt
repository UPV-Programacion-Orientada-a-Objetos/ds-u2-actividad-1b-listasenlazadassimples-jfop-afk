# CMakeLists.txt para Sistema IoT de Gestión de Sensores
# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(SistemaIoTSensores VERSION 1.0 LANGUAGES CXX)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Archivos fuente
set(SOURCES
    main.cpp
    SensorBase.cpp
    SensorTemperatura.cpp
    SensorPresion.cpp
    ListaGeneral.cpp
    SerialReader.cpp
)

# Archivos de encabezado
set(HEADERS
    SensorBase.h
    SensorTemperatura.h
    SensorPresion.h
    ListaSensor.h
    ListaGeneral.h
    SerialReader.h
)

# Crear el ejecutable
add_executable(SistemaIoT ${SOURCES} ${HEADERS})

# Opciones de compilación dependiendo del sistema operativo
if(WIN32)
    # Para Windows no necesitamos bibliotecas adicionales
    message(STATUS "Configurando para Windows")
elseif(UNIX)
    # Para Linux/Mac podríamos necesitar pthread
    message(STATUS "Configurando para Unix/Linux")
endif()

# Configuración de instalación
install(TARGETS SistemaIoT DESTINATION bin)

# Información de compilación
message(STATUS "===================================")
message(STATUS "Sistema IoT de Gestión de Sensores")
message(STATUS "===================================")
message(STATUS "Archivos fuente: ${SOURCES}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER}")
message(STATUS "Estándar C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "===================================")