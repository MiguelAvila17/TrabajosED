def counting_sort(arr):
    if not arr:
        return arr
    
    max_val = max(arr)
    count = [0] * (max_val + 1)
    
    # Contar las ocurrencias
    for num in arr:
        count[num] += 1
    
    # Reconstruir el arreglo ordenado
    sorted_arr = []
    for i, c in enumerate(count):
        sorted_arr.extend([i] * c)
    
    return sorted_arr

# Ejemplo
arr = [4, 2, 2, 8, 3, 3, 1]
print(counting_sort(arr))