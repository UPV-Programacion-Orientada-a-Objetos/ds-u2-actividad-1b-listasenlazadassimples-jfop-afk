/**
 * @file arduino_sensor.ino
 * @brief Simulador de sensores IoT para Arduino
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 * 
 * Este sketch simula sensores de temperatura y presión,
 * enviando datos por el puerto serial en formato:
 * TEMP:valor o PRES:valor
 */

/**
 * @brief Configuración inicial del Arduino
 * 
 * Se ejecuta una sola vez al iniciar el Arduino.
 * Configura la comunicación serial a 9600 baudios.
 */
void setup() {
  // Iniciar comunicación serial a 9600 baudios
  Serial.begin(9600);
  
  // Inicializar generador de números aleatorios
  randomSeed(analogRead(0));
  
  // Mensaje de inicio
  Serial.println("=================================");
  Serial.println("Simulador de Sensores IoT");
  Serial.println("Enviando datos al sistema...");
  Serial.println("=================================");
  delay(2000);
}

/**
 * @brief Bucle principal que se ejecuta continuamente
 * 
 * Envía lecturas simuladas de temperatura y presión
 * alternadamente cada 2 segundos.
 */
void loop() {
  // Simular sensor de temperatura
  // Genera valores entre 20.0 y 50.0 grados Celsius
  float temperatura = 20.0 + random(0, 300) / 10.0;
  
  // Enviar temperatura en formato: TEMP:valor
  Serial.print("TEMP:");
  Serial.println(temperatura);
  
  // Esperar 2 segundos
  delay(2000);
  
  // Simular sensor de presión
  // Genera valores entre 70 y 120 unidades
  int presion = random(70, 120);
  
  // Enviar presión en formato: PRES:valor
  Serial.print("PRES:");
  Serial.println(presion);
  
  // Esperar 2 segundos antes de la siguiente lectura
  delay(2000);
}