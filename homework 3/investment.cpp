// #include <iostream>
// #include <string>
// using namespace std;

class Investment {
public:
    Investment(string name, int price) : m_n(name), m_p(price) {}
    virtual ~Investment() {}
    string name() const { return m_n; }
    int purchasePrice() const { return m_p; }
    virtual string description() const = 0;
    virtual bool fungible() const { return false; }

private:
    string m_n;
    int m_p;
};

class Painting : public Investment {
public:
    Painting(string name, int price) : Investment(name, price) {}
    ~Painting() { cout << "Destroying " << name() << ", a painting" << endl; }
    virtual string description() const { return "painting"; }
};

class Stock : public Investment {
public:
    Stock(string name, int price, string description) : Investment(name, price), m_d(description) {}
    ~Stock() { cout << "Destroying " << name() << ", a stock holding" << endl; }
    virtual string description() const { return "stock trading as " + m_d; }
    virtual bool fungible() const { return true; }

private:
    string m_d;
};

class House : public Investment {
public:
    House(string name, int price) : Investment(name, price) {}
    ~House() { cout << "Destroying the house " << name() << endl; }
    virtual string description() const { return "house"; }
};

// void display(const Investment* inv)
// {
//     cout << inv->name();
//     if (inv->fungible())
//         cout << " (fungible)";
//     cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
// }

// int main()
// {
//     Investment* portfolio[4];
//     portfolio[0] = new Painting("Salvator Mundi", 450300000);
//       // Stock holdings have a name, value, and ticker symbol
//     portfolio[1] = new Stock("Nvidia", 50000, "NVDA");
//     portfolio[2] = new Stock("Costco", 10000, "COST");
//     portfolio[3] = new House("4 Privet Drive", 670000);

//     for (int k = 0; k < 4; k++)
//         display(portfolio[k]);

//       // Clean up the investments before exiting
//     cout << "Cleaning up." << endl;
//     for (int k = 0; k < 4; k++)
//         delete portfolio[k];
// }
