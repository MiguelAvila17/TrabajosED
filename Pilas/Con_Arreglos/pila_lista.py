MAX_SIZE = 100
stack = [0] * MAX_SIZE
top = -1

def push(item):
    global top
    if top == MAX_SIZE - 1:
        print("Stack Overflow")
        return
    top += 1
    stack[top] = item

def pop():
    global top
    if top == -1:
        print("Stack Underflow")
        return -1
    value = stack[top]
    top -= 1
    return value

def peek():
    if top == -1:
        print("Pila vacía")
        return -1
    return stack[top]

def is_empty():
    return top == -1

def is_full():
    return top == MAX_SIZE - 1

push(10)
push(20)
push(30)
print("Elemento Superior:", peek())
print("Extrae elemento:", pop())
print("Elemento Superior:", peek())