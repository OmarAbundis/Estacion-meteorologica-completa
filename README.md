# Flow-7 Estación meteorológica completa
Este repositorio incluye los archivos para el ejercicio realizado en la clase de IoT, el cual envía información del sensor de temperatura y humedad **HT11** por **MQTT** a un Flow en **NodeRed**.


## Introducción
Como parte de las actividades de aprendizaje del IoT, el presente ejercicio corresponde a realizar una pequeña estación de clima, la cual debe de cumplir con los siguientes puntos.

- Obtener de la ubicación actual del usuario la temperatura ambiente y humedad relativa con el sensor DHT11 y como elemento control y procesador de señales, el microcontrolador ESP32CAM.
- Enviar la información adquirida por los sensores del circuito local en formato **JSON** por **MQTT**.
- Generar un Flow de control basado en el [flow5](https://github.com/OmarAbundis/Flow5), pero cumpliendo las siguientes características:
1. Obtener los valores correspondientes a la temperatura, humedad relativa, calidad del aire e índice ultravioleta por API de la página openweathermap.org.
2. Suscribirse a un Broker MQTT de tipo público, para obtener la información de datos climáticos de todos los alumnos que conforman el grupo 7.
3. Reportar por MQTT los datos obtenidos a través de la API para que puedan ser visualizados por cualquier otro integrante del grupo 7.
4. Enviar una señal de encendido y apagado del LED Flash incluido en el ESP32CAM, para indicar que se a rebasado la temperatura de 26°C.

## Material necesario

Para realizar la práctica se debe de contar con el siguiente material:

- MicrocontroladorbESP32CAM
- Convertidor FTDI
- Cable USB a USB-mini
- Jumpers MM
- Protoboard
- Sensor DHT11
- Un resistor de 10kohms

## Software necesario

En la experimentación de está práctica se debe de contar con el siguiente software libre:

- Ubuntu 20.04
- Arduino IDE
- Mosquitto MQTT Broker, Listener en puerto 1883 para 0.0.0.0 y conexiones autentificadas activadas.
- NodeJS. NPM, NodeRed y Node Dashboard.

## Material de referencia

Previamente a la realización de está práctica, ha sido necesario el estudio de distitos temas, que se encuentran en la plataforma edu.codigoiot.com, en donde se explican conceptos y configuraciones necesarias, tales como:

- Instalación de virtual Box y Ubuntu 20.04
- Configuración de Arduino IDE para ESP32CAM
- Instalación de NodeRed
- Introducción a NodeRed
- Instalación de Mosquitto MQTT

## Servicios

Adicional a lo ya indicado en líneas superiores, también es necesario contar con los siguientes servicios:

- [HiveMQ](https://www.hivemq.com/). Es un broker público y que no demanda de contar con una cuenta.
- [OpenWeatherMap](https://openweathermap.org/). Página de la cual se tomaran las APIs que proporcionan la temperatura, humedad, índice de radiación UV y nivel de contaminación de una región especifica.
- [GoogleMaps](https://www.google.com.mx/maps/preview). Para localizar las coordenas del área geográfica del cual se tomaran las mediones para la API.

## Instrucciones para la realización de la práctica

Para una experimentación satisfactoria es necesario cumplir lo siguiente:

1. Realizar el armado del circuito mostrado en la figura 1.
   
**Figura 1.** *Circuito electrónico*
![](https://github.com/OmarAbundis/Sensor-de-temperatura-humedad-local/blob/main/imagenes/ESP32%20CAM%20y%20DTH11.png)

2. Realizar el programa de control, tomando como base el programa [ESP32CAM-Wi-Fi-Basic](https://github.com/codigo-iot/ESP32CAM-WiFi-Basic/blob/main/ESP32CAM-WiFi-Basic/ESP32CAM-WiFi-Basic.ino), proporcionado por el profesor. En el programa base se tienen que realizar los siguiente cambios.
- El tema de publicación y suscripción.
- Nombre de red y contraseña al que deseas conectarte.
- Tiempo de espera entre envío de datos en una escala de tiempo de milisegundos.

3. Arrancar NodeRed y cargar el Flow7. Se debe de modificar

- Temas MQTT a reportar.
- Coordenadas geográficas usadas para hacer la petición API a OpenWeatherMAp.
- API key. Generar las API Keys para hacer uso del servicio de OpenWeatherMAp.
- Temperatura umbral para envíar señal de encendido del ledFlash para indicar que se ha rebasado la temperatura de 26°C, propuesta.

4. Polarizar el circuito electrónico y garantizar el rango de covertura de la señal WiFi, no mayor a 3 metros.

## Instrucciones de operación

Ya realizado el Flow7 y hecho **Deploy** en NodeRed, es necesario abrir el dashboard, el cual redirecciona a la página [http://localHost:1880/ui](http://localHost:1880//ui).

## Resultados

En la figura 2, comprueba primeramente el envío de datos usando la terminal de Ubuntu, ya suscrito al tema.

**Figura 2.** *Visualización de datos en la terminal*
![Datos](https://github.com/OmarAbundis/Sensor-de-temperatura-humedad-local/blob/main/imagenes/Evidencia%20en%20terminal%20sensores.PNG).

En la figura 3, se muestra una captura del Dashboard, con las gráficas correspondientes de los valores detectados de temperatura, humedad, UVI y calidad de aire; tanto personales y grupales.

**Figura 3**. *DashBoard estación climática.*
![Dashboard](https://github.com/OmarAbundis/Sensor-de-temperatura-humedad-local/blob/main/imagenes/Dash%20Estaci%C3%B3n%20meteorol%C3%B3gica%20Flow%207.PNG)

## Evidencias

A continuación se pueden ver enlaces a las evidencias de este proyecto:

- [Repositorio](https://github.com/OmarAbundis/Sensor-de-temperatura-humedad-local)
- YouTube

## Preguntas frecuentes



  **P: ¿Por qué no se conecta el ESP32CAM a mí WiFi?**

  **R:** Verifica que hayas colocado correctamente tu SSID y contraseña.
  **R:** Verifica que tu red tenga una conexión AES-WPA2.
  **R:** Asegurate que el microcontrolador se encuentra en el rango de alcance de tu red WiFi, menor a 3 metros.

  **P: ¿Qué significa el error BrownOut?**

  **R:** Significa que tu microcontrolador tiene sobre carga de ruido o le falta potencia de alimentación. Intenta moverlo un poco o conectarlo en un puerto USB diferente.
  **P: ¿Por qué no puedo ver la información en las gráficas del Dashboard?**
  
  **R:** Verifica que hayas escrito los mismos temas en los suscriptores y en los publicadores tanto de flow como del programa del ESP32CAM.
  **R:** Asegurate de tener una regla que permita conexiones en el puerto 1883 y tener correctamente configurado el archivo mosquitto.conf.
  **R:** Asegurate de buscar la IP más reciente del broker público, está es dinámica y cambia frecuentemente.

## Compatibilidad

Código directamente compatible con:

- Tarjeta de desarrollo ESP32CAM.
- Sensor DHT11.

## Créditos

Al profesor Hugo Escalpelo, instructor titular del curso IoT del grupo 7.