# Análisis de Transmisiones y Códigos Maliciosos

- Jorge Iván Sánchez González A01761414
- Alejandro Moncada Espinosa A01638343
- Ana Camila Jiménez Mendoza A01274422
- Santiago Gutiérrez González A00572499

## Descripción del Problema

Este programa analiza archivos de transmisión y código malicioso, y realiza las siguientes operaciones:

1. **Parte 1:** Verifica si los archivos de transmisión (`transmission1.txt`, `transmission2.txt`) contienen los códigos maliciosos especificados en los archivos (`mcode1.txt`, `mcode2.txt`, `mcode3.txt`).
2. **Parte 2:** Encuentra el palíndromo más largo (código espejeado) en cada archivo de transmisión.
3. **Parte 3:** Determina la subcadena común más larga entre los archivos de transmisión.

### Archivos de entrada
El programa lee los siguientes archivos de texto, que deben estar en la misma ruta de ejecución:
- `transmission1.txt`
- `transmission2.txt`
- `mcode1.txt`
- `mcode2.txt`
- `mcode3.txt`

### Salida esperada
1. Se muestra si los archivos de transmisión contienen o no los códigos maliciosos, indicando la posición inicial si es encontrado.
2. La posición del palíndromo más largo en cada archivo de transmisión.
3. La posición inicial y final del substring común más largo entre los dos archivos de transmisión.

## Instrucciones de Compilación

Para compilar y ejecutar el programa, sigue estos pasos:

1. Abre una terminal en la carpeta donde está el archivo `main.cpp`.
2. Compila el programa con el siguiente comando:

   ```bash
   g++ -o transmisiones main.cpp
3. Ejecuta el programa con el siguiente comando:
   ```bash
   ./transmisiones
   
Asegúrate de que los archivos de entrada (transmission1.txt, transmission2.txt, mcode1.txt, mcode2.txt, mcode3.txt) estén en la misma carpeta donde se ejecuta el programa.