#ifndef CARTE_HEXAGONE_HPP
#define CARTE_HEXAGONE_HPP

#include "hex/ICarte.hpp"
#include <stdexcept>
#include <sstream>
#include <cmath>

namespace hex
{

template <typename T>
class CarteHexagone : public ICarte<T>
{
protected:
    /** Nombre de cases entre la case centrale et le bord */
    size_t rayon;
    T **plateau;

public:
    explicit CarteHexagone(size_t rayon) : rayon(rayon), plateau(nullptr)
    {
        size_t diametre = 2 * this->rayon + 1;
        this->plateau = new T *[diametre];
        for (size_t i = 1; i <= this->rayon; i++)
        {
            this->plateau[this->rayon + i] = new T[diametre - i];
            this->plateau[this->rayon - i] = new T[diametre - i];
        }
        this->plateau[this->rayon] = new T[diametre];
    }

    ~CarteHexagone()
    {
        size_t diametre = 2 * this->rayon + 1;
        for (size_t i = 0; i < diametre; i++)
        {
            delete[] this->plateau[i];
        }
        delete[] this->plateau;
    }

    virtual T &operator()(Coordonnees &c)
    {
        if (abs(c.getRow()) > (int)this->rayon || abs(c.getColumn()) > (int)this->rayon)
        {
            std::stringstream ss;
            ss << '(' << c.getColumn() << ", " << c.getRow() << ") est hors de l'hexagone de rayon " << this->rayon << ".";
            throw std::out_of_range(ss.str());
        }
        return this->plateau[this->rayon - c.getColumn()][this->rayon - c.getRow()];
    }

    virtual const T &operator()(Coordonnees &c) const
    {
        if (abs(c.getRow()) > (int)this->rayon || abs(c.getColumn()) > (int)this->rayon)
        {
            std::stringstream ss;
            ss << '(' << c.getColumn() << ", " << c.getRow() << ") est hors de l'hexagone de rayon " << this->rayon << ".";
            throw std::out_of_range(ss.str());
        }
        return this->plateau[this->rayon - c.getColumn()][this->rayon - c.getRow()];
    }
};

}; // namespace hex
#endif
