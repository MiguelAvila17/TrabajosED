import random
import time
from collections import defaultdict

# --- Algoritmos de Ordenamiento ---

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr

def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]
        merge_sort(left_half)
        merge_sort(right_half)
        i = j = k = 0
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1
        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1
        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1
    return arr

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)
    return arr

def counting_sort(arr, exp=1):
    n = len(arr)
    output = [0] * n
    count = [0] * 10 
    for i in range(n):
        index = arr[i] // exp
        count[index % 10] += 1
    for i in range(1, 10):
        count[i] += count[i - 1]
    i = n - 1
    while i >= 0:
        index = arr[i] // exp
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        i -= 1
    for i in range(n):
        arr[i] = output[i]
    return arr

def radix_sort(arr):
    if not arr:
        return []
    max_val = max(arr)
    exp = 1
    while max_val // exp > 0:
        counting_sort(arr, exp)
        exp *= 10
    return arr

def bucket_sort(arr):
    if not arr:
        return []
    max_val = max(arr)
    min_val = min(arr)
    if max_val == min_val:
        return arr
    bucket_size = 10 
    num_buckets = (max_val - min_val) // bucket_size + 1
    buckets = [[] for _ in range(num_buckets)]
    for num in arr:
        idx = (num - min_val) // bucket_size
        buckets[idx].append(num)
    sorted_arr = []
    for bucket in buckets:
        insertion_sort(bucket) 
        sorted_arr.extend(bucket)
    return sorted_arr

def hash_sort(arr):
    if not arr:
        return []
    freq_map = defaultdict(int)
    for x in arr:
        freq_map[x] += 1
    sorted_arr = []
    for key in sorted(freq_map.keys()):
        sorted_arr.extend([key] * freq_map[key])
    return sorted_arr

# --- Funciones de Generación de Arreglos (Sin cambios) ---

def generate_ordered_array(size):
    return list(range(size))

def generate_reverse_ordered_array(size):
    return list(range(size - 1, -1, -1))

def generate_random_array(size):
    return [random.randint(0, size * 10) for _ in range(size)]

def generate_partially_ordered_array(size, num_swaps=None):
    arr = list(range(size))
    if num_swaps is None:
        num_swaps = size // 10
    for _ in range(num_swaps):
        idx1, idx2 = random.sample(range(size), 2)
        arr[idx1], arr[idx2] = arr[idx2], arr[idx1]
    return arr

# --- NUEVO: Funciones del Menú Interactivo ---

# Listas de opciones para los menús
sorting_algorithms_menu = [
    ("Burbuja", bubble_sort),
    ("Selección", selection_sort),
    ("Inserción", insertion_sort),
    ("Merge", merge_sort),
    ("Quick", quick_sort),
    ("Heap", heap_sort),
    ("Counting", radix_sort),
    ("Bucket", bucket_sort),
    ("Hash", hash_sort),
]

array_types_menu = [
    ("Aleatorio", generate_random_array),
    ("Ordenado", generate_ordered_array),
    ("Inverso", generate_reverse_ordered_array),
    ("Medianamente Ordenado", generate_partially_ordered_array),
]

def get_menu_choice(menu_options, title):
    """Muestra un menú y devuelve la opción seleccionada por el usuario."""
    print(f"\n--- {title} ---")
    for i, (name, _) in enumerate(menu_options, 1):
        print(f"  {i}. {name}")
    print("  0. Salir")
    
    while True:
        try:
            choice = int(input(f"Elige una opción (0-{len(menu_options)}): "))
            if 0 <= choice <= len(menu_options):
                return choice
            else:
                print("Opción no válida, intenta de nuevo.")
        except ValueError:
            print("Entrada no válida, por favor ingresa un número.")

def get_array_size():
    """Pregunta al usuario por el tamaño del arreglo."""
    print("\n--- Tamaño del Arreglo ---")
    print("  (Escribe 0 para salir)")
    while True:
        try:
            size = int(input("Ingresa el tamaño del arreglo (ej: 100, 1000, 10000): "))
            if size >= 0:
                return size
            else:
                print("El tamaño no puede ser negativo.")
        except ValueError:
            print("Entrada no válida, por favor ingresa un número.")

# --- NUEVO: Lógica Principal (Main Loop) ---

def main():
    print("Bienvenido al Probador Interactivo de Algoritmos de Ordenamiento")
    
    while True:
        # 1. Elegir Algoritmo
        algo_choice = get_menu_choice(sorting_algorithms_menu, "Elige un Algoritmo")
        if algo_choice == 0:
            break
        algo_name, sort_func = sorting_algorithms_menu[algo_choice - 1]

        # 2. Elegir Tipo de Arreglo
        type_choice = get_menu_choice(array_types_menu, "Elige el Tipo de Arreglo")
        if type_choice == 0:
            break
        array_type_name, array_gen_func = array_types_menu[type_choice - 1]

        # 3. Elegir Tamaño
        size = get_array_size()
        if size == 0:
            break
            
        # 4. Generar y Ejecutar
        print("\n--- Ejecutando Prueba ---")
        print(f"Algoritmo: {algo_name}")
        print(f"Tipo:      {array_type_name}")
        print(f"Tamaño:    {size}")

        print("\nGenerando arreglo...")
        original_arr = array_gen_func(size)
        arr_copy = list(original_arr) # Copia para no modificar el original

        print(f"Ejecutando {algo_name}...")
        try:
            start_time = time.perf_counter()
            sort_func(arr_copy) # Ejecuta el ordenamiento
            end_time = time.perf_counter()
            
            duration = (end_time - start_time) * 1000 # en milisegundos
            
            print("¡Prueba completada!")
            print(f"** Tiempo de ejecución: {duration:.4f} ms **")

            # Verificación opcional
            # if arr_copy == sorted(original_arr):
            #     print("Verificación: El arreglo fue ordenado correctamente.")
            # else:
            #     print("ERROR: El arreglo NO fue ordenado correctamente.")
                
        except RecursionError:
            print(f"ERROR: {algo_name} excedió el límite de recursión.")
            print("   (Esto es común en QuickSort con arreglos ordenados/inversos de gran tamaño)")
        
        print("-" * 30 + "\n")

    print("Saliendo del programa. ¡Adiós!")

# Ejecutar el programa principal
if __name__ == "__main__":
    main()