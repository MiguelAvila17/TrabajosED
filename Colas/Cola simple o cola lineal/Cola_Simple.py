MAXSIZE = 5
queue = [None] * MAXSIZE
front = -1
rear = -1

def insertar():
    global front, rear
    if rear == MAXSIZE - 1:
        print("Desbordamiento (OVERFLOW)")
        return
    elemento = int(input("Ingrese el elemento: "))
    if front == -1 and rear == -1:
        front = rear = 0
    else:
        rear += 1
    queue[rear] = elemento
    print("Elemento insertado correctamente.")

def eliminar():
    global front, rear
    if front == -1 or front > rear:
        print("Subdesbordamiento (UNDERFLOW)")
        return
    print("Elemento eliminado:", queue[front])
    if front == rear:
        front = rear = -1
    else:
        front += 1

def mostrar():
    if front == -1 or front > rear:
        print("La cola está vacía.")
    else:
        print("Elementos en la cola:")
        for i in range(front, rear + 1):
            print(queue[i])

while True:
    print("\n1.Insertar 2.Eliminar 3.Mostrar 4.Salir")
    op = input("Opción: ")
    if op == "1": insertar()
    elif op == "2": eliminar()
    elif op == "3": mostrar()
    elif op == "4": break