import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Datos
data = {
    "Algoritmo": [
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort",
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort",
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort",
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort",
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort",
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort",
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort",
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort",
        "Bubble Sort","Insertion Sort","Selection Sort","Quick Sort","Merge Sort","Heap Sort","Hash Sort","Bucket Sort","Radix Sort"
    ],
    "Tamano": [
        100]*27 + [1000]*27 + [10000]*27,
    "Tipo": [
        "Aleatorio"]*9 + ["Ordenado"]*9 + ["Inverso"]*9 +
        ["Aleatorio"]*9 + ["Ordenado"]*9 + ["Inverso"]*9 +
        ["Aleatorio"]*9 + ["Ordenado"]*9 + ["Inverso"]*9,
    "Tiempo_ms": [
        0.0468,0.0205,0.0258,0.0074,0.041,0.0137,0.0042,0.0036,0.0112,
        0.0233,0.0012,0.023,0.0252,0.028,0.0138,0.0037,0.0033,0.0075,
        0.0459,0.0184,0.0264,0.0135,0.0303,0.0134,0.0034,0.0034,0.0109,
        4.5186,1.8398,2.2405,0.1042,0.3462,0.2069,0.0425,0.0973,0.1405,
        2.2783,0.0104,2.1143,2.7836,0.2815,0.1982,0.0288,0.0327,0.1041,
        4.5214,1.7172,2.155,0.1127,0.3258,0.205,0.0239,0.0228,0.1008,
        453.2,179.401,194.618,1.3481,3.6261,2.727,0.2322,0.2318,1.059,
        222.466,0.1261,210.3,258.257,3.0069,2.5516,0.274,0.2608,1.3375,
        449.617,175.603,201.55,1.4284,3.7529,2.8433,0.2336,0.2308,1.0588
    ]
}

# Crear DataFrame
df = pd.DataFrame(data)

# Configuración estética
sns.set(style="whitegrid")

# Graficar por tamaño y tipo
for tamano in df['Tamano'].unique():
    plt.figure(figsize=(12,6))
    df_subset = df[df['Tamano']==tamano]
    sns.barplot(x="Algoritmo", y="Tiempo_ms", hue="Tipo", data=df_subset)
    plt.title(f'Tiempos de algoritmos de ordenamiento (n={tamano})')
    plt.ylabel('Tiempo (ms)')
    plt.xlabel('Algoritmo')
    plt.xticks(rotation=45)
    plt.legend(title='Tipo de arreglo')
    plt.tight_layout()
    plt.show()