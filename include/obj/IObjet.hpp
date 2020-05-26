#ifndef IOBJET_HPP
#define IOBJET_HPP

#include <memory>
#include "hex/Coordonnees.hpp"

namespace donjon
{
    class IDonjon;
}

namespace obj
{

    class IObjet
    {
    public:
        virtual ~IObjet() {}

        /**
         * @brief Utilise l'objet sur un personnage.
         *
         * @param donjon Le donjon.
         * @param cible La cible de l'utilisation.
         *
         * @throw invalid_argument Quand la cible n'est pas valide.
         * @throw logic_error Quand l'objet ne peut être utilisé.
         */
        virtual void utiliser(donjon::IDonjon& donjon,
                              const hex::Coordonnees& origine,
                              const hex::Coordonnees& cible) = 0;
    };

    using IObjet_S = std::shared_ptr<IObjet>;
    using IObjet_SC = std::shared_ptr<const IObjet>;

}; // namespace obj

#endif
