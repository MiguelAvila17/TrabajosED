def Radix_Sort(arr):
    max_val = max(arr)
    exp = 1
    n = len(arr)
    
    while max_val // exp > 0:
        output = [0] * n
        count = [0] * 10

        for i in range(n):
            index = (arr[i] // exp) % 10
            count[index] += 1

        for i in range(1, 10):
            count[i] += count[i - 1]

        i = n - 1
        while i >= 0:
            index = (arr[i] // exp) % 10
            output[count[index] - 1] = arr[i]
            count[index] -= 1
            i -= 1

        for i in range(n):
            arr[i] = output[i]

        exp *= 10

# Ejemplo
arr = [170, 45, 75, 90, 802, 24, 2, 66]
radix_sort(arr)
print("Arreglo ordenado:", arr)