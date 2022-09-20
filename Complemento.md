## Flow-7 Estación meteorológica COMPLEMENTO

Para concluir con la actividad se solicitó añadir las lecturas tomadas del sensor de temperatura y humedad DHT11, crear una base de datos en MySQL, usar Grafana para mostra los datos de temperatura y humedad de todos los integrantes del taller y compartir las graficas en en Dashboard de la estación meteorológica.

Para garantizar el éxito de la práctica se tuvieron que cumplir con los siguientes pasos:

1. Comprobar el funcionamiento del flow 7
- Actualizar la IP del broker publico
- 35.157.153.222
- Comprobar el funcionamiento de la API Call
- Comprobar el funcionamiento del circuito
- Comprobar los temas mqtt en los que publica el prototipo
- Tema historico grupal sensores codigoIoT/g7/mosquitto/sensores
- Tema historico grupal API codigoIoT/g7/mosquitto/API

2. Agregar una sección MySQL
- Crear una nueva base de datos llamada **codigoIoT**
- Crear una nueva tabla llamda clima
- id, fecha, nombre, temperatura y humedad

3. Modificar el Nodo function Query

msg.topic = "INSERT INTO clima (nombre,temperatura,humedad) VALUES ('" + msg.payload.id + "'," + msg.payload.temp+ "," + msg.payload.hum + ");";
return msg;

