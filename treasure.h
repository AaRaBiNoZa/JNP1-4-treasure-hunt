#ifndef TREASURE_H
#define TREASURE_H

#include <concepts>

template <std::integral ValueType, bool IsTrapped>
class Treasure
{
private:
    ValueType loot;

public:
    constexpr static bool isTrapped = IsTrapped;

    constexpr Treasure(ValueType value) : loot(value) {}

    constexpr ValueType evaluate() const { return loot; }

    constexpr ValueType getLoot()
    {
        ValueType tmp = loot;
        loot = 0;

        return tmp;
    }
};

template <std::integral ValueType>
using SafeTreasure = Treasure<ValueType, false>;

template <std::integral ValueType>
using TrappedTreasure = Treasure<ValueType, true>;

#endif