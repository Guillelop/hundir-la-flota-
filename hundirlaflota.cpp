#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int FILAS = 8;
const int COLUMNAS = 8;

void inicializarTablero(int tablero[FILAS][COLUMNAS]){
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            tablero[i][j] = 0;
        }
    }
}

void colocarBarcos(int tablero[FILAS][COLUMNAS]){
    srand(time(NULL));
    int fila, columna;
    for(int i = 0; i < 8; i++){
        do{
            fila = rand() % FILAS;
            columna = rand() % COLUMNAS;
        } while(tablero[fila][columna] != 0);
        tablero[fila][columna] = 1;
    }
}

void mostrarTablero(int tablero[FILAS][COLUMNAS]){
    cout << endl;
    cout << "\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8" << endl;
    cout << endl;
    for(int i = 0; i < FILAS; i++){
        cout << i+1 << "\t";
        for(int j = 0; j < COLUMNAS; j++){
            if(tablero[i][j] == 0){
                cout << "~\t";
            } else if(tablero[i][j] == 1){
                cout << "*\t";
            } else if(tablero[i][j] == 8){
                cout << "O\t";
            } else {
                cout << "X\t";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool disparar(int tablero[FILAS][COLUMNAS], int &aciertos){
    int fila, columna;
    cout << "Introduce una fila: ";
    cin >> fila;
    cout << "Introduce una columna: ";
    cin >> columna;
    fila--;
    columna--;
    if(tablero[fila][columna] == 0){
        cout << "\t\tAgua" << endl;
        tablero[fila][columna] = 8;
        return false;
    } else if(tablero[fila][columna] == 1){
        cout << "\t\t¡Acertaste!" << endl;
        tablero[fila][columna] = 9;
        aciertos++;
        return true;
    } else {
        cout << "\t\tYa habías disparado ahí" << endl;
        return false;
    }
}

int main(){
    int tablero[FILAS][COLUMNAS];
    int aciertos = 0;
    int intentos = 0;
    bool quedanBarcos = true;
    inicializarTablero(tablero);
    colocarBarcos(tablero);
    cout << "\t¡Bienvenido a Hundir la Flota!" << endl;
    while(quedanBarcos){
        mostrarTablero(tablero);
        bool acierto = disparar(tablero, aciertos);
        if(aciertos == 8){
            quedanBarcos = false;
            cout << "¡Ganaste! Has hundido todos los barcos en " << intentos+1 << " intentos." << endl;
        } else {
            intentos++;
        }
    }
    return 0;
}
