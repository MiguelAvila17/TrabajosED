MAXSIZE = 5
queue = [None] * MAXSIZE
front = -1
rear = -1

def esta_vacia():
    return front == -1

def esta_llena():
    return (rear + 1) % MAXSIZE == front

def insertar():
    global rear, front
    elemento = int(input("Ingrese el elemento: "))
    if esta_llena():
        print("Desbordamiento (OVERFLOW)")
        return
    if esta_vacia():
        front = rear = 0
    else:
        rear = (rear + 1) % MAXSIZE
    queue[rear] = elemento
    print("Elemento insertado correctamente.")

def eliminar():
    global front, rear
    if esta_vacia():
        print("Subdesbordamiento (UNDERFLOW)")
        return
    print(f"Elemento eliminado: {queue[front]}")
    if front == rear:
        front = rear = -1
    else:
        front = (front + 1) % MAXSIZE

def mostrar():
    if esta_vacia():
        print("La cola está vacía.")
        return
    i = front
    print("Elementos en la cola circular:")
    while True:
        print(queue[i], end=" ")
        if i == rear:
            break
        i = (i + 1) % MAXSIZE
    print()

while True:
    print("\n1. Insertar\n2. Eliminar\n3. Mostrar\n4. Salir")
    op = input("Opción: ")
    if op == "1": insertar()
    elif op == "2": eliminar()
    elif op == "3": mostrar()
    elif op == "4": break