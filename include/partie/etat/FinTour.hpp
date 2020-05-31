#ifndef __FINTOUR_H__
#define __FINTOUR_H__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class FinTour : public IEtat
    {
    protected:
        /* indice de l'equipe en jeu. */
        size_t m_indiceEquipe;

    public:
        FinTour(size_t indice);

        /**
         * @brief Operation de l'etat courant sur la partie.
         *
         * @param partie la Partie.
         * @param coordonnees les coordonnees selectionnees.
         * @param objet l'objet selectionne.
         */
        void operation(Partie& partie, const hex::Coordonnees& coordonnees);
        void operation(Partie& partie, obj::IObjet_S objet);
    private:
        void operation(Partie& partie);
    };
} // namespace partie::etat

#endif //__FINTOUR_H__