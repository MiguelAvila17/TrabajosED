class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.anterior = None
        self.siguiente = None

class ListaDoble:
    def __init__(self):
        self.cabeza = None

    def agregar(self, dato):
        nuevo = Nodo(dato)
        if not self.cabeza:
            self.cabeza = nuevo
        else:
            actual = self.cabeza
            while actual.siguiente:
                actual = actual.siguiente
            actual.siguiente = nuevo
            nuevo.anterior = actual

    def mostrar(self):
        if not self.cabeza:
            print("Lista vacía.")
            return
        actual = self.cabeza
        print("\nLista doblemente enlazada:")
        while actual:
            print(actual.dato, end=" <-> ")
            actual = actual.siguiente
        print("None\n")

lista = ListaDoble()

while True:
    print("=== LISTA DOBLEMENTE ENLAZADA (Python) ===")
    print("1. Agregar nodo")
    print("2. Mostrar lista")
    print("3. Salir")
    opcion = input("Opción: ")

    if opcion == "1":
        dato = int(input("Dato: "))
        lista.agregar(dato)
    elif opcion == "2":
        lista.mostrar()
    elif opcion == "3":
        break