def hash_sort(arr):
    hash_table = {}
    max_val = 0

    for num in arr:
        hash_table[num] = hash_table.get(num, 0) + 1
        if num > max_val:
            max_val = num

    sorted_arr = []
    for i in range(max_val + 1):
        if i in hash_table:
            sorted_arr.extend([i] * hash_table[i])
    return sorted_arr

arr = [4, 2, 2, 8, 3, 3, 1]
print("Arreglo original:", arr)

arr_sorted = hash_sort(arr)
print("Arreglo ordenado:", arr_sorted)