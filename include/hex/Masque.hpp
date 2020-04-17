#ifndef __IMASQUE_H__
#define __IMASQUE_H__

#include "hex/CarteHexagone.hpp"

namespace hex
{
    class Masque : public CarteHexagone<bool>
    {
    public:
        Masque(size_t m_rayon);

        virtual ~Masque();

        virtual Masque operator||(const Masque& autre) const;

        virtual Masque operator&&(const Masque& autre) const;

        virtual Masque operator!() const;
    };
} // namespace hex

#endif // __IMASQUE_H__
