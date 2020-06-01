#ifndef __PERSOACTIF_H__
#define __PERSOACTIF_H__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"
#include "per/APersonnage.hpp"

namespace partie::etat
{
    class PersoActif : public IEtat
    {
    protected:
        /* indice de l'equipe en jeu. */
        size_t m_indiceEquipe;
        /* personnage actif. */
        per::APersonnage_S m_personnage;

    public:
        PersoActif(size_t indice, per::APersonnage_S personnage);

        /**
         * @brief Operation de l'etat courant sur la partie.
         *
         * @param partie la Partie.
         * @param coordonnees les coordonnees selectionnees.
         * @param objet l'objet selectionne.
         */
        void operation(Partie& partie, const hex::Coordonnees& coordonnees);
        void operation(Partie& partie, obj::IObjet_S objet);

        /**
         * @brief Affiche l'état courant.
         */
        void afficher() const;
    };
} // namespace partie::etat

#endif //__PERSOACTIF_H__