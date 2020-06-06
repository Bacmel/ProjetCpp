#ifndef __IITERATOR_HPP__
#define __IITERATOR_HPP__

#include <memory>

namespace hex
{
    template <typename T>
    struct IIterateur
    {
        virtual ~IIterateur() {}

        /**
         * @brief Indique la présence d'éléments ensuite
         *
         * @return true
         * @return false
         */
        virtual bool aSuite() = 0;

        /**
         * @brief Donne une copie de l'élément suivant
         *
         * @return T Une copie de l'élément suivant
         */
        virtual T suite() = 0;
    };

    template <typename T>
    using IIterator_S = std::shared_ptr<IIterateur<T>>;

    template <typename T>
    using IIterator_SC = std::shared_ptr<const IIterateur<T>>;
} // namespace hex

#endif // __IITERATOR_HPP__
