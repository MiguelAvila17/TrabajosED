## bst.py

from node import Nodo

class BST:
    """
    Implementación del Árbol Binario de Búsqueda (BST).
    """
    def __init__(self):
        self.root = None

    # --- Operaciones Básicas ---

    # Complejidad: O(log n) en promedio, O(n) en el peor caso (árbol degenerado).
    def insert(self, key):
        """Inserta una clave en el BST."""
        if self.root is None:
            self.root = Nodo(key)
            return

        def _insert_rec(node, key):
            if key < node.key:
                if node.left is None:
                    node.left = Nodo(key)
                else:
                    _insert_rec(node.left, key)
            elif key > node.key:
                if node.right is None:
                    node.right = Nodo(key)
                else:
                    _insert_rec(node.right, key)
            # Clave igual: se ignora (no se permiten duplicados)

        _insert_rec(self.root, key)

    # Complejidad: O(log n) en promedio, O(n) en el peor caso.
    def search(self, key):
        """Busca una clave y devuelve el camino si existe."""
        if self.root is None:
            return None, []

        path = []
        current = self.root
        while current is not None:
            path.append(current.key)
            if key == current.key:
                return current, path # Encontrado
            elif key < current.key:
                current = current.left
            else:
                current = current.right

        return None, path # No encontrado

    # Complejidad: O(log n) en promedio, O(n) en el peor caso.
    def delete(self, key):
        """Elimina una clave del BST."""
        self.root = self._delete_rec(self.root, key)

    def _delete_rec(self, root, key):
        if root is None:
            print(f"Error: La clave {key} no existe en el árbol.")
            return None
        
        # 1. Recorrer para encontrar el nodo a eliminar
        if key < root.key:
            root.left = self._delete_rec(root.left, key)
        elif key > root.key:
            root.right = self._delete_rec(root.right, key)
        else:
            # 2. Nodo encontrado, manejar los 3 casos de eliminación:
            
            # Caso 1: Cero o Un hijo (hoja o solo hijo derecho)
            if root.left is None:
                return root.right
            
            # Caso 1: Un hijo (solo hijo izquierdo)
            if root.right is None:
                return root.left
            
            # Caso 2: Dos hijos
            # Encontrar el sucesor inorden (el menor en el subárbol derecho)
            temp = self._min_value_node(root.right)
            
            # Copiar la clave del sucesor inorden a este nodo
            root.key = temp.key
            
            # Eliminar el sucesor inorden
            root.right = self._delete_rec(root.right, temp.key)

        return root

    def _min_value_node(self, node):
        """Encuentra el nodo con el valor mínimo en el subárbol."""
        current = node
        while current.left is not None:
            current = current.left
        return current

    # --- Recorridos ---

    # Complejidad de todos los recorridos: O(n) (visitan cada nodo una vez).
    
    def inorder(self):
        """Recorrido Inorden: Izquierda -> Raíz -> Derecha (Ordenado)."""
        result = []
        self._inorder_rec(self.root, result)
        return result

    def _inorder_rec(self, root, result):
        if root:
            self._inorder_rec(root.left, result)
            result.append(root.key)
            self._inorder_rec(root.right, result)

    def preorder(self):
        """Recorrido Preorden: Raíz -> Izquierda -> Derecha (Copia de la estructura)."""
        result = []
        self._preorder_rec(self.root, result)
        return result

    def _preorder_rec(self, root, result):
        if root:
            result.append(root.key)
            self._preorder_rec(root.left, result)
            self._preorder_rec(root.right, result)

    def postorder(self):
        """Recorrido Postorden: Izquierda -> Derecha -> Raíz (Eliminación/liberación)."""
        result = []
        self._postorder_rec(self.root, result)
        return result

    def _postorder_rec(self, root, result):
        if root:
            self._postorder_rec(root.left, result)
            self._postorder_rec(root.right, result)
            result.append(root.key)

    # --- Métricas ---

    # Complejidad: O(n) (visitan cada nodo una vez).
    def height(self):
        """Calcula la altura del árbol (longitud del camino más largo de la raíz a una hoja)."""
        return self._height_rec(self.root)

    def _height_rec(self, root):
        if root is None:
            return -1 # Convención: altura de un árbol con un solo nodo es 0
        left_h = self._height_rec(root.left)
        right_h = self._height_rec(root.right)
        return 1 + max(left_h, right_h)

    # Complejidad: O(n) (visitan cada nodo una vez).
    def size(self):
        """Calcula el número total de nodos en el árbol."""
        return self._size_rec(self.root)

    def _size_rec(self, root):
        if root is None:
            return 0
        return 1 + self._size_rec(root.left) + self._size_rec(root.right)

    # --- Persistencia ---

    # Complejidad: O(n) (similar a inorder).
    def export_inorder(self, filename):
        """Guarda el recorrido inorden en un archivo de texto."""
        try:
            data = [str(k) for k in self.inorder()]
            with open(filename, 'w') as f:
                f.write(' '.join(data))
            return True
        except Exception as e:
            print(f"Error al exportar a {filename}: {e}")
            return False
            
    # Complejidad: O(k log n) donde k es el número de claves (k inserciones).
    def load_keys(self, filename):
        """Carga claves desde un archivo y reconstruye el árbol (opcional)."""
        try:
            with open(filename, 'r') as f:
                line = f.read().strip()
                if not line:
                    return 0
                keys = [int(x) for x in line.split()]
                count = 0
                for key in keys:
                    self.insert(key)
                    count += 1
                return count
        except FileNotFoundError:
            print(f"Advertencia: Archivo de persistencia '{filename}' no encontrado.")
            return 0
        except ValueError:
            print(f"Error: El archivo '{filename}' contiene datos no válidos.")
            return 0
        except Exception as e:
            print(f"Error al cargar claves: {e}")
            return 0