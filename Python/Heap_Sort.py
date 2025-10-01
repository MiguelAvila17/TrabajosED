# Heapsort es un algoritmo de ordenamiento basado en un árbol binario llamado "heap".
# La idea es construir un heap máximo (max-heap) y luego extraer el mayor elemento 
# (la raíz) para colocarlo al final del arreglo, repitiendo el proceso hasta ordenar todo.

def heapify(arr, n, i):
    # Función para asegurar que el subárbol con raíz en el índice i
    # cumpla con la propiedad de heap máximo.
    # arr: lista a ordenar
    # n: tamaño del heap
    # i: índice de la raíz del subárbol
    
    largest = i        # Inicialmente, asumimos que la raíz es el mayor
    left = 2 * i + 1   # Índice del hijo izquierdo
    right = 2 * i + 2  # Índice del hijo derecho

    # Si el hijo izquierdo existe y es mayor que la raíz
    if left < n and arr[left] > arr[largest]:
        largest = left

    # Si el hijo derecho existe y es mayor que el mayor actual
    if right < n and arr[right] > arr[largest]:
        largest = right

    # Si el mayor no es la raíz, intercambiamos y seguimos ajustando recursivamente
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # Intercambio
        heapify(arr, n, largest)  # Ajustar el subárbol afectado


def heapsort(arr):
    # Función principal de Heapsort.
    # Ordena la lista arr en orden ascendente.
    
    n = len(arr)

    # Paso 1: Construir un heap máximo
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Paso 2: Extraer elementos uno por uno del heap
    for i in range(n - 1, 0, -1):
        # Mover la raíz (máximo) al final
        arr[0], arr[i] = arr[i], arr[0]
        
        # Llamar heapify en el heap reducido
        heapify(arr, i, 0)


# Ejemplo de uso
if __name__ == "__main__":
    lista = [12, 11, 13, 5, 6, 7]
    print("Antes de ordenar los elementos del array son: ", lista)
    heapsort(lista)
    print("\nDespués de ordenar el arreglo: ", lista)