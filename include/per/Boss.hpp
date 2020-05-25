#ifndef BOSS_HPP
#define BOSS_HPP

#include <memory>
#include <vector>
#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "per/APersonnage.hpp"

namespace per
{

    class Boss : public APersonnage
    {
    protected:
        /** Liste des objets detenue par le Boss */
        std::vector<obj::IObjet_S> m_sac;

    public:
        /**
         * @brief Construit un Boss avec son équipement
         *
         * @param pvMax La santé maximale.
         * @param coor Les coordonnées initiales.
         * @param sac L'équipement.
         */
        Boss(size_t pvMax, hex::Coordonnees coor, std::vector<obj::IObjet_S> sac);

        Boss(const Boss& autre) = default;
        Boss(Boss&& autre) = default;
        Boss& operator=(const Boss& autre) = default;
        Boss& operator=(Boss& autre) = default;
        ~Boss() {}

        /**
         * @brief Obtient l'inventaire.
         *
         * @return const std::vector<obj::IObjet_S>& L'inventaire.
         */
        inline const std::vector<obj::IObjet_S>& getInventaire() const { return m_sac; }

        /**
         * @brief Ajoute un objet à l'inventaire.
         *
         * NOTE: Un nullptr ne lève pas d'exception mais n'est pas ajouté à
         * l'inventaire.
         *
         * @param objet L'objet à ajouter.
         */
        void prendre(obj::IObjet_S objet);

        /**
         * @brief Retire un objet de l'inventaire et le retourne.
         *
         * @param indice L'indice de l'objet dans l'inventaire.
         * @return obj::IObjet_S L'objet retiré.
         * @throw std::out_of_range Quand l'indice est hors de l'inventaire.
         */
        obj::IObjet_S lacher(size_t indice);
    };
}; // namespace per

#endif // BOSS_HPP
