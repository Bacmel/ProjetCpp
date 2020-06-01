#ifndef __FINPARTIE_H__
#define __FINPARTIE_H__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class FinPartie : public IEtat
    {
    protected:
        /* indice de l'equipe en jeu. */
        size_t m_indiceGagnant;

    public:
        FinPartie(size_t indice);

        /**
         * @brief Operation de l'etat courant sur la partie.
         *
         * @param partie la Partie.
         */
        void operation(Partie& partie);

        void afficher() const override;

        inline size_t getEquipeCourante() const override { return m_indiceGagnant; }

        per::APersonnage_SC getPersoSelect() const override;

        obj::IObjet_SC getObjetSelect() const override;

        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;

        void operation(Partie& partie, size_t objet) override;
    };
} // namespace partie::etat

#endif //__FINPARTIE_H__
