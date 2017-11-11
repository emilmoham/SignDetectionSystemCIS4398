#ifndef __COLORS_H_
#define __COLORS_H_

/// Wrapped in namespace for ease-of-use (compare this to using an enum class as a bit vector...)
namespace Color
{
    /// Bit vector of color types detected by the program. Used to narrow down
    /// potential signs during preprocessing/analyzing stages
    enum Value
    {
        None   = 0x00,
        White  = 0x01,
        Yellow = 0x02,
        Red    = 0x04,
        Green  = 0x08,
        Blue   = 0x10
    };
}

#endif //__COLORS_H_

