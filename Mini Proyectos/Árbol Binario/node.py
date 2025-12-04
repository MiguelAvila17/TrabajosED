## node.py

class Nodo:
    """
    Representa un nodo en el Árbol Binario de Búsqueda (BST).
    """
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

    def __str__(self):
        return f"Nodo({self.key})"