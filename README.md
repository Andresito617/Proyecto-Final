# ¡Bienvenido a "Conectando Ciudades"!

---

## 🗺️ Descripción del Proyecto

"Conectando Ciudades" es una aplicación de consola desarrollada en C++ que simula un mapa interactivo de ciudades y rutas. El objetivo principal es visualizar una red de transporte donde las ciudades están conectadas por rutas de diferentes colores, y eventualmente, estas rutas pueden ser "tomadas" por jugadores.

Este proyecto ha sido desarrollado con un enfoque en la claridad del código y la representación visual en la terminal, utilizando coordenadas de cuadrícula y códigos de color ANSI para una experiencia inmersiva.

---

## ✨ Características Principales

* **Mapa de Ciudades:** Representación en cuadrícula de diversas ciudades.
* **Rutas Coloreadas:** Conexiones entre ciudades visualizadas con caracteres 'X' y colores específicos (Rojo, Azul, Marrón, etc.) utilizando códigos ANSI.
* **Gestión de Rutas:** Capacidad para definir rutas con sus IDs de origen/destino, color y longitud.
* **Diseño Modular:** Separación de responsabilidades en clases como `Ciudad`, `Ruta`, `Mapa` y `BoardRenderer` para facilitar la comprensión y el mantenimiento.

---

## 📝 Rúbrica de Evaluación

Este proyecto será evaluado siguiendo los siguientes criterios:

### 1. Funcionalidad (50%)

* **1.1 Inicialización del Mapa (15%):**
    * Todas las **ciudades** deben ser insertadas correctamente y ubicadas en el tablero en sus coordenadas predefinidas.
    * Todas las **rutas** deben ser instanciadas con sus IDs correctos, color y longitud.
* **1.2 Dibujo de Ciudades (10%):**
    * Cada ciudad debe ser representada con el carácter 'O' (u otro símbolo adecuado) en su posición exacta en la cuadrícula.
* **1.3 Dibujo de Rutas (25%):**
    * Cada segmento de ruta debe ser dibujado con el carácter 'X' en las coordenadas precisas que conectan las ciudades.
    * Las 'X' de cada ruta deben mostrarse con el **color correspondiente** (ej. 'X' de color rojo para una ruta roja).
    * No deben aparecer 'X' ni ningún otro carácter de ruta en posiciones incorrectas o donde no haya una ruta definida.

### 2. Estructura y Estilo del Código (30%)

* **2.1 Modularidad (10%):**
    * El proyecto debe estar bien organizado en clases (`Ciudad`, `Ruta`, `Mapa`, `BoardRenderer`, etc.), con responsabilidades claras y bien definidas para cada una.
    * Uso adecuado de archivos `.h` (encabezados) y `.cpp` (implementación).
* **2.2 Claridad y Legibilidad (10%):**
    * Nombres de variables, funciones y clases descriptivos y coherentes.
    * Comentarios adecuados que expliquen la lógica compleja o secciones importantes del código.
    * Formato consistente (indentación, espaciado).
* **2.3 Eficiencia y Buenas Prácticas (10%):**
    * Uso eficiente de estructuras de datos y algoritmos.
    * Manejo de memoria (si aplica).
    * Evitar código duplicado.

### 3. Documentación (20%)

* **3.1 README.md (15%):**
    * Contenido claro y completo que describa el proyecto, cómo compilarlo y ejecutarlo, tecnologías usadas, estructura del proyecto y esta rúbrica.
    * Formato Markdown adecuado para una lectura fácil.
* **3.2 Comentarios en el Código (5%):**
    * Comentarios internos que expliquen la lógica de las funciones, clases y secciones complejas.

---

## 🛠️ Tecnologías Utilizadas

* **C++:** Lenguaje de programación principal.
* **Compilador:** Compatible con C++11 o superior (ej. g++).
* **Terminal compatible con ANSI:** Para la correcta visualización de los colores en el mapa (la mayoría de las terminales modernas lo son, como GNOME Terminal, iTerm2, Windows Terminal, etc.).

---

## 🚀 Cómo Compilar y Ejecutar

Sigue estos pasos para poner en marcha el proyecto en tu sistema:

### Requisitos

* Un compilador de C++ (como G++).

### Pasos

1.  **Clonar el repositorio (si aplica) o descargar los archivos:**
    Si tu proyecto está en un repositorio Git:
    ```bash
    git clone <URL_DE_TU_REPOSITORIO>
    cd <nombre_del_proyecto>
    ```
    Si tienes los archivos localmente, navega a la carpeta raíz de tu proyecto.

2.  **Compilar el proyecto:**
    Abre una terminal en la raíz de tu proyecto y ejecuta el siguiente comando de compilación (ajusta los nombres de los archivos `.cpp` según sea necesario):

    ```bash
    g++ -o main main.cpp Mapa.cpp BoardRenderer.cpp Ciudad.cpp Ruta.cpp -std=c++11
    ```
    * `g++`: El compilador de C++.
    * `-o main`: Especifica que el ejecutable se llamará `main` (o el nombre que prefieras, ej. `juego_mapa`).
    * `main.cpp Mapa.cpp BoardRenderer.cpp Ciudad.cpp Ruta.cpp`: Son tus archivos fuente. Asegúrate de incluir todos los `.cpp` de tu proyecto.
    * `-std=c++11`: Asegura la compatibilidad con el estándar C++11, necesario para algunas características.

3.  **Ejecutar la aplicación:**
    Una vez compilado, puedes ejecutar la aplicación con:

    ```bash
    ./main
    ```
    En Windows, si compilaste con un `.exe`, sería `main.exe`.

---

## 📂 Estructura del Proyecto (Ejemplo)
