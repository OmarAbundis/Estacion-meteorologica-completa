# Flow-7 Estación meteorológica completa
Este repositorio incluye los archivos para el ejercicio realizado en la clase de IoT, el cual envía información del sensor de temperatura y humedad **HT11** por **MQTT** a un Flow en **NodeRed**.


## Introducción
Como parte de las actividades de aprendizaje del IoT, el presente ejercicio corresponde a realizar una pequeña estación de clima, la cual debe de cmplir con los siguientes puntos.

- Obtener de la ubicación actual del usuario la temperatura ambiente y humedad relativa con el sensor DHT11 y como elemento control y procesador de señales el microcontrolador ESP32CAM.
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





 