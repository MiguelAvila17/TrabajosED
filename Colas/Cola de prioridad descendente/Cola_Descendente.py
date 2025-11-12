MAXSIZE = 5
queue = []

def insertar():
    if len(queue) == MAXSIZE:
        print("OVERFLOW")
        return
    e = int(input("Ingrese el elemento: "))
    queue.append(e)
    queue.sort(reverse=True)
    print("Elemento insertado.")

def eliminar():
    if not queue:
        print("UNDERFLOW")
        return
    print("Elemento eliminado:", queue.pop(0))

def mostrar():
    if not queue:
        print("Vacía")
    else:
        print("Cola descendente:", queue)

while True:
    print("\n1.Insertar 2.Eliminar 3.Mostrar 4.Salir")
    op = input("Opción: ")
    if op == "1": insertar()
    elif op == "2": eliminar()
    elif op == "3": mostrar()
    elif op == "4": break