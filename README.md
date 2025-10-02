🅿️ FisgonParkingMain: Monitoreo IoT de Parqueaderos
📋 Tabla de Contenidos
Introducción

Arquitectura del Sistema

Componentes Principales

Instalación

Uso

Tecnologías

🚀 Introducción
Este repositorio contiene la implementación completa del proyecto de tesis:
DISEÑO E IMPLEMENTACIÓN DE UN SISTEMA PROTOTIPO DE MONITOREO PARA LOS PARQUEADEROS DEL EDIFICIO MATRIZ DEL INSTITUTO SUPERIOR TECNOLÓGICO SUDAMERICANO, QUITO.

FisgonParkingMain es un sistema prototipo de monitoreo de disponibilidad de parqueaderos que utiliza hardware de bajo costo (módulos ESP) y sensores ultrasónicos para ofrecer una solución de gestión en tiempo real.

El proyecto aborda la necesidad de optimizar el tiempo de búsqueda y la eficiencia en el uso de los estacionamientos institucionales. Los datos de disponibilidad se capturan de forma distribuida y se consolidan en un servidor central, que luego expone una interfaz web para su visualización remota.

🏗️ Arquitectura del Sistema
El sistema opera bajo una arquitectura de Internet de las Cosas (IoT) con un modelo de comunicación Cliente-Servidor (Maestro-Esclavo) y transmisión de datos ligera vía UDP.

Diagrama de Arquitectura
text
┌─────────────────┐    UDP    ┌─────────────────┐    HTTP    ┌─────────────────┐
│   ESP Cliente   │ ────────▶ │   ESP Servidor  │ ────────▶ │    Interfaz     │
│    (Esclavo)    │           │    (Maestro)    │           │     Web         │
└─────────────────┘           └─────────────────┘           └─────────────────┘
⚙️ Componentes Principales
Componente	Descripción	Tecnologías Clave
ESP Cliente (Esclavo)	Módulo de adquisición de datos. Captura la distancia con sensores ultrasónicos, formatea la información y la transmite al servidor.	C/C++ (Arduino), Sensores Ultrasónicos, Comunicación UDP
ESP Servidor (Maestro)	Núcleo del sistema. Recibe, clasifica y procesa los paquetes UDP de todos los clientes, actualizando las variables de estado de las plazas.	C/C++ (Arduino), Comunicación UDP, Servidor Web HTTP
Interfaz de Monitoreo	Página web levantada directamente por el ESP Servidor, que visualiza el estado de las plazas en tiempo real usando scripts internos.	HTML, CSS, JavaScript
