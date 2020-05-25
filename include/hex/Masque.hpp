#ifndef __IMASQUE_H__
#define __IMASQUE_H__

#include "hex/CarteHexagone.hpp"

namespace hex
{
    class Masque : public CarteHexagone<bool>
    {
    public:
        explicit Masque(size_t rayon);

        Masque(const Masque& autre) = default;
        Masque(Masque&& autre) = default;
        Masque& operator=(const Masque& autre) = default;
        Masque& operator=(Masque&& autre) = default;
        virtual ~Masque();

        virtual Masque operator||(const Masque& autre) const;

        virtual Masque operator&&(const Masque& autre) const;

        virtual Masque operator!() const;
    };
} // namespace hex

#endif // __IMASQUE_H__
