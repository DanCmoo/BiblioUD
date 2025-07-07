# Documento de Análisis de la Solución  
## Proyecto: BiblioUD

---

## 1. Introducción

Este documento analiza la solución implementada para el sistema **BiblioUD**, una aplicación de consola orientada a la gestión y consulta de información en una biblioteca universitaria, con fines académicos. Se describen los componentes principales, la estructura del proyecto, las decisiones técnicas, los flujos de información.

---

## 2. Estructura del Proyecto

La organización del código y los datos es clave para la mantenibilidad y la claridad del sistema. La estructura de carpetas del proyecto es la siguiente:

```
src/
├── data/
│   ├── autores.txt
│   ├── ediciones.txt
│   ├── editoriales.txt
│   └── obras.txt
├── datastructures/
│   ├── AVL.h
│   └── Lista.h
├── models/
│   ├── Autor.cpp, Autor.h
│   ├── Edicion.cpp, Edicion.h
│   ├── Editorial.cpp, Editorial.h
│   ├── Obra.cpp, Obra.h
├── persistence/
│   └── Persistence.h
└── main.cpp
```

- **data/**: Archivos de datos persistentes para las entidades principales.
- **datastructures/**: Estructuras de datos genéricas y especializadas (AVL, Lista).
- **models/**: Definición de clases de dominio y su implementación.
- **persistence/**: Lógica de serialización y deserialización.
- **main.cpp**: Punto de entrada del programa.

---

## 3. Componentes Principales

### 3.1 Estructuras y Algoritmos

- **Árbol AVL**:  
  Utilizados para almacenar y gestionar entidades (por ejemplo, autores y obras) permitiendo búsquedas, inserciones y eliminaciones eficientes. El AVL garantiza el balanceo automático y un desempeño óptimo en modelos donde se ejecutan búsquedas muy frecuentes.

- **Lista**:  
  Se emplea una estructura de lista para manejar las ediciones, priorizando la simplicidad en esos casos.

- **Persistencia en Archivos**:  
  Cada entidad principal se almacena en un archivo de texto separado dentro de `src/data/`, facilitando la recuperación y actualización de información sin depender de una base de datos externa.

### 3.2 Módulos y Clases

- **Clases de dominio**:  
  `Autor`, `Edicion`, `Editorial`, `Obra` encapsulan los datos y comportamientos de cada entidad. Un autor puede tener muchas obras, una obra puede tener muchas ediciones, y cada edición pertenece a una editorial.

- **Persistence**:  
  Clase genérica responsable de la persistencia de objetos mediante serialización/deserialización a archivos de texto.

---

## 4. Estructura de Almacenamiento de los Archivos

Los archivos ubicados en `src/data/` almacenan la información de cada entidad en formato texto, utilizando el carácter `|` como delimitador de campos y, cuando corresponde, el carácter `;` para listas de valores. Cada línea en el archivo representa una instancia de la entidad correspondiente con el siguiente formato, de acuerdo con sus clases asociadas:

- **autores.txt**  
  Cada línea almacena un autor, con los campos en este orden:
  ```
  idAutor|nombre|apellido|sexo|fechaNacimiento|ciudadNacimiento|paisNacimiento|ciudadResidencia|formacionBase|anioInicioLiteratura|anioPrimeraObra
  ```
  - Ejemplo: `1|Gabriel|García Márquez|1|1927-03-06|Aracataca|Colombia|Ciudad de México|Periodismo|1947|1955`

- **editoriales.txt**  
  Cada línea representa una editorial:
  ```
  idEditorial|nombre|ciudad|pais
  ```
  - Ejemplo: `1|Sudamericana|Buenos Aires|Argentina`

- **ediciones.txt**  
  Cada línea representa una edición de una obra:
  ```
  numeroEdicion|fechaPublicacion|idEditorial|ciudadPublicacion|nombreObra|idAutor
  ```
  - Ejemplo: `1|1967-05-30|1|Buenos Aires|Cien Años de Soledad|1`

- **obras.txt**  
  Cada línea representa una obra y almacena los IDs de las ediciones asociadas separados por `;`:
  ```
  nombreObra|tipoPoesia|idAutor|idEdicion1;idEdicion2;idEdicion3
  ```
  - Ejemplo: `Cien Años de Soledad|Novela|1|1;2`

> **Nota:**  
> - Los campos booleanos (como el sexo en Autor) se almacenan como `1` (masculino) o `0` (femenino).
> - Los identificadores cruzados (por ejemplo, `idAutor` en Obra o `idEditorial` en Edición) permiten la relación entre entidades.
> - El listado de IDs de ediciones en Obra permite asociar múltiples ediciones a una misma obra.

---

## 5. Flujos de Información

1. **Ingreso de Datos**:  
   El usuario interactúa con la aplicación desde la consola, ingresando información sobre autores, obras, ediciones y editoriales.

2. **Procesamiento**:  
   El sistema valida la información, actualiza las estructuras de datos en memoria (AVL, Lista), y aplica las reglas de negocio y relaciones entre entidades.

3. **Persistencia**:  
   Las modificaciones se reflejan en los archivos correspondientes dentro de `src/data/` para garantizar la durabilidad de los datos.

4. **Consulta**:  
   Las búsquedas y listados se realizan sobre las estructuras en memoria, aprovechando la eficiencia de los árboles balanceados.

---

## 6. Justificación de las Decisiones Técnicas

- **Uso de consola**:  
  Permite un enfoque didáctico y sencillo para la interacción con el usuario.

- **Propósito académico**:  
  El proyecto está diseñado para ilustrar la implementación y el uso de estructuras de datos avanzadas en un contexto realista.

- **Persistencia en archivos planos**:  
  Elegida para no depender de una base de datos y para poder aplicar y analizar nuestros propios algoritmos de almacenamiento.

- **Elección de estructuras de datos**:  
  - **AVL**: Seleccionado para los modelos que requieren búsquedas frecuentes, ya que mantiene el árbol equilibrado y asegura eficiencia.
  - **Lista**: Utilizada en ediciones por su simplicidad en la gestión de datos secuenciales.

- **Escalabilidad**:  
  Aunque no se ha establecido un volumen específico de datos esperado, la complejidad algorítmica de las estructuras empleadas permite al sistema soportar grandes cargas de información.

- **Modularidad y extensibilidad**:  
  Gracias al uso de templates en las estructuras de datos y la organización modular del código, el sistema puede ser extendido fácilmente para incluir nuevas entidades o funcionalidades.

---

## 7. Riesgos y Limitaciones

- **Escalabilidad limitada**:  
  El manejo de archivos planos puede no ser óptimo para volúmenes extremadamente grandes de datos o acceso concurrente.

- **Sin control transaccional**:  
  No hay garantías de atomicidad ante fallos durante la escritura de archivos.

- **Monousuario**:  
  La solución está orientada a un solo usuario/interfaz a la vez.

---

## 8. Conclusión

La solución propuesta para BiblioUD cumple con los objetivos académicos de claridad, eficiencia y modularidad. La estructura de carpetas, la selección de algoritmos y la estructura de almacenamiento de los archivos permiten una gestión eficiente de la información y proveen una base sólida para el análisis y aprendizaje en el contexto universitario.

---
