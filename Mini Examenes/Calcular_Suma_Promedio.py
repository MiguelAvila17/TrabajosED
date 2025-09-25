# Lista vacía para guardar los números
numeros = []

# Pedir 10 números
for i in range(10):
    num = int(input(f"Ingrese el número {i+1}: "))
    numeros.append(num)

# Calcular operaciones
suma = sum(numeros)
promedio = suma / len(numeros)
maximo = max(numeros)
minimo = min(numeros)

# Mostrar resultados
print("\nNúmeros ingresados:", numeros)
print("Suma:", suma)
print("Promedio:", promedio)
print("Máximo:", maximo)
print("Mínimo:", minimo)