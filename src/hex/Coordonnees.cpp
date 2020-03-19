#include "hex/Coordonnees.hpp"
#include <stdexcept>
#include <sstream>

hex::Coordonnees::Coordonnees(int q, int r) : q(q), r(r) {}

void hex::Coordonnees::translate(Direction dir, int distance)
{
    switch (dir)
    {
    case Direction::NORD:
        q += distance;
        break;
    case Direction::SUD:
        q -= distance;
        break;
    case Direction::NORD_OUEST:
        q += distance;
        r -= distance;
        break;
    case Direction::SUD_EST:
        q -= distance;
        r += distance;
        break;
    case Direction::NORD_EST:
        r += distance;
        break;
    case Direction::SUD_OUEST:
        r -= distance;
        break;
    default:
        std::stringstream ss;
        ss << "Direction : " << (size_t)dir << " non supportée.";
        throw std::invalid_argument(ss.str());
    }
}

std::ostream &hex::operator<<(std::ostream &os, Coordonnees &c)
{
    os << "Coordonnees(" << c.getColumn() << ", " << c.getRow() << ")";
    return os;
}
