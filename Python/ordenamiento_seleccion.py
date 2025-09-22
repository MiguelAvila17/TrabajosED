import random

def selection(a):
    for i in range(len(a)):
        small = i
        for j in range(i + 1, len(a)):
            if a[small] > a[j]:
                small = j
        a[i], a[small] = a[small], a[i]

def printArr(a):
    for i in range(len(a)):
        print(a[i], end=" ")
    print()

# Generar arreglo aleatorio
a = [random.randint(1, 100) for _ in range(5)]

print("Arreglo antes de ser ordenado:")
printArr(a)

selection(a)

print("\nArreglo después de ser ordenado:")
printArr(a)