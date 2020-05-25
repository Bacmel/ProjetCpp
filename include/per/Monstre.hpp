#ifndef MONSTRE_HPP
#define MONSTRE_HPP

#include <memory>
#include <vector>
#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "per/APersonnage.hpp"

namespace per
{

    class Monstre : public APersonnage
    {
    protected:
        /** Arme du monstre */
        obj::IObjet_S m_arme;

    public:
        Monstre(size_t pvMax, hex::Coordonnees coor, obj::IObjet_S arme);

        Monstre(const Monstre& autre) = default;
        Monstre(Monstre&& autre) = default;
        Monstre& operator=(const Monstre& autre) = default;
        Monstre& operator=(Monstre&& autre) = default;
        ~Monstre() {}

        /**
         * @brief Obtient l'arme
         *
         * @return obj::IObjet_SC Un pointeur constant vers l'arme.
         */
        inline obj::IObjet_SC getArme() const { return m_arme; }
    };
}; // namespace per

#endif // MONSTRE_HPP
