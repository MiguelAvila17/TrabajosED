# 🌳 Gestor de Números con Árbol Binario de Búsqueda (BST) en Consola

Este proyecto implementa un Árbol Binario de Búsqueda (BST) para gestionar números enteros, ofreciendo una interfaz de consola simple para la manipulación y visualización de la estructura de datos.

## 📝 Resumen del Proyecto

La aplicación permite al usuario realizar las operaciones fundamentales de un BST: **inserción**, **búsqueda** y **eliminación**. Además, facilita la práctica de los tres tipos de **recorridos** (preorden, inorden, posorden) y proporciona métricas como la **altura** y el **tamaño** del árbol.

## ⚙️ Requisitos Técnicos

* **Lenguaje de Programación:** Python 3.x

## 📁 Estructura del Proyecto

El código está organizado modularmente en tres archivos para mejorar la claridad y el mantenimiento:

| Archivo | Contenido | Responsabilidad |
| :--- | :--- | :--- |
| `node.py` | Clase `Nodo` | Define la estructura básica de cada elemento del árbol (clave, hijos izquierdo y derecho). |
| `bst.py` | Clase `BST` | Implementa toda la lógica del Árbol Binario de Búsqueda (inserción, eliminación, recorridos, etc.). |
| `main.py` | Función `main_cli` | Gestiona la Interfaz de Usuario de Consola (CLI) y la interacción con el usuario. |

## 🚀 Instrucciones de Compilación y Ejecución

No se requiere compilación, solo la ejecución directa del archivo principal de Python.

1.  **Clonar/Descargar el Repositorio:** Asegúrate de tener los archivos `node.py`, `bst.py`, y `main.py` en el mismo directorio.
2.  **Abrir la Terminal:** Navega al directorio del proyecto.
3.  **Ejecución:** Inicia la aplicación con el siguiente comando:

    ```bash
    python main.py
    ```

## 📋 Comandos de la Interfaz de Consola

Una vez iniciada la aplicación, se mostrará el *prompt* `BST >`. Utiliza el comando `help` para ver esta lista dentro de la aplicación.

| Comando | Sintaxis | Descripción |
| :--- | :--- | :--- |
| **`insert`** | `insert <num>` | Inserta un nuevo número entero en el árbol. |
| **`search`** | `search <num>` | Busca un número y muestra si existe, indicando la ruta desde la raíz. |
| **`delete`** | `delete <num>` | Elimina un número. Maneja los casos de 0, 1 o 2 hijos. |
| **`inorder`** | `inorder` | Muestra el recorrido en orden (números ordenados). |
| **`preorder`** | `preorder` | Muestra el recorrido en preorden. |
| **`postorder`** | `postorder` | Muestra el recorrido en postorden. |
| **`height`** | `height` | Muestra la altura del árbol (longitud del camino más largo). |
| **`size`** | `size` | Muestra el número total de nodos en el árbol. |
| **`export`** | `export` | Guarda el recorrido inorden actual en el archivo `bst_keys.txt`. |
| **`help`** | `help` | Muestra la lista de comandos disponibles. |
| **`exit`** | `exit` | Cierra la aplicación (y guarda el estado del árbol si hay nodos). |

## 📊 Casos de Prueba Recomendados

Se recomienda ejecutar la siguiente secuencia para validar la funcionalidad completa:

1.  **Inserción:** Inserta los números `45 15 79 90 10 55 12 20 50`.
2.  **Verificación Inorden:** Ejecuta `inorder`. La salida debe ser: `10 12 15 20 45 50 55 79 90`.
3.  **Búsqueda:**
    * `search 20` (Debe existir).
    * `search 100` (No debe existir).
4.  **Eliminación y Verificación de Casos:**
    * `delete 90` (Elimina una **hoja**).
    * `delete 79` (Elimina un nodo con **un hijo**).
    * `delete 45` (Elimina un nodo con **dos hijos**).
    * Verifica el nuevo orden con `inorder`.

## 📈 Comentarios sobre la Complejidad Temporal

Las operaciones fundamentales de un BST tienen una complejidad que depende de la altura ($h$) del árbol.

| Operación | Complejidad Promedio | Complejidad Peor Caso |
| :--- | :--- | :--- |
| **Inserción** | $O(\log n)$ | $O(n)$ |
| **Búsqueda** | $O(\log n)$ | $O(n)$ |
| **Eliminación** | $O(\log n)$ | $O(n)$ |
| **Recorridos** (Inorden, Preorden, Postorden) | $O(n)$ | $O(n)$ |

> **Nota:** El peor caso ($O(n)$) ocurre cuando el árbol está completamente desbalanceado (degenerado, como una lista enlazada).

## 💾 Persistencia

El programa soporta persistencia básica:
* Al ejecutar el comando **`export`** o **`exit`**, el recorrido Inorden del árbol se guarda en el archivo **`bst_keys.txt`**.
* Al **iniciar** la aplicación (`python main.py`), si `bst_keys.txt` existe, el árbol será reconstruido automáticamente a partir de las claves guardadas.

---