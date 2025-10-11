def insertion_sort(bukt):
    # Función de ordenamiento por inserción
    for j in range(1, len(bukt)):  # Iterar desde el segundo elemento
        val = bukt[j]              # Elemento actual a insertar
        k = j - 1                  # Índice del elemento anterior
        # Mover elementos mayores hacia la derecha
        while k >= 0 and bukt[k] > val:
            bukt[k + 1] = bukt[k]  # Desplazar elemento
            k -= 1
        bukt[k + 1] = val          # Insertar el elemento en su posición correcta
def bucket_sort(inputArr):
    # Función principal de ordenamiento bucket sort
    s = len(inputArr)                       # Número de buckets
    bucketArr = [[] for _ in range(s)]      # Crear lista de buckets vacíos
    # Colocar cada elemento en su bucket correspondiente
    for j in inputArr:
        bi = int(s * j)                     # Índice del bucket
        if bi != s:                         # Evitar índice fuera de rango
            bucketArr[bi].append(j)
        else:
            bucketArr[s - 1].append(j)
    # Ordenar cada bucket individualmente usando ordenamiento por inserción
    for bukt in bucketArr:
        insertion_sort(bukt)
    # Concatenar todos los buckets ordenados en el arreglo original
    idx = 0
    for bukt in bucketArr:
        for j in bukt:
            inputArr[idx] = j
            idx += 1
# Ejemplo de uso
inputArr = [0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67]
print("Arreglo antes de ordenar:")
print(" ".join(map(str, inputArr)))
bucket_sort(inputArr)
print("\nArreglo después de ordenar:")
print(" ".join(map(str, inputArr)))