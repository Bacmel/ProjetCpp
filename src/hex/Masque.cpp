#include "hex/Masque.hpp"
#include <stdexcept>

namespace hex
{
    Masque::Masque() : std::set<Coordonnees>() {}

    Masque::Masque(const Masque& autre) : std::set<Coordonnees>(autre) {}

    Masque::Masque(Masque&& autre) : std::set<Coordonnees>(autre) {}

    Masque& Masque::operator=(const Masque& autre)
    {
        std::set<Coordonnees>::operator=(autre);
        return *this;
    }

    Masque& Masque::operator=(Masque&& autre)
    {
        std::set<Coordonnees>::operator=(autre);
        return *this;
    }

    Masque::~Masque() {}

    Masque Masque::operator||(const Masque& autre) const
    {
        Masque ou(autre);
        for(auto itr = this->begin(); itr != this->end(); itr++)
        {
            ou.insert(*itr);
        }
        return ou;
    }

    Masque Masque::operator&&(const Masque& autre) const
    {
        Masque et;
        for(auto itr = this->begin(); itr != this->end(); itr++)
        {
            if(autre(*itr))
            {
                et.insert(*itr);
            }
        }
        return et;
    }

    Masque Masque::operator+(const Coordonnees& autre) const
    {
        Masque plus(*this);
        plus.insert(autre);
        return plus;
    }

    Masque Masque::operator-(const Coordonnees& autre) const
    {
        Masque moins(*this);
        moins.erase(moins.find(autre));
        return moins;
    }

    Masque Masque::deplacer(const Coordonnees& vecteur) const
    {
        Masque deplace;
        for(auto itr = this->begin(); itr!= this->end(); itr++)
        {
            deplace.insert((*itr)+vecteur);
        }
        return deplace;
    }

    bool Masque::operator()(const Coordonnees& c) const
    {
        if(this->find(c) != this->end())
        {
            return true;
        }
        return false;
    }
} // namespace hex
