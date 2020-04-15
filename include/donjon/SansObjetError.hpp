#ifndef __SANSOBJETERROR_H__
#define __SANSOBJETERROR_H__

#include <stdexcept>
#include <string>

namespace donjon
{
    class SansObjetError: public std::runtime_error
    {
    public:
        SansObjetError(const std::string& message);

        virtual ~SansObjetError();
    };
} // namespace donjon

#endif // __SANSOBJETERROR_H__
