from collections import deque

MAXSIZE = 5
dq = deque()

def insertar_frente():
    if len(dq) == MAXSIZE:
        print("OVERFLOW")
        return
    e = int(input("Ingrese elemento: "))
    dq.appendleft(e)
    print("Insertado al frente.")

def insertar_final():
    if len(dq) == MAXSIZE:
        print("OVERFLOW")
        return
    e = int(input("Ingrese elemento: "))
    dq.append(e)
    print("Insertado al final.")

def eliminar_frente():
    if not dq:
        print("UNDERFLOW")
        return
    print("Eliminado del frente:", dq.popleft())

def eliminar_final():
    if not dq:
        print("UNDERFLOW")
        return
    print("Eliminado del final:", dq.pop())

def mostrar():
    print("Deque:", list(dq))

while True:
    print("\n1.Insertar frente 2.Insertar final 3.Eliminar frente 4.Eliminar final 5.Mostrar 6.Salir")
    op = input("Opción: ")
    if op == "1": insertar_frente()
    elif op == "2": insertar_final()
    elif op == "3": eliminar_frente()
    elif op == "4": eliminar_final()
    elif op == "5": mostrar()
    elif op == "6": break