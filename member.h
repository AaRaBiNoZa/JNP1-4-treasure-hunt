#ifndef MEMBER_H
#define MEMBER_H

#include "treasure.h"
#include <concepts>
#include <cstdint>

namespace {

// Concepts to ensure that T is a valid type for a treasure
template <typename T, bool b>
concept treasureValueTypeSpecific = requires(T t) {
  typename Treasure<T, b>;
};

template <typename T>
concept treasureValueType =
    treasureValueTypeSpecific<T, true> || treasureValueTypeSpecific<T, false>;

constexpr uint32_t fib(uint32_t n) {
  uint32_t last = 1;
  uint32_t previous = 0;
  if (n == 0) {
    return previous;
  } else if (n == 1) {
    return last;
  }
  uint32_t temp;
  for (uint32_t i = 1; i < n; i++) {
    temp = last;
    last += previous;
    previous = temp;
  }
  return last;
}

} // namespace

template <treasureValueType ValueType, bool IsArmed> class Adventurer {};

// Adventurer<ValueType, false> declaration

template <treasureValueType ValueType> class Adventurer<ValueType, false> {
public:
  using strength_t = uint32_t;
  constexpr static bool isArmed = false;
  constexpr Adventurer() = default;
  constexpr void loot(Treasure<ValueType, false> &&treasure);
  constexpr ValueType pay();
  constexpr void addWealth(ValueType x);

private:
  ValueType wealth = 0;
};

template <treasureValueType ValueType>
constexpr void
Adventurer<ValueType, false>::loot(Treasure<ValueType, false> &&treasure) {
  wealth += treasure.getLoot();
};

template <treasureValueType ValueType>
constexpr ValueType Adventurer<ValueType, false>::pay() {
  ValueType temp = this->wealth;
  this->wealth = 0;
  return temp;
}

template <treasureValueType ValueType>
constexpr void Adventurer<ValueType, false>::addWealth(ValueType x) {
  wealth += x;
}

// end of Adventurer<ValueType, false> function definition

// Adventurer<ValueType, true> declaration

template <treasureValueType ValueType> class Adventurer<ValueType, true> {
public:
  using strength_t = uint32_t;
  strength_t strength;
  constexpr static bool isArmed = true;
  constexpr explicit Adventurer(strength_t _strength) : strength(_strength){};
  constexpr void loot(Treasure<ValueType, true> &&treasure);
  constexpr void loot(Treasure<ValueType, false> &&treasure);
  constexpr strength_t getStrength() const;
  constexpr ValueType pay();
  constexpr void addWealth(ValueType x);

private:
  ValueType wealth = 0;
};

template <treasureValueType ValueType>
constexpr void
Adventurer<ValueType, true>::loot(Treasure<ValueType, false> &&treasure) {
  wealth += treasure.getLoot();
}

template <treasureValueType ValueType>
constexpr void
Adventurer<ValueType, true>::loot(Treasure<ValueType, true> &&treasure) {
  if (strength == 0) {
    return;
  } else {
    wealth += treasure.getLoot();
    strength /= 2;
  }
}

template <treasureValueType ValueType>
constexpr typename Adventurer<ValueType, true>::strength_t
Adventurer<ValueType, true>::getStrength() const {
  return strength;
}

template <treasureValueType ValueType>
constexpr ValueType Adventurer<ValueType, true>::pay() {
  ValueType temp = this->wealth;
  this->wealth = 0;
  return temp;
}

template <treasureValueType ValueType>
constexpr void Adventurer<ValueType, true>::addWealth(ValueType x) {
  wealth += x;
}

// end of Adventurer<ValueType, true> function definition

template <treasureValueType ValueType>
using Explorer = Adventurer<ValueType, false>;

template <treasureValueType ValueType, std::size_t CompletedExpeditions>
requires(CompletedExpeditions < 25) class Veteran {
public:
  using strength_t = uint32_t;
  strength_t strength;
  constexpr Veteran() : strength(fib(CompletedExpeditions)){};
  constexpr void loot(Treasure<ValueType, false> &&treasure);
  constexpr void loot(Treasure<ValueType, true> &&treasure);
  constexpr ValueType pay();
  static constexpr bool isArmed = true;
  constexpr void addWealth(ValueType x);
  constexpr strength_t getStrength() const;

private:
  ValueType wealth = 0;
};

template <treasureValueType ValueType, std::size_t CompletedExpeditions>
requires(CompletedExpeditions <
         25) constexpr void Veteran<ValueType, CompletedExpeditions>::
    loot(Treasure<ValueType, true> &&treasure) {
  if (strength > 0) {
    wealth += treasure.getLoot();
  }
}

template <treasureValueType ValueType, std::size_t CompletedExpeditions>
requires(CompletedExpeditions <
         25) constexpr void Veteran<ValueType, CompletedExpeditions>::
    loot(Treasure<ValueType, false> &&treasure) {
  wealth += treasure.getLoot();
}

template <treasureValueType ValueType, std::size_t CompletedExpeditions>
requires(CompletedExpeditions < 25) constexpr ValueType
    Veteran<ValueType, CompletedExpeditions>::pay() {
  ValueType temp = this->wealth;
  this->wealth = 0;
  return temp;
}

template <treasureValueType ValueType, std::size_t CompletedExpeditions>
requires(CompletedExpeditions < 25) constexpr void Veteran<
    ValueType, CompletedExpeditions>::addWealth(ValueType x) {
  wealth += x;
}

template <treasureValueType ValueType, std::size_t CompletedExpeditions>
requires(CompletedExpeditions < 25) constexpr
    typename Veteran<ValueType, CompletedExpeditions>::strength_t
    Veteran<ValueType, CompletedExpeditions>::getStrength() const {
  return strength;
}

#endif
