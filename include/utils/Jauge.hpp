#ifndef __JAUGE_HPP__
#define __JAUGE_HPP__

#include <cstddef>

namespace utils
{
    class Jauge
    {
    protected:
        /** Valeur maximal et valeur actuelle de la jauge. */
        size_t m_valMax;
        size_t m_val;

    public:
        Jauge(size_t valMax) : m_valMax(valMax), m_val(valMax){};

        /**
         * @brief Modifie la valeur actuelle.
         *
         * @param valeur La valeur à ajouter. Elle peut être négative.
         * @throw err::JaugeErreur Si m_val + valeur < 0
         */
        void ajouterValeur(int valeur);

        /**
         * @brief Modifie la valeur maximale
         *
         * @param valeur La valeur à ajouter. Elle peut être négative.
         * @throw err::JaugeErreur Si m_val + valeur < 0
         */
        void ajouterValeurMax(int valeur);

        /**
         * @brief Obtient la valeur actuelle.
         *
         * @return size_t la valeur actuelle.
         */
        inline size_t getVal() const { return m_val; }

        /**
         * @brief Obtient la valeur maximale.
         *
         * @return size_t la valeur maximale.
         */
        inline size_t getValMax() const { return m_valMax; }

        /**
         * @brief Remplie la jauge.
         */
        void remplir();

        /**
         * @brief Vide la jauge.
         */
        void vider();
    };
} // namespace utils

#endif // __JAUGE_HPP__