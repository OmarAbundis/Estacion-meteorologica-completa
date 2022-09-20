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

### Configuración de MySQL en terminal de Ubuntu

1. Instalar mysql server
+ `sudo apt update`
+ `sudo apt install mysql-server`

2. Entrar a mysql con la instrucción:
   
   `sudo mysql`

3. Crear una nueva base de datos
   
    `CREATE DATABASE codigoIoT;`

4. Seleccionar base de datos 
   
    `use DetectorSintomas;`

5. Crear una tabla llamada **clima** que contenga todos los campos necesarios
    
    `create table clima (id INT (6) UNSIGNED AUTO_INCREMENT PRIMARY KEY, fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP, nombre CHAR (248) NOT NULL, temperatura FLOAT (4,2), humedad INT (3));`

6. Crear un nuevo usuario de MySQL

    `CREATE USER 'newuser'@'localhost' IDENTIFIED BY 'password';
    GRANT ALL PRIVILEGES ON *.* TO 'OmarAbu'@'localhost';`


7. Para salir de los comandos de MySQL, usar el comando
   
    `exit;`
