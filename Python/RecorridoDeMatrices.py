# Recorrido por renglones
matriz = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

print("Recorrido por renglones:")
for fila in matriz:
    for valor in fila:
        print(valor, end=" ")
    print()

# Recorrido por columnas
print("\nRecorrido por columnas:")
for col in range(len(matriz[0])):
    for fila in range(len(matriz)):
        print(matriz[fila][col], end=" ")
    print()