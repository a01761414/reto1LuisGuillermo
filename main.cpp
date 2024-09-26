#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string readFile(string filePath) {
    // Complejidad: O(n) donde n es el tamaño del archivo.
    // Descripción: Lee el contenido de un archivo y devuelve el texto como una cadena de caracteres.

    ifstream file(filePath); // Abre el archivo especificado en el path 'filePath'.
    if (!file.is_open()) { // Verifica si el archivo se abrió correctamente.
        cerr << "Failed to open the file: " << filePath << endl;
        return ""; // Si no se pudo abrir el archivo, retorna un string vacío.
    }
    string text;
    stringstream buffer;

    buffer << file.rdbuf(); // Lee todo el contenido del archivo y lo almacena en el buffer.
    text = buffer.str(); // Convierte el contenido del buffer en una cadena de caracteres.
    file.close();  // Cierra el archivo.
    return text;
}

vector<int> funcLPS(string &p) {
    // Complejidad: O(m) donde m es la longitud del patrón 'p'.
    // Descripción: Calcula el array de prefijos más largos que también son sufijos (LPS) para el patrón 'p', 
    // lo que ayuda a optimizar el algoritmo KMP para buscar subcadenas.

    int m = p.length(); // Obtiene la longitud del patrón
    vector<int> lps(m, 0); // Inicializa el array LPS de tamaño 'm' con todos los valores en 0.
    int i = 1, j = 0; // 'i' es el índice que recorre el patrón, 'j' es la longitud del prefijo más largo actual

    while (i < m) {
        if (p[i] == p[j]) {
            lps[i] = j + 1; // Si hay coincidencia, el valor LPS en 'i' es el tamaño del prefijo (j + 1).
            i++;
            j++;
        } else if (j > 0) {
            j = lps[j - 1]; // Retrocede 'j' al valor del LPS anterior para intentar emparejar desde allí.
        } else {
            lps[i] = 0;  // Si no hay coincidencia y no hay prefijo, el valor en LPS es 0.
            i++;
        }
    }
    return lps;
}

int kmpPos(string &t, string &p) {
    // Complejidad: O(n + m) donde n es la longitud del texto 't' y m es la longitud del patrón 'p'.
    // Descripción: Utiliza el algoritmo KMP para encontrar la posición de inicio del patrón 'p' en el texto 't'. 
    // Si el patrón no se encuentra, devuelve -1.
    int m = p.length(), n = t.length();
    vector<int> lps = funcLPS(p);
    int i = 0, j = 0;

    while (i < n) {
        if (p[j] == t[i]) {  // Si los caracteres actuales coinciden, se incrementan ambos índices.
            if (j == m - 1) { // Si se ha encontrado una coincidencia completa del patrón (cuando 'j' llega al final del patrón)
                return i - m + 2; // Posición Inicial de coincidencia
            }
            i++;
            j++;
        } else if (j > 0) { // Si los caracteres no coinciden y 'j' es mayor que 0 (es decir, hubo una coincidencia parcial)
            j = lps[j - 1];
        } else {  // Si no hay coincidencia y 'j' es 0, se incrementa solo 'i' para avanzar en el texto.
            i++;
        }
    }
    return -1;
}

pair<int, int> longestPalindromeManacher(const string &s) {
    // Complejidad: O(n) donde n es la longitud de la cadena 's'.
    // Descripción: Implementa el algoritmo de Manacher para encontrar el palíndromo más largo en la cadena 's' en tiempo lineal.

    string t = "^#"; // 't' será la cadena modificada para Manacher. Se insertan caracteres especiales '^' al inicio y '$' al final,
                     // además de '#' entre cada letra de 's' para manejar palíndromos de longitud par e impar de manera uniforme.
    for (size_t i = 0; i < s.length(); ++i) {
        t += s[i];
        t += '#';
        // Agrega cada carácter de la cadena original 's' separado por '#'.
    }
    t += '$'; // Añade '$' al final para evitar desbordamientos durante las comparaciones.


    int n = t.length(); // 'n' es la longitud de la cadena modificada 't'.
    vector<int> p(n, 0);  // 'p' es el array que almacena la longitud del palíndromo más largo centrado en cada posición de 't'.
    int center = 0, right = 0; // 'center' es el centro del palíndromo más a la derecha encontrado hasta ahora, y'right' es el borde derecho del palíndromo más a la derecha.

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * center - i; // 'mirror' es el índice espejo de 'i' respecto al centro actual
        if (right > i) { // Si 'i' está dentro de los límites del palíndromo más a la derecha
            p[i] = min(right - i, p[mirror]);
        }
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) { // Intenta expandir el palíndromo alrededor de 'i'.
            ++p[i]; // Expande el palíndromo mientras los caracteres a ambos lados coincidan.
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
            // Actualiza el centro y el borde derecho si el palíndromo centrado en 'i' se expande más allá del 'right' actual.
        }
    }

    int maxLength = 0, start = 0; // 'maxLength' almacenará la longitud del palíndromo más largo encontrado, y 'start' almacenará la posición de inicio del palíndromo más largo en la cadena original 's'.

    for (int i = 1; i < n - 1; ++i) {
        if (p[i] > maxLength) {
            maxLength = p[i];
            start = (i - p[i]) / 2; 
            // Actualiza 'maxLength' y 'start' si se encuentra un palíndromo más largo.
        }
    }

    return make_pair(start + 1, start + maxLength); // Devuelve un par de enteros: el inicio y el final (no inclusivo) del palíndromo más largo
}

pair<pair<int, int>, pair<int, int> > longestCommonSubstring(const string &s1, const string &s2) {
    // Complejidad: O(n * m), donde 'n' es la longitud de 's1' y 'm' es la longitud de 's2'.
    // Descripción: Esta función utiliza programación dinámica para encontrar la subcadena común más larga entre dos cadenas.
    // La tabla 'dp' almacena la longitud de la subcadena común más larga que termina en las posiciones 'i-1' de 's1' y 'j-1' de 's2'.
    // Además de la longitud, se guarda la posición final de dicha subcadena en ambas cadenas.

    int n = s1.length();
    int m = s2.length();
    vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0)); // DP table
    int length = 0; // Longitud de la subcadena más larga
    int endPos1 = 0; // Fin de la subcadena en s1
    int endPos2 = 0; // Fin de la subcadena en s2

    // Rellenar la tabla dp
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Extender subcadena común
                if (dp[i][j] > length) { // Actualizar si encontramos una subcadena más larga
                    length = dp[i][j];
                    endPos1 = i - 1; // Fin en s1
                    endPos2 = j - 1; // Fin en s2
                }
            }
        }
    }

    int startPos1 = endPos1 - length + 1; // Inicio en s1
    int startPos2 = endPos2 - length + 1; // Inicio en s2

    return make_pair(make_pair(startPos1 + 1, endPos1 + 1), make_pair(startPos2 + 1, endPos2 + 1)); // Convertir a base 1
}



void isMcode(int pos) {
    if (pos != -1) {
        cout << "   " << "true" << " " << pos << endl;
    } else {
        cout << "   " << "false" << endl;
    }
}

int main() {
    string t1 = readFile("transmission1.txt");
    t1.erase(remove(t1.begin(), t1.end(), '\n'), t1.end());

    string t2 = readFile("transmission2.txt");
    t2.erase(remove(t2.begin(), t2.end(), '\n'), t2.end());

    string m1 = readFile("mcode1.txt");
    string m2 = readFile("mcode2.txt");
    string m3 = readFile("mcode3.txt");

    cout << "parte 1" << endl;
    isMcode(kmpPos(t1, m1));
    isMcode(kmpPos(t1, m2));
    isMcode(kmpPos(t1, m3));
    isMcode(kmpPos(t2, m1));
    isMcode(kmpPos(t2, m2));
    isMcode(kmpPos(t2, m3));

    cout << "parte 2" << endl;
    pair<int, int> lps = longestPalindromeManacher(t1);
    cout << "   " << lps.first << " "<< lps.second << endl;

    pair<int, int> lps2 = longestPalindromeManacher(t2);
    cout << "   " << lps2.first << " "<< lps2.second << endl;

    cout << "parte 3" << endl;
    pair<pair<int, int>, pair<int, int> > lcs = longestCommonSubstring(t1, t2);

    //En transmision 1
    cout << "   " << lcs.first.first << " " << lcs.first.second << endl;
    //En transmision 2
    cout << "   " << lcs.second.first << " " << lcs.second.second << endl;

    return 0;
}