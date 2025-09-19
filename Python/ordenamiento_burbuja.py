import random

def burbuja(arr):
    n = len(arr)
    for i in range(n - 1):
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

# Generar arreglo de 10 números aleatorios entre 1 y 100
arr = [random.randint(1, 100) for _ in range(10)]
print("Original:", arr)
burbuja(arr)
print("Ordenado:", arr)