#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H

#include "member.h"
#include "treasure.h"

#include <concepts>
#include <utility>

namespace
{

  template <class T>
  concept treasure = requires(T t)
  {
    {
      Treasure(t)
      }
      -> std::same_as<T>;
  };

  template <class T>
  concept adventurer = requires(T t)
  {
    typename T::strength_t;
    {[]() constexpr {return std::remove_reference<T>::type::isArmed;
  }
  ()
}; // namespace
std::is_convertible<decltype(T::isArmed), bool>();
{
  t.pay()
  }
  -> std::integral;
{Treasure<int, false>(t.pay())};
}
;

template <class T>
concept EncounterSide = treasure<T> || adventurer<T>;

template <typename T>
concept _encounter = requires(T t)
{
  EncounterSide<decltype(t.first)>;
  EncounterSide<decltype(t.second)>;
};
}
; // end namespace

template <EncounterSide sideA, EncounterSide sideB>
using Encounter = std::pair<sideA &, sideB &>;

template <treasure T, adventurer A>
constexpr void run(Encounter<A, T> encounter)
{
  if constexpr (!(T::isTrapped && !A::isArmed))
    encounter.first.loot(std::move(encounter.second));
}

template <treasure T, adventurer A>
constexpr void run(Encounter<T, A> encounter)
{
  if constexpr (!(T::isTrapped && !A::isArmed))
    encounter.second.loot(std::move(encounter.first));
}

template <adventurer A1, adventurer A2>
constexpr void run(Encounter<A1, A2> encounter)
{
  if (A1::isArmed and !A2::isArmed)
  {
    encounter.first.addWealth(encounter.second.pay());
  }
  else if (!A1::isArmed and A2::isArmed)
  {
    encounter.second.addWealth(encounter.first.pay());
  }
  else if constexpr (A1::isArmed and A2::isArmed)
  {
    if (encounter.first.getStrength() > encounter.second.getStrength())
      encounter.first.addWealth(encounter.second.pay());
    else if (encounter.first.getStrength() < encounter.second.getStrength())
      encounter.second.addWealth(encounter.first.pay());
  }
}

template <treasure T1, treasure T2>
constexpr void run(Encounter<T1, T2> encounter) = delete;

template <_encounter E1, _encounter... E2>
constexpr void expedition(E1 first, E2... rest)
{
  run(first);

  if constexpr (sizeof...(rest) > 0)
    expedition(rest...);
}

#endif