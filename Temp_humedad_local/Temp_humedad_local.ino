/*Programa que mada datos adquiridos con el sensor DHT11, procesado por ESP32-CAM y los datos
   tipo JSON enviados a través de MQTT a un Flow que sirve de estación meteorológica
 
  Realizado: Prof. Hugo Escalpelo
  Editado por: Alumno, Omar Abundis
 
  Fecha: 19 de agosto del 2022

  Notas del profesor:
  
  Este programa envía datos a por Internet a través del protocolo MQTT. Para poder
  comprobar el funcionamiento de este programa, es necesario conectarse a un broker
  y usar NodeRed para visualzar que la información se está recibiendo correctamente.
  Este programa no requiere componentes adicionales.
  
  Este programa está basado en "Conexión básica por MQTT del NodeMCU" y explica como
  enviar strings que contengan JSON para enviar mas de una variable a la vez.
 
   Example testing sketch for various DHT humidity/temperature sensors written by ladyada
  REQUIRES the following Arduino libraries:
  - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
 - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
*/

/*          Componentes   Pines del ESP32-CAM     estados lógicos
 *           
 *          -> ledStatus------GPIO 33---------On=>LOW,  Off=>HIGH
 *          -> ledFlash-------GPIO 4----------On=>HIGH, Off=>LOW
 * 
 *                        Pines del ESP32-CAM       Pines del DHT11    
 *                            
 *                            GPIO 2----------------- DATA
 *                            5V     ------------------Vcc
 *                            GND    ------------------Gnd
 *                            
 *     Referencia de terminales DHT 11                       
 *     https://www.omniblug.com/sensor-temperatura-humedad-DHT11-DHT22.html
 */

// BIBLIOTECAS

#include <WiFi.h>           // Biblioteca para el control de WiFi
#include <PubSubClient.h>   //Biblioteca para conexion MQTT
#include <DHT.h>            //Biblioteca para el control del DHT11

//Datos de WiFi

const char* ssid = "INFINITUMB46E_2.4";   // Aquí debes poner el nombre de tu red
const char* password = "4520297937";      // Aquí debes poner la contraseña de tu red

//Datos del broker MQTT

const char* mqtt_server = "192.168.1.64"; // Si estas en una red local, coloca la IP asignada, en caso contrario, coloca la IP publica
IPAddress server(192,168,1,64);


#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define DHTPIN 2     // Digital pin connected to the DHT sensor


// Objetos

WiFiClient espClient;                     // Este objeto maneja los datos de conexion WiFi
PubSubClient client(espClient);           // Este objeto maneja los datos de conexion al broker
DHT dht(DHTPIN, DHTTYPE);                 // Objeto que inicia el sensor

// Variables

int flashLedPin = 4;                      // Para mostrar mensajes recibidos
int statusLedPin = 33;                    // Para indicar el estatus de conexión
long timeNow, timeLast;                   // Variables de control de tiempo no bloqueante
int wait = 5000;                          // Indica la espera cada 5 segundos para envío de mensajes MQTT



// Inicialización del programa

void setup() 
{
  // Iniciar comunicación serial
  
  Serial.begin (115200);
  Serial.println ("programa iniciado");
 
  pinMode (flashLedPin, OUTPUT);
  pinMode (statusLedPin, OUTPUT);
  digitalWrite (flashLedPin, LOW);
  digitalWrite (statusLedPin, HIGH);

  Serial.println();
  Serial.println();
  Serial.print("Conectar a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password); // Esta es la función que realiz la conexión a WiFi
 
  while (WiFi.status() != WL_CONNECTED) 
  { // Este bucle espera a que se realice la conexión
    
    digitalWrite (statusLedPin, HIGH);
    delay(500);         //dado que es de suma importancia esperar a la conexión, debe usarse espera bloqueante
    digitalWrite (statusLedPin, LOW);
    Serial.print(".");  // Indicador de progreso
    delay (5);
  }
  
  // Cuando se haya logrado la conexión, el programa avanzará, por lo tanto, puede informarse lo siguiente
  
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Si se logro la conexión, encender led
  
  if (WiFi.status () > 0)
  {
    digitalWrite (statusLedPin, LOW);
  }
  
  delay (1000); // Esta espera es solo una formalidad antes de iniciar la comunicación con el broker

  // Conexión con el broker MQTT
  
  client.setServer(server,1883); // Conectarse a la IP del broker en el puerto indicado
  client.setCallback(callback); // Activar función de CallBack, permite recibir mensajes MQTT y ejecutar funciones a partir de ellos
  delay(1500);  // Esta espera es preventiva, espera a la conexión para no perder información

  dht.begin();                  //Función que inicia el sensor
  timeLast = millis ();         // Inicia el control de tiempo
  
}// fin del void setup ()


// Cuerpo del programa, bucle principal

void loop() 
{
                //Verificar siempre que haya conexión al broker
  
  if (!client.connected()) 
  {
    reconnect();  // En caso de que no haya conexión, ejecutar la función de reconexión, definida despues del void setup ()
  }               // fin del if (!client.connected())
  
  client.loop(); // Esta función es muy importante, ejecuta de manera no bloqueante las funciones necesarias para la comunicación con el broker
  
  timeNow = millis(); // Control de tiempo para esperas no bloqueantes
  if (timeNow - timeLast > wait) 
  { // Manda un mensaje por MQTT cada cinco segundos
    
    timeLast = timeNow; // Actualización de seguimiento de tiempo

                // Obtener temperatura y humedad relativa

    float t = dht.readTemperature();      //Adquisición de la temperatura.
    float h = dht.readHumidity();         //Adqusición de la humedad

      // Check if any reads failed and exit early (to try again).
      
    if (isnan(h) || isnan(t)) 
    {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    }
      
    //Se construye el string correspondiente al JSON que contiene 3 variables
    
    String json = "{\"id\":\"OmarAb\",\"temp\":"+String(t)+",\"hum\":"+String(h)+"}";
    
    Serial.println(json); // Se imprime en monitor solo para poder visualizar que el string esta correctamente creado
    
    int str_len = json.length() + 1;        //Se calcula la longitud del string
    char char_array[str_len];               //Se crea un arreglo de caracteres de dicha longitud
    json.toCharArray(char_array, str_len);  //Se convierte el string a char array    
    client.publish("codigoIoT/ejemplo/mqtt", char_array); // Esta es la función que envía los datos por MQTT, especifica el tema y el valor
    
  }// fin del if (timeNow - timeLast > wait)
}// fin del void loop ()

// Funciones de usuario

// Esta función permite tomar acciones en caso de que se reciba un mensaje correspondiente a un tema al cual se hará una suscripción

void callback(char* topic, byte* message, unsigned int length) 
{
  
  // Indicar por serial que llegó un mensaje
  
  Serial.print("Llegó un mensaje en el tema: ");
  Serial.print(topic);

  // Concatenar los mensajes recibidos para conformarlos como una varialbe String
  
  String messageTemp;                 // Se declara la variable en la cual se generará el mensaje completo  
  
  for (int i = 0; i < length; i++) 
  {  // Se imprime y concatena el mensaje
    
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  // Se comprueba que el mensaje se haya concatenado correctamente
  
  Serial.println();
  Serial.print ("Mensaje concatenado en una sola variable: ");
  Serial.println (messageTemp);

  // En esta parte puedes agregar las funciones que requieras para actuar segun lo necesites al recibir un mensaje MQTT

  // Ejemplo, en caso de recibir el mensaje true - false, se cambiará el estado del led soldado en la placa.
  // El ESP323CAM está suscrito al tema codigoIoT/ejemplo/mqttin
  
  if (String(topic) == "codigoIoT/ejemplo/mqttin") 
    {  // En caso de recibirse mensaje en el tema codigoIoT/ejemplo/mqttin
      if(messageTemp == "true")
      {
        Serial.println("Led encendido");
        digitalWrite(flashLedPin, HIGH);
      }// fin del if (String(topic) == "")
      
      else if(messageTemp == "false")
      {
        Serial.println("Led apagado");
        digitalWrite(flashLedPin, LOW);
      }// fin del else if(messageTemp == "false")
      
    }// fin del if (String(topic) == "esp32/output")
    
}// fin del void callback

// Función para reconectarse

void reconnect() 
{
  // Bucle hasta lograr conexión
  while (!client.connected()) { // Pregunta si hay conexión
  Serial.print("Tratando de contectarse...");
    // Intentar reconexión
    
  if (client.connect("ESP32CAMClient")) 
  { //Pregunta por el resultado del intento de conexión
    
    Serial.println("Conectado");
    client.subscribe("codigoIoT/ejemplo/mqttin"); // Esta función realiza la suscripción al tema
    
    }// fin del  if (client.connect("codigoIoT/ejemplo/mqttin"))
    
   else 
   {  //en caso de que la conexión no se logre
    
     Serial.print("Conexion fallida, Error rc=");
     Serial.print(client.state()); // Muestra el codigo de error
     Serial.println(" Volviendo a intentar en 5 segundos");
    
     delay(5000);  // Espera de 5 segundos bloqueante
     
     Serial.println (client.connected ()); // Muestra estatus de conexión
    }// fin del else
  }// fin del bucle while (!client.connected())
}// fin de void reconnect(
