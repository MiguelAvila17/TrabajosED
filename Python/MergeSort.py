# Merge dos subarrays de a[].
def merge(a, l, m, r): 
    # Tamaño del primer subarray
    a1 = m - l + 1  
    # Tamaño del segundo subarray
    a2 = r - m      

    # Crear arrays temporales
    L = [0] * a1   # Crear array temporal
    R = [0] * a2   # Crear array temporal

    # Copiar datos a los arrays temporales L[] y R[]
    for j in range(0, a1): # copiar datos al array temporal
        L[j] = a[l + j]

    for k in range(0, a2): # copiar datos al array temporal
        R[k] = a[m + 1 + k]

    i = 0   # Indice inicial del primer subarray
    j = 0   # Indice inicial del segundo subarray
    k = l   # Indice inicial del subarray mezclado

    # Mezclar los arrays temporales de nuevo en a[l..r]
    while i < a1 and j < a2: # recorrer ambos arrays
        if L[i] <= R[j]: # comparar los elementos de ambos arrays
            a[k] = L[i]  # copiar el elemento más pequeño al array original
            i = i + 1    # incrementar el índice del primer array
        else: # si el elemento del segundo array es más pequeño
            a[k] = R[j]  # copiar el elemento más pequeño al array original
            j = j + 1    # incrementar el índice del segundo array
        k = k + 1        # incrementar el índice del array original

    # copiar los elementos restantes de L[], si hay alguno
    while i < a1: # copiar los elementos restantes del primer array
        a[k] = L[i] # copiar el elemento al array original
        i = i + 1   # incrementar el índice del primer array
        k = k + 1   # incrementar el índice del array original

    # copiar los elementos restantes de R[], si hay alguno
    while j < a2: # copiar los elementos restantes del segundo array
        a[k] = R[j] # copiar el elemento al array original
        j = j + 1   # incrementar el índice del segundo array
        k = k + 1   # incrementar el índice del array original

# l es para el índice izquierdo, y r es para el índice derecho del
# sub-array de *a* a ser ordenado
def mergeSort(a, l, r): # función principal que ordena a[l..r]
    if l < r:
        # Igual que (l + r)//2, pero evita el desbordamiento para
        # grandes valores de l y r
        m = l + (r - l) // 2
        # Ordenar la primera y segunda mitad
        mergeSort(a, l, m)     # ordenar la primera mitad
        mergeSort(a, m + 1, r) # ordenar la segunda mitad
        merge(a, l, m, r)      # mezclar las dos mitades

# Divide el array en dos mitades, las ordena y luego las mezcla
# Código para probar la implementación de MergeSort
a = [39, 28, 44, 11] # arreglo desordenado
s = len(a) # tamaño del arreglo

print("Antes de ordenar el arreglo: ") # imprime el arreglo
for j in range(s):
    print("%d" % a[j], end=" ")

mergeSort(a, 0, s - 1) # llama a la función mergeSort

print("\nDespués de ordenar el arreglo: ")
for j in range(s):
    print("%d" % a[j], end=" ")