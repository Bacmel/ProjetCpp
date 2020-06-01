#ifndef __Initial_H__
#define __Initial_H__

#include "partie/etat/IEtat.hpp"
#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"

namespace partie::etat
{
    class Initial : public IEtat
    {
    protected:
        /* indice de L'Equipe en jeu. */
        size_t m_indiceEquipe;        
    public:
        Initial(size_t indice);

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
        inline void afficher() const;
    };
} // namespace partie::etat

#endif //__Initial_H__