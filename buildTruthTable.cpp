#include <iostream>
#include <math.h>

using namespace std;

const int MAX_VARIABLES = 10;

bool* convertirProductoString(string producto) {
    int caracteres = producto.size();
    
    bool* vector = new bool[caracteres];
    
    for (int i=0 ; i<caracteres ; i++) {
        vector[i] = isupper(producto[i]);
        // cout << vector[i];
    }
    // cout << endl;
    return vector;
}

bool* pedirValoresDeProducto(int variables) {
    
    string s;
    cout << "Introduzca los valores del producto: ";
    cin >> s;
    // cout << "Producto: " << s << endl;
    
    return convertirProductoString(s);
}

bool calcularSuma(bool* producto, int variables) {
    // cout << "Calculando la suma del producto:" << endl;
    
    bool resultado = producto[0];
    
    // cout << resultado << " | ";
    
    for (int i = 1 ; i < variables ; i++) {
        // cout << producto[i] << " | ";    
        resultado = resultado | producto[i];
    }
    // cout << " = " << resultado << endl;
    return resultado;
}

bool calcularProducto(bool* producto, int productos) {
    bool resultado = producto[0];
    
    for (int i = 1 ; i < productos ; i++) {
        resultado = resultado & producto[i];
    }
    
    return resultado;
}


// bool calcularFilaTabla(bool* fila, int variables) {
    
// }

void imprimirMatrizDeVariables(bool variables[][50], int numVariables, int numProductos) {
    for (int i = 0 ; i < numProductos ; i++) {
        for (int j = 0 ; j < numVariables ; j++) {
            cout << variables[i][j] << " ";
        }
        cout << endl;
    }
}

void imprimirVector(bool* arreglo, int variables) {
    for (int i = 0 ; i < variables ; i++) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

bool** generarPermutacionesTablaDeVerdad(int variables) {
    int max = pow(2, variables);
    bool** matriz = new bool*[max];
    for (int i=0 ; i < max ; i++) {
        matriz[i] = new bool[variables];
        
        int aux = 1;
        int pos = 0;
        
        for (int j = 0 ; j < variables ; j++) {
            matriz[i][pos++] = i & aux;
            aux = aux << 1;
        }
    }
    
    // imprimir tabla
    // for (int i = 0 ; i < max ; i++) {
    //     for (int j = 0 ; j < variables ; j++) {
    //         cout << matriz[i][j] << " " ;
    //     }
    //     cout << endl;
    // }
    
    return matriz;
}

bool* obtenerVariablesEvaluadas(bool* aEvaluar, bool* funcion, int variables) {
    // cout << "Evaluando ";
    // imprimirVector(aEvaluar, variables);
    // cout << " con ";
    // imprimirVector(funcion, variables);
    bool* nueva = new bool[variables];
    for (int i = 0 ; i < variables ; i++) {
        if (funcion[i] == false) {
            // negar en caso de que la funcion este negada
            // cout << "negando!" << endl;
            nueva[i] = !aEvaluar[i];
        } else {
            nueva[i] = aEvaluar[i];
        }
    }
    
    // cout << " resulta ";
    // imprimirVector(nueva, variables);
    return nueva;
}


void imprimirTablaDeVerdadConResultado(bool** matrizVerdad, bool* resultados, int numVariables, int numResultados) {
    cout << "=========== Tabla de Verdad ===========" << endl ;
    char letra = 'A';
    for (int i = 0 ; i < numVariables ; i++) {
        cout << letra++ << " ";
    }
    cout << "| F" << endl;
    
    for (int i = 0 ; i < numResultados ; i++) {
        for (int j = 0 ; j < numVariables ; j++) {
            cout << matrizVerdad[i][j] << " ";
        }
        cout << "| " << resultados[i] << endl;
    }
}

int main()
{
    // Maximo 5 variables
    // Los valores seran alfabeticos, en donde la variable en Mayuscula sera positiva, y la variable en Minuscula sera negativa.
    int numVariables;
    int numProductos;
    cout << "Bienvenido al programa, a continuacion responda lo siguiente\n";
    cout << "_____________________________________________________________\n";
    cout << "Numero de variables: \n";
    cin >> numVariables;
    cout << "Numero de productos: \n";
    cin >> numProductos;
    
    
    bool** matrizVerdad = generarPermutacionesTablaDeVerdad(numVariables);
    // Definir la matriz de variables y el vector de productos
    bool variables[numProductos][50];
    bool productos[numProductos];
    
    // Pedir los valores de los productos
    for (int i = 0 ; i < numProductos ; i++) {
        bool* producto = pedirValoresDeProducto(numVariables);
        // Guardar en la matriz de productos
        for (int j = 0 ; j < numVariables ; j++) {
            variables[i][j] = producto[j];
        }
    }
    // imprimirMatrizDeVariables(variables, numVariables, numProductos);
    
    // productos[i] = calcularSuma(producto, numVariables);
    // Evalúa tabla de verdad
    int permutaciones = pow(2, numVariables);
    bool resultados[permutaciones];
    
    for (int i = 0 ; i < permutaciones ; i++) {
        bool* entradaDeMatriz = matrizVerdad[i];
        
        // j es el numero de producto
        for (int j = 0 ; j < numProductos ; j++) {
            bool* evaluacion = obtenerVariablesEvaluadas(entradaDeMatriz, variables[j], numVariables);
            
            // Imprimir evaluacion
            // cout << "Variables evaluadas con el " << j+1 << " producto" << endl;
            // imprimirVector(evaluacion, numVariables);
            
            productos[j] = calcularSuma(evaluacion, numVariables);
        }
        
        bool resultadoFinal = calcularProducto(productos, numProductos);
        resultados[i] = resultadoFinal;
    }
    
    imprimirTablaDeVerdadConResultado(matrizVerdad, resultados, numVariables, permutaciones);
    
    return 0;
}
