# 🅿️ FisgonParkingMain: Monitoreo IoT de Parqueaderos  

## 1. Introducción y Resumen del Proyecto  
Este repositorio contiene la implementación completa del proyecto de tesis:  

**DISEÑO E IMPLEMENTACIÓN DE UN SISTEMA PROTOTIPO DE MONITOREO PARA LOS PARQUEADEROS DEL EDIFICIO MATRIZ DEL INSTITUTO SUPERIOR TECNOLÓGICO SUDAMERICANO, QUITO.**

**FisgonParkingMain** es un sistema prototipo de monitoreo de disponibilidad de parqueaderos que utiliza **hardware de bajo costo** (módulos ESP) y **sensores ultrasónicos** para ofrecer una solución de gestión en tiempo real.  

El proyecto aborda la necesidad de optimizar el **tiempo de búsqueda** y la **eficiencia en el uso de los estacionamientos institucionales**.  
Los datos de disponibilidad se capturan de forma distribuida y se consolidan en un servidor central, que luego expone una **interfaz web** para su visualización remota.  

---

## 2. Arquitectura del Sistema (IoT Distribuido)  
El sistema opera bajo una **arquitectura de Internet de las Cosas (IoT)** con un modelo de comunicación **Cliente-Servidor (Maestro-Esclavo)** y transmisión de datos ligera vía **UDP**.  

### 2.1 Componentes Principales  

| **Componente**       | **Descripción** | **Tecnologías Clave** |
|-----------------------|-----------------|------------------------|
| **ESP Cliente (Esclavo)** | Módulo de adquisición de datos. Captura la distancia con sensores ultrasónicos, formatea la información y la transmite al servidor. | C/C++ (Arduino), Sensores Ultrasónicos, Comunicación UDP |
| **ESP Servidor (Maestro)** | Núcleo del sistema. Recibe, clasifica y procesa los paquetes UDP de todos los clientes, actualizando las variables de estado de las plazas. | C/C++ (Arduino), Comunicación UDP, Servidor Web HTTP |
| **Interfaz de Monitoreo** | Página web levantada directamente por el ESP Servidor, que visualiza el estado de las plazas en tiempo real usando scripts internos. | HTML, CSS, JavaScript |

---

### 2.2 Flujo Lógico de Funcionamiento  

![Diagrama de flujo 1](./imagenes del proyecto)

1. **Captura de Datos:**  
   Los **ESP Clientes** miden constantemente la distancia de las plazas con sensores ultrasónicos.  

2. **Transmisión:**  
   La información formateada (paquetes de datos) se envía al **ESP Servidor** a través de la red **Wi-Fi** usando el protocolo **UDP (User Datagram Protocol)**, asegurando una transmisión rápida y continua.  

3. **Procesamiento:**  
   El **ESP Servidor** clasifica los paquetes recibidos y actualiza variables internas con la disponibilidad de cada plaza.  

4. **Visualización Remota:**  
   El servidor genera y aloja una **página web** que usa **JavaScript** para indexar y actualizar el estado de las plazas en intervalos definidos, ofreciendo la vista en **tiempo real** a través del túnel **Ngrok**.  

---

## 3. Tecnologías y Lenguajes Implementados  

El proyecto combina **programación embebida de bajo nivel** con **desarrollo web** para la interfaz de usuario.  

| **Categoría**            | **Herramienta**            | **Propósito** |
|---------------------------|-----------------------------|---------------|
| **Programación Embebida** | C / C++ (Arduino)           | Firmware de los módulos ESP Cliente y Servidor |
| **Hardware**              | Módulos ESP (ESP8266/ESP32) | Dispositivos principales para conectividad Wi-Fi y procesamiento |
| **Web Frontend**          | HTML, CSS, JavaScript       | Desarrollo de la interfaz de monitoreo web |
| **IDE Principal**         | Visual Studio Code          | Entorno de desarrollo para código y archivos web |
| **Networking / Túnel**    | Ngrok                       | Creación de un túnel público para acceder al portal web local del ESP Servidor desde Internet |

---

## 4. Estructura del Repositorio  

El código está organizado siguiendo la **separación de roles** de los módulos **ESP Cliente** y **ESP Servidor**, además de incluir toda la **documentación gráfica** y **archivos de apoyo** necesarios para la implementación y pruebas.  



