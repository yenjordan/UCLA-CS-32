#include "History.h"
#include "Tooter.h"
#include "globals.h"
#include "Player.h"

#include <iostream>


using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols)
{
    // Initialize history grid with dots
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            m_historyGrid[r][c] = '.';
        }
    }
}

bool History::record(int r, int c)
{
    // Check if the position is within the city bounds
    if (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols)
    {
        char& gridChar = m_historyGrid[r - 1][c - 1];
        // Update the history grid with the number of conversions
        if (gridChar == '.')
            gridChar = 'A'; // First conversion
        else if (gridChar >= 'A' && gridChar < 'Z')
            gridChar++; // Increment conversion count
        // If conversion count reaches Z, keep it at Z
        return true;
    }
    else
    {
        return false; // Position is not within city bounds
    }
}

void History::display() const
{
    clearScreen();
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            cout << m_historyGrid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
