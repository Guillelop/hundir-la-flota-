#include <iostream>
#include <cstring>
using namespace std;

const int BOARD_SIZE = 10;
const char SHIP_SYMBOL = 'S';
const char HIT_SYMBOL = 'X';
const char MISS_SYMBOL = 'O';

// Estructura que representa una coordenada en el tablero
struct Coordinate {
    int row;
    int col;
};

// Estructura que representa un barco en el tablero
struct Ship {
    char symbol; // Símbolo que se mostrará en el tablero para representar al barco
    int size; // Tamaño del barco
    Coordinate position; // Coordenada de la casilla del barco que está más a la izquierda o más arriba
    bool vertical; // true si el barco está en posición vertical, false si está en posición horizontal
    bool destroyed; // true si el barco ha sido destruido, false si no
};

// Función que inicializa el tablero con agua
void initBoard(char board[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '~';
        }
    }
}

// Función que muestra el tablero en la consola
void printBoard(char board[][BOARD_SIZE]) {
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << char('A' + i) << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Función que coloca un barco en el tablero
void placeShip(char board[][BOARD_SIZE], Ship ship) {
    int row = ship.position.row;
    int col = ship.position.col;
    for (int i = 0; i < ship.size; i++) {
        board[row][col] = ship.symbol;
        if (ship.vertical) {
            row++;
        } else {
            col++;
        }
    }
}

// Función que valida si un barco puede ser colocado en una posición dada
bool canPlaceShip(char board[][BOARD_SIZE], Ship ship) {
    int row = ship.position.row;
    int col = ship.position.col;
    for (int i = 0; i < ship.size; i++) {
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != '~') {
            return false;
        }
        if (ship.vertical) {
            row++;
        } else {
            col++;
        }
    }
    return true;
}

// Función que pide al usuario las coordenadas donde quiere atacar
Coordinate getAttackCoordinates() {
    Coordinate c;
    cout << "Introduce las coordenadas de tu ataque (fila columna): ";
    cin >> c.row >> c.col;
    c.row--; // Restamos 1 para que el índice de la fila empiece en 0
    c.col--;
    return c;
}

// Función que actualiza el tablero después de un ataque
void attack(char board[][BOARD_SIZE], Ship ships[], int numShips, Coordinate c) {
    if (board[c.row][c.col] == SHIP_SYMBOL) {
        board[c.row][c.col] = HIT_SYMBOL;
        for (int i = 0; i < numShips; i++) {
            if (ships[i].position.row == c.row && ships[i].position.col == c.col) {
                ships[i].destroyed = true;
                cout << "¡Has hundido un barco!" << endl;
                break;
            }
        }
    } else {
        board[c.row][c.col] = MISS_SYMBOL;
        cout << "¡Has fallado!" << endl;
    }
}

// Función que valida si todos los barcos han sido destruidos
bool allShipsDestroyed(Ship ships[], int numShips) {
    for (int i = 0; i < numShips; i++) {
        if (!ships[i].destroyed) {
            return false;
        }
    }
    return true;
}

// Programa principal
int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    Ship ships[] = {
        {'C', 5, {0, 0}, true, false},
        {'B', 4, {2, 3}, false, false},
        {'D', 3, {4, 6}, true, false},
        {'S', 3, {8, 1}, false, false},
        {'P', 2, {6, 4}, true, false}
    };
    int numShips = sizeof(ships) / sizeof(ships[0]);
    
    initBoard(board);
    for (int i = 0; i < numShips; i++) {
        while (!canPlaceShip(board, ships[i])) {
            ships[i].position.row = rand() % BOARD_SIZE;
            ships[i].position.col = rand() % BOARD_SIZE;
}
placeShip(board, &ships[i]);
}
playGame(board, ships, numShips);

return 0;
}
