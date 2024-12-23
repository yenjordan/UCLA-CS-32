#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }

private:
    int m_row;
    int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc)); // Enqueue the starting coordinate
    maze[sr][sc] = '!'; // Mark the starting cell as visited

    while (!coordQueue.empty()) {
        Coord current = coordQueue.front();
        coordQueue.pop();

        int r = current.r();
        int c = current.c();

        // Check if we reached the end coordinate
        if (r == er && c == ec)
            return true;

        // Check each possible move
        if (maze[r][c+1] == '.') { // Move EAST
            coordQueue.push(Coord(r, c+1));
            maze[r][c+1] = '!'; // Mark the cell as visited
        }
        if (maze[r+1][c] == '.') { // Move SOUTH
            coordQueue.push(Coord(r+1, c));
            maze[r+1][c] = '!'; // Mark the cell as visited
        }
        if (maze[r][c-1] == '.') { // Move WEST
            coordQueue.push(Coord(r, c-1));
            maze[r][c-1] = '!'; // Mark the cell as visited
        }
        if (maze[r-1][c] == '.') { // Move NORTH
            coordQueue.push(Coord(r-1, c));
            maze[r-1][c] = '!'; // Mark the cell as visited
        }
    }

    // If we reach here, there's no path
    return false;
}

// int main() {
//     char maze[10][10] = {
//         { 'X','X','X','X','X','X','X','X','X','X' },
//         { 'X','.','.','.','X','.','.','X','.','X' },
//         { 'X','.','X','X','X','.','.','.','.','X' },
//         { 'X','.','X','.','X','X','X','X','.','X' },
//         { 'X','X','X','.','.','.','.','.','.','X' },
//         { 'X','.','.','.','X','.','X','X','.','X' },
//         { 'X','.','X','.','X','.','.','X','.','X' },
//         { 'X','.','X','X','X','X','.','X','.','X' },
//         { 'X','.','.','X','.','.','.','X','.','X' },
//         { 'X','X','X','X','X','X','X','X','X','X' }
//     };

//     if (pathExists(maze, 4, 3, 1, 8))
//         cout << "Solvable!" << endl;
//     else
//         cout << "Out of luck!" << endl;

//     return 0;
// }

