/** MY FUNCTION GOES WEST, EAST, NORTH, SOUTH **/

#include <iostream>
#include <queue>

using namespace std;


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
void draw(string maze[], int nRows, int nCols);



int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    

    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    
}



void draw(string maze[], int nRows, int nCols) {
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            cerr << maze[i][j];
        }
        cerr << endl;
    }
}

/** FUNCTION UTILIZES A QUEUE TO CHECK IF A MAZE IS SOLVABLE, MOVING FROM (SR, SC) TO (ER, EC) **/
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    Coord unused(nRows, nCols);
    queue<Coord> s1;
    s1.push(unused);
    s1.pop(); // to get rid of compiler warning in g++ from not using nRows or nCols
    Coord a(sr,sc);
    s1.push(a);
    maze[a.r()][a.c()] = '#'; // if index has been visited, the function will replace '.' with '#' to indicate
    s1.pop();
    
    do {
        if (a.r() == er && a.c() == ec)
            return true;
        
        int west_col = a.c() - 1;
        int east_col = a.c() + 1;
        int north_row = a.r() - 1;
        int south_row = a.r() + 1;
        
        
        if (maze[a.r()][west_col] != 'X' && maze[a.r()][west_col] != '#') { // IF A POINT IS NOT A WALL OR HAS NOT BEEN DISCOVERED
            Coord west(a.r(), west_col);
            maze[west.r()][west.c()] = '#';
            s1.push(west);
        }
        
        if (maze[a.r()][east_col] != 'X' && maze[a.r()][east_col] != '#') {
            Coord east(a.r(), east_col);
            maze[east.r()][east.c()] = '#';
            s1.push(east);
        }
        
        if (maze[north_row][a.c()] != 'X' && maze[north_row][a.c()] != '#') {
            Coord north(north_row,a.c());
            maze[north.r()][north.c()] = '#';
            s1.push(north);
        }
        
        if (maze[south_row][a.c()] != 'X' && maze[south_row][a.c()] != '#') {
            Coord south(south_row,a.c());
            maze[south.r()][south.c()] = '#';
            s1.push(south);
        }
        a = s1.front();
        s1.pop();
    } while (!(s1.empty()));
    return false;
}
