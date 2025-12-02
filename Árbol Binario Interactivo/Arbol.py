import sys

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def create_tree():
    """Función para crear un árbol binario de forma recursiva (interactiva)"""
    while True:
        try:
            print("Presiona 0 para salir")
            print("Presiona 1 para un nuevo nodo")
            choice = int(input("Ingresa la opción: "))
            
            if choice == 0:
                return None
            elif choice == 1:
                data = int(input("Ingresa los datos: "))
                temp = Node(data)
                
                print(f"Ingresa el nodo hijo izquierdo de {data}")
                temp.left = create_tree()
                
                print(f"Ingresa el nodo hijo derecho de {data}")
                temp.right = create_tree()
                
                return temp
            else:
                print("Opción no válida. Intenta de nuevo.")
        except ValueError:
            print("Entrada no válida. Por favor, ingresa 0 o 1.")
            # Continuará el bucle para pedir una nueva entrada

# Ejemplo de uso:
# root = create_tree()