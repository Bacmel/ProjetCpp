#ifndef __IACTUALISABLE_HPP__
#define __IACTUALISABLE_HPP__

namespace utils
{
    class IActualisable
    {
    public:
        /**
         * @brief Effectue la mise a jour de l'element.
         */
        virtual void actualiser() = 0;
    };
} // namespace utils

#endif // __IACTUALISABLE_HPP__