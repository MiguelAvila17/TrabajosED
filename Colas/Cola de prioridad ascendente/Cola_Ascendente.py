MAXSIZE = 5
queue = []
def insertar():
    if len(queue) == MAXSIZE:
        print("Desbordamiento (OVERFLOW)")
        return
    elemento = int(input("Ingrese el elemento: "))
    queue.append(elemento)
    queue.sort()
    print("Elemento insertado correctamente.")

def eliminar():
    if not queue:
        print("Subdesbordamiento (UNDERFLOW)")
        return
    print(f"Elemento eliminado: {queue.pop(0)}")

def mostrar():
    if not queue:
        print("La cola está vacía.")
    else:
        print("Cola (prioridad ascendente):", queue)

while True:
    print("\n1.Insertar 2.Eliminar 3.Mostrar 4.Salir")
    op = input("Opción: ")
    if op == "1": insertar()
    elif op == "2": eliminar()
    elif op == "3": mostrar()
    elif op == "4": break