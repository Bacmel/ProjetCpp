#ifndef COORDONNEES_HPP
#define COORDONNEES_HPP

#include <ostream>
namespace hex
{

enum class Direction
{
    NORD_OUEST,
    NORD,
    NORD_EST,
    SUD_EST,
    SUD,
    SUD_OUEST
};

class Coordonnees
{
protected:
    int q;
    int r;

public:
    Coordonnees(int q = 0, int r = 0);
    virtual ~Coordonnees() = default;

    int getColumn() { return this->q; }
    int getRow() { return this->r; }
    void translate(Direction dir, int distance = 1);
};

std::ostream &operator<<(std::ostream &os, Coordonnees &c);

}; // namespace hex
#endif
