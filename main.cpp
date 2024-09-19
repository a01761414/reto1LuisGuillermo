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

bool kmpBool(string &t, string &p) {
    // Complejidad: O(n + m) donde n es la longitud del texto 't' y m es la longitud del patrón 'p'.
    // Descripción: Implementa el algoritmo KMP para verificar si el patrón 'p' se encuentra dentro del texto 't'.

    int m = p.length(), n = t.length(); // Longitud del patrón y del texto
    vector<int> lps = funcLPS(p); // Calcula el array LPS (Longest Prefix Suffix) para el patrón 'p'
    int i = 0, j = 0; 

    // Bucle principal que recorre el texto 't' para buscar el patrón 'p'.
    while (i < n) {
        if (t[i] == p[j]) { // Caso 1: Los caracteres de 't' e 'p' coinciden.
            i++;
            j++;
        }

        if (j == m) { // Caso 2: Si 'j' ha alcanzado el final del patrón, significa que se ha encontrado el patrón en el texto.
            return true;
        } else if (i < n && p[j] != t[i]) {  // Caso 3: Si los caracteres no coinciden y aún no hemos recorrido todo el texto.
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false; // Si se recorre todo el texto sin encontrar el patrón, retorna falso.
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
                return i - m + 1; // Posición Inicial de coincidencia
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

pair<int, int> longestCommonSubstring(const string &s1, const string &s2) {
    // Complejidad: O(n * m) donde n y m son las longitudes de las cadenas 's1' y 's2', respectivamente.
    // Descripción: Encuentra la subcadena común más larga entre dos cadenas utilizando programación dinámica.

    int n = s1.length();
    int m = s2.length();
    vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0)); // 'dp[i][j]' almacena la longitud de la subcadena común más larga que termina en las posiciones 'i-1' de 's1' y 'j-1' de 's2'
    int length = 0, endPos = 0;
    // 'length' guarda la longitud de la subcadena común más larga encontrada.
    // 'endPos' guarda la posición final de dicha subcadena en 's1'.

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Si los caracteres coinciden, se extiende la longitud de la subcadena común previa (en 'dp[i-1][j-1]') sumando 1.
                if (dp[i][j] > length) { // Si se encuentra una subcadena más larga, actualiza 'length' y guarda la posición de fin en 'endPos'
                    length = dp[i][j];
                    endPos = i - 1;
                }
            }
            // Si los caracteres no coinciden, dp[i][j] se mantiene como 0, lo que indica que no hay subcadena común terminando en estas posiciones.
        }
    }

    int startPos = endPos - length + 1;
    return make_pair(startPos + 1, endPos + 1); // Convertir a base 1
}

int main() {
    string t1 = readFile("transmission1.txt");
    t1.erase(remove(t1.begin(), t1.end(), '\n'), t1.end());

    string t2 = readFile("transmission2.txt");
    t2.erase(remove(t2.begin(), t2.end(), '\n'), t2.end());

    string m1 = readFile("mcode1.txt");
    string m2 = readFile("mcode2.txt");
    string m3 = readFile("mcode3.txt");

    cout << "\ntransmission1 comparison with mcodes: \n";
    cout << "- mcode1: \n";
    if (kmpBool(t1, m1)) {
        cout << "  " << "true" << " pos:" << kmpPos(t1, m1) << endl;
    } else {
        cout << "  " << "false" << endl;
    }

    cout << "- mcode2: \n";
    if (kmpBool(t1, m2)) {
        cout << "  " << "true" << " pos:" << kmpPos(t1, m2) << endl;
    } else {
        cout << "  " << "false" << endl;
    }

    cout << "- mcode3: \n";
    if (kmpBool(t1, m3)) {
        cout << "  " << "true" << " pos:" << kmpPos(t1, m3) << endl;
    } else {
        cout << "  " << "false" << endl;
    }

    cout << "\ntransmission2 comparison with mcodes: \n";
    cout << "- mcode1: \n";
    if (kmpBool(t2, m1)) {
        cout << "  " << "true" << " pos:" << kmpPos(t2, m1) << endl;
    } else {
        cout << "  " << "false" << endl;
    }

    cout << "- mcode2: \n";
    if (kmpBool(t2, m2)) {
        cout << "  " << "true" << " pos:" << kmpPos(t2, m2) << endl;
    } else {
        cout << "  " << "false" << endl;
    }

    cout << "- mcode3: \n";
    if (kmpBool(t2, m3)) {
        cout << "  " << "true" << " pos:" << kmpPos(t2, m3) << endl << endl;
    } else {
        cout << "  " << "false" << endl << endl;
    }

    pair<int, int> lps = longestPalindromeManacher(t1);
    cout << "Longest Palindrome in transmission1 using Manacher: " << t1.substr(lps.first - 1, lps.second - lps.first + 1) << endl;
    cout << "Position: " << lps.first-1 << "   Length: "<< lps.second - lps.first + 1 <<endl;

    pair<int, int> lps2 = longestPalindromeManacher(t2);
    cout << "Longest Palindrome in transmission2 using Manacher: " << t2.substr(lps2.first - 1, lps2.second - lps2.first + 1) << endl;
    cout << "Position: " << lps2.first-1 << "   Length: "<< lps2.second - lps2.first + 1 <<endl;

    cout << endl;

    pair<int, int> lcs = longestCommonSubstring(t1, t2);
    cout << "Longest common substring between transmission1 and transmission2: " << t1.substr(lcs.first - 1, lcs.second - lcs.first + 1) << endl << endl;


    return 0;
}