import random

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key

# Generar lista de números aleatorios
arr = [random.randint(1, 100) for _ in range(10)]
print("Antes de ordenar:", arr)
insertion_sort(arr)
print("Después de ordenar:", arr)