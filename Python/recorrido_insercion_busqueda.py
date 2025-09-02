# 1. Recorrer e imprimir valores
arr = [10, 20, 30, 40, 50]
print("Recorrido del arreglo:")
for i in arr:
    print(i)

# 2. Insertar en índice determinado
arr.insert(2, 99)   # Inserta 99 en la posición 2
print("Después de insertar:", arr)

# 3. Búsqueda lineal
x = 30
encontrado = False
for i in range(len(arr)):
    if arr[i] == x:
        print(f"Elemento {x} encontrado en índice {i}")
        encontrado = True
        break
if not encontrado:
    print(f"Elemento {x} no encontrado")
