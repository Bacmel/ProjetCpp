#ifndef __IEtat_H__
#define __IEtat_H__

#include <memory>
#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"

namespace partie
{
    class Partie;
    namespace etat
    {
        class IEtat
        {
        public:
            virtual ~IEtat() {}

            /**
             * @brief Operation de l'etat courant sur la partie.
             *
             * @param partie la Partie.
             * @param coordonnees les coordonnees selectionnees.
             * @param objet l'objet selectionne.
             */
            virtual void operation(Partie& partie, const hex::Coordonnees& coordonnees) = 0;
            virtual void operation(Partie& partie, obj::IObjet_S objet) = 0;
        };

        using IEtat_S = std::shared_ptr<IEtat>;
        using IEtat_SC = std::shared_ptr<const IEtat>;
    } // namespace etat
} // namespace partie

#endif //__IEtat_H__
