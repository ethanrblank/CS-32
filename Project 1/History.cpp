#include "History.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols) {
    rows = nRows;
    cols = nCols;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            table[i][j] = '.';
        }
    }
}

bool History::record(int r, int c) {
    if (r < 0  ||  r > rows  ||  c < 0  ||  c > cols)
        return false;
    char value = table[r][c];
    switch (value) {
        case '.': {
            table[r][c] = 'A';
            break;
        }
        case 'A' : {
            table[r][c] = 'B';
            break;
        }
        case 'B' : {
            table[r][c] = 'C';
            break;
        }
        case 'C' : {
            table[r][c] = 'D';
            break;
        }
        case 'D' : {
            table[r][c] = 'E';
            break;
        }
        case 'E' : {
            table[r][c] = 'F';
            break;
        }
        case 'F' : {
            table[r][c] = 'G';
            break;
        }
        case 'G' : {
            table[r][c] = 'H';
            break;
        }
        case 'H' : {
            table[r][c] = 'I';
            break;
        }
        case 'I' : {
            table[r][c] = 'J';
            break;
        }
        case 'J' : {
            table[r][c] = 'K';
            break;
        }
        case 'K' : {
            table[r][c] = 'L';
            break;
        }
        case 'L' : {
            table[r][c] = 'M';
            break;
        }
        case 'M' : {
            table[r][c] = 'N';
            break;
        }
        case 'N' : {
            table[r][c] = 'O';
            break;
        }
        case 'P' : {
            table[r][c] = 'Q';
            break;
        }
        case 'Q' : {
            table[r][c] = 'R';
            break;
        }
        case 'R' : {
            table[r][c] = 'S';
            break;
        }
        case 'S' : {
            table[r][c] = 'U';
            break;
        }
        case 'U' : {
            table[r][c] = 'V';
            break;
        }
        case 'V' : {
            table[r][c] = 'W';
            break;
        }
        case 'X' : {
            table[r][c] = 'Y';
            break;
        }
        case 'Y' : {
            table[r][c] = 'Z';
            break;
        }
        case 'Z' : {
            table[c][r] = 'Z';
            break;
        }
        default:
            break;
    }
    return true;
}

void History::display() const {
    clearScreen();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= cols; ++j) {
            cout << table[i][j];
        }
        cout << endl;
    }
}
