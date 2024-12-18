#include <vector>
#include <iostream>

using namespace std;

vector<vector<int> > lista_de_ady, matriz_de_ady;

int grado_mat(int v) {
    int grado = 0;

    // Recordemos que M[i][j] = 1 o 0
    for (int i = 0; i < matriz_de_ady.size(); i++)
        grado += matriz_de_ady[v][i];

    return grado;
}

int grado_list(int v) {
    return lista_de_ady[v].size();
}

int pertenece(int v, vector<int>& Nu) {
    for(int i = 0; i < Nu.size(); i++)
        if (v == Nu[i]) 
            return 1;

    return 0;
}

vector<int> interseccion_vecinos_lista(vector<int>& S) {
    int n = lista_de_ady.size();
    vector<bool> vecindario(n, false);
    
    // Recorremos todos los nodos
    for(int v = 1; v < n; v++) {
        
        // Pertene a todos los elementos del conjunto?
        int suma = 0;
        for (int u: S) suma += pertenece(v, lista_de_ady[u]);

        // Si pertenece a todos agregamos
        if (suma == S.size()) vecindario[v] = true;
        
    }
                
    // Armamos la solución
    vector<int> result;
    for (int i = 0; i < n; i++) 
        if(vecindario[i]) result.push_back(i);
    
    return result;
}  

vector<int> interseccion_vecinos_mat(vector<int>& S) {
    int n = matriz_de_ady.size();
    vector<bool> vecindario(n, false);
    
    // Recorremos todos los nodos
    for(int v = 1; v < n; v++) {
        
        // Pertene a todos los elementos del conjunto?
        int suma = 0;
        for (int u: S) suma += matriz_de_ady[u][v];

        // Si pertenece a todos agregamos
        if (suma == S.size()) vecindario[v] = true;
        
    }
                
    // Armamos la solución
    vector<int> result;
    for (int i = 0; i < n; i++) 
        if(vecindario[i]) result.push_back(i);
    
    return result;
} 

vector<int> interseccion_opt(vector<int>& S) {
    int n = lista_de_ady.size();
    vector<int> times(n,0);
    vector<bool> cumpleanero(n,false);

    // Bitmap
    for (int i = 0; i < S.size(); i++) cumpleanero[S[i]] = true;

    // Recorremos el grafo
    for (int v = 0; v < n; v++) {
        if (cumpleanero[v]) continue;

        for (int u: lista_de_ady[v])
            if (cumpleanero[u]) 
                times[v]++;
    }

    // Armamos la solución
    vector<int> result;
    for (int i = 0; i < n; i++) 
        if(times[i] == S.size())
            result.push_back(i);
    
    return result;
}

// Compilar + Ejecutar:
// g++ -w -o claseEjec clase.cpp;./claseEjec < grafito.txt
int main() {
    // n = #nodos
    // m = #arsitas
    // s = #S
    
    int n, m, s; cin >> n >> m >> s;

    // Inicializamos las estructuras
    vector<int> S(s);
    lista_de_ady.assign(n+1, vector<int>());
    matriz_de_ady.assign(n+1, vector<int>(n+1, 0));

    // Leemos el conjunto S
    for(int i = 0; i < s; i++) cin >> S[i];

    // Leemos las aristas
    while(m--) {
        int u, v; cin >> u >> v;

        lista_de_ady[u].push_back(v);
        lista_de_ady[v].push_back(u);

        matriz_de_ady[v][u] = 1;
        matriz_de_ady[u][v] = 1;
    }

    vector<int> vecindarioL = interseccion_vecinos_lista(S);
    vector<int> vecindarioM = interseccion_vecinos_mat(S);
    vector<int> vecindarioO = interseccion_opt(S);

    // Prints

    cout << "Lista: ";
    for(int i = 0; i < vecindarioL.size(); i++) cout << vecindarioL[i] << " ";
    cout << endl;

    cout << "Matriz: ";
    for(int i = 0; i < vecindarioM.size(); i++) cout << vecindarioM[i] << " ";
    cout << endl;

    cout << "Lineal: ";
    for(int i = 0; i < vecindarioO.size(); i++) cout << vecindarioO[i] << " ";
    cout << endl;

}