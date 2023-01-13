#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


class IDGenerator
{
private:
    static IDGenerator* instance;
    int nextID;
    IDGenerator() : nextID(0) {}

public:
    static IDGenerator* getInstance()
    {
        if (!instance)
            instance = new IDGenerator;
        return instance;
    }

    int getNextID()
    {
        return nextID++;
    }
};

IDGenerator* IDGenerator::instance = nullptr;


class Imbracaminte
{
protected:
    std::string nume;
    double pret;
    int id;

public:
    Imbracaminte(std::string nume, double pret) : nume(nume), pret(pret)
    {
        id = IDGenerator::getInstance()->getNextID();
    }

    virtual Imbracaminte* clone() = 0;

    std::string getNume()
    {
        return nume;
    }

    double getPret()
    {
        return pret;
    }

    int getID()
    {
        return id;
    }

    virtual void print() = 0;

    friend std::ostream &operator<<(std::ostream &os, Imbracaminte &imbracaminte) {
        imbracaminte.print();
        return os;
    }
};


class Bluza : public Imbracaminte
{
private:
    std::string marime;
    std::string culoare;

public:
    Bluza(std::string nume, double pret, std::string marime, std::string culoare) : Imbracaminte(nume, pret), marime(marime), culoare(culoare)
    {
    }

    Bluza* clone()
    {
        return new Bluza(nume, pret, marime, culoare);
    }

    void print()
    {
        std::cout << "Bluza: " << nume << " (" << marime << ", " << culoare << ") - $" << pret << std::endl;
    }
};


class Pantaloni : public Imbracaminte
{
private:
    std::string marime;
    std::string culoare;

public:
    Pantaloni(std::string nume, double pret, std::string marime, std::string culoare) : Imbracaminte(nume, pret), marime(marime), culoare(culoare)
    {
    }

    Pantaloni* clone()
    {
        return new Pantaloni(nume, pret, marime, culoare);
    }

    void print()
    {
        std::cout << "Pantaloni: " << nume << " (" << marime << ", " << culoare << ") - $" << pret << std::endl;
    }
};


class Accesorii : public Imbracaminte
{
protected:
    Imbracaminte* imbracaminte;

public:
    Accesorii(Imbracaminte* imbracaminte) : Imbracaminte(imbracaminte->getNume(), imbracaminte->getPret()), imbracaminte(imbracaminte) {}

    virtual void print() = 0;
};


class Buzunare : public Accesorii
{
public:
    Buzunare(Imbracaminte* imbracaminte) : Accesorii(imbracaminte) {}

    void print()
    {
        std::cout << "Am adaugat buzunare la: ";
        imbracaminte->print();
    }
};


template <typename T>
class ComparaID {
public:
    bool operator()(const T &ob1, const T &ob2) {
        return ob1->getID() < ob2->getID();
    }
};


template <class T>
void SortareImbracaminte(std::vector <T*> &ListaImbracaminte) {
    std::sort(ListaImbracaminte.begin(), ListaImbracaminte.end(),
            [](const T* ob1, const T* ob2) { return ob1->getNume() < ob2->getNume(); });
}


template <>
void SortareImbracaminte(std::vector <Bluza*> &ListaBluze) {
    std::sort(ListaBluze.begin(), ListaBluze.end(),
              [](Bluza *ob1, Bluza *ob2) { return ob1->getNume() < ob2->getNume(); });
}

int main()
{
    Bluza* bluza1 = new Bluza("Helanca", 19.99, "M", "Rosie");
    Bluza* bluza2 = new Bluza("Bluza", 29.99, "L", "Verde");
    Pantaloni* pantaloni = new Pantaloni("Blugi", 39.99, "L", "Albastri");

    std::vector<Imbracaminte*> haine;
    haine.push_back(bluza1);
    haine.push_back(bluza2);
    haine.push_back(pantaloni);

    std::sort(haine.begin(), haine.end(), ComparaID<Imbracaminte*>());

    for (auto ob : haine)
        ob->print();

    return 0;
}
