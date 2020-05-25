#ifndef __IITERATOR_H__
#define __IITERATOR_H__

#include <memory>

namespace hex
{

    template <typename T>
    struct IIterator
    {
        virtual ~IIterator() {}

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

    template<typename T>
    using IIterator_S = std::shared_ptr<IIterator<T>>;

    template<typename T>
    using IIterator_SC = std::shared_ptr<const IIterator<T>>;
} // namespace hex

#endif // __IITERATOR_H__
