## main.py

from bst import BST
import os

# Nombre del archivo de persistencia (Opcional)
PERSISTENCE_FILE = "bst_keys.txt"

def display_help():
    """Muestra la lista de comandos disponibles."""
    print("\n--- Comandos Disponibles ---")
    print(f"  insert <num>         : Inserta un número en el BST.")
    print(f"  search <num>         : Busca un número y muestra el camino.")
    print(f"  delete <num>         : Elimina un número del BST.")
    print(f"  inorder              : Muestra el recorrido Inorden (ordenado).")
    print(f"  preorder             : Muestra el recorrido Preorden.")
    print(f"  postorder            : Muestra el recorrido Postorden.")
    print(f"  height               : Muestra la altura del árbol.")
    print(f"  size                 : Muestra el número total de nodos.")
    print(f"  export               : Guarda el recorrido inorden a '{PERSISTENCE_FILE}'.")
    print(f"  help                 : Muestra esta ayuda.")
    print(f"  exit                 : Sale del programa.")
    print("---------------------------\n")

def main_cli():
    """Función principal para la interfaz de consola."""
    bst = BST()
    
    # Persistencia Opcional: Cargar datos al inicio
    loaded_count = bst.load_keys(PERSISTENCE_FILE)
    print("===================================================")
    print("Gestor de Números con Árbol Binario de Búsqueda")
    print("===================================================")
    if loaded_count > 0:
        print(f"Se cargaron {loaded_count} claves desde '{PERSISTENCE_FILE}'.")
    else:
        print(f"ℹÁrbol vacío o archivo de claves no encontrado. Use 'insert <num>'.")
    print("Escriba 'help' para ver los comandos.")

    while True:
        try:
            command_line = input("\nBST > ").strip().split()
            if not command_line:
                continue

            command = command_line[0].lower()
            args = command_line[1:]
            
            # Validar si el argumento es un número para comandos que lo requieren
            if command in ['insert', 'search', 'delete']:
                if not args or not args[0].isdigit():
                    print(f"Error: El comando '{command}' requiere un número. Ejemplo: {command} 42")
                    continue
                key = int(args[0])

            # --- Manejo de Comandos ---
            
            if command == 'insert':
                bst.insert(key)
                print(f"Número {key} insertado.")
            
            elif command == 'search':
                node, path = bst.search(key)
                if node:
                    print(f"Número {key} encontrado.")
                    print(f"   Ruta: {' -> '.join(map(str, path))}")
                else:
                    print(f"Número {key} no encontrado.")
                    print(f"   Última ruta: {' -> '.join(map(str, path))}")

            elif command == 'delete':
                bst.delete(key) # La impresión de error/éxito se maneja dentro de delete
                print(f"Intento de eliminación de {key} completado.")
                
            elif command == 'inorder':
                result = bst.inorder()
                print(f"Inorden (Ordenado): {' '.join(map(str, result))}")
                
            elif command == 'preorder':
                result = bst.preorder()
                print(f"Preorden: {' '.join(map(str, result))}")

            elif command == 'postorder':
                result = bst.postorder()
                print(f"Postorden: {' '.join(map(str, result))}")

            elif command == 'height':
                h = bst.height()
                # La altura -1 para un árbol vacío y 0 para un nodo único
                # es estándar, pero se muestra de forma más amigable
                display_h = h if h >= 0 else 0
                print(f"Altura del árbol: {display_h} (Niveles: {display_h + 1})")

            elif command == 'size':
                s = bst.size()
                print(f"Número total de nodos: {s}")

            elif command == 'export':
                if bst.export_inorder(PERSISTENCE_FILE):
                    print(f"Recorrido Inorden guardado con éxito en '{PERSISTENCE_FILE}'.")
                
            elif command == 'help':
                display_help()

            elif command == 'exit':
                # Persistencia Opcional: Guardar el estado actual al salir
                if bst.size() > 0:
                     if bst.export_inorder(PERSISTENCE_FILE):
                        print(f"Guardando estado actual del Inorden en '{PERSISTENCE_FILE}' antes de salir...")
                else:
                    # Opcional: Eliminar el archivo si el árbol está vacío
                    if os.path.exists(PERSISTENCE_FILE):
                        os.remove(PERSISTENCE_FILE)
                        print(f"Archivo de persistencia eliminado, árbol vacío.")

                print("¡Adiós!")
                break
            
            else:
                print(f"Comando desconocido: '{command}'. Escriba 'help' para ver los comandos.")

        except EOFError:
            print("\nSaliendo del programa...")
            break
        except Exception as e:
            print(f"Error inesperado: {e}")

if __name__ == "__main__":
    main_cli()