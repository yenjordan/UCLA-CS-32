// #include <iostream>
// using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    // If the start location is equal to the ending location, then we've solved the maze
    if (sr == er && sc == ec)
        return true;

    // Mark the start location as visited
    maze[sr][sc] = '!';

    // Check each of the four directions
    if (maze[sr][sc + 1] == '.' && pathExists(maze, sr, sc + 1, er, ec)) // Move EAST
        return true;
    if (maze[sr + 1][sc] == '.' && pathExists(maze, sr + 1, sc, er, ec)) // Move SOUTH
        return true;
    if (maze[sr][sc - 1] == '.' && pathExists(maze, sr, sc - 1, er, ec)) // Move WEST
        return true;
    if (maze[sr - 1][sc] == '.' && pathExists(maze, sr - 1, sc, er, ec)) // Move NORTH
        return true;

    // If no path was found, mark the current cell as unvisited and return false
    maze[sr][sc] = '.';
    return false;
}

// int main()
//         {
//             char maze[10][10] = {
//                 { 'X','X','X','X','X','X','X','X','X','X' },
//                 { 'X','.','.','.','X','.','.','X','.','X' },
//                 { 'X','.','X','X','X','.','.','.','.','X' },
//                 { 'X','.','X','.','X','X','X','X','.','X' },
//                 { 'X','X','X','.','.','.','.','.','.','X' },
//                 { 'X','.','.','.','X','.','X','X','.','X' },
//                 { 'X','.','X','.','X','.','.','X','.','X' },
//                 { 'X','.','X','X','X','X','.','X','.','X' },
//                 { 'X','.','.','X','.','.','.','X','.','X' },
//                 { 'X','X','X','X','X','X','X','X','X','X' }
//             };

//             if (pathExists(maze, 4,3, 1,8))
//                 cout << "Solvable!" << endl;
//             else
//                 cout << "Out of luck!" << endl;
//         }