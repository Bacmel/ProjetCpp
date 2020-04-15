#ifndef IOBJET_HPP
#define IOBJET_HPP

#include <memory>
#include "donjon/IDonjon.hpp"
#include "hex/Coordonnees.hpp"
#include "per/IPersonnage.hpp"

namespace obj
{

    class IObjet
    {
    public:
        typedef std::shared_ptr<IObjet> Ptr;
        typedef std::shared_ptr<const IObjet> ConstPtr;

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
        virtual void utiliser(donjon::IDonjon& donjon, const hex::Coordonnees& cible) = 0;
    };

}; // namespace obj

#endif
