#ifndef TOOTER_H
#define TOOTER_H

class City;  // This is needed to let the compiler know that City is a
             // type name, since it's mentioned in the Tooter declaration.

class Tooter
{
  public:
        // Constructor
    Tooter(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};

#endif