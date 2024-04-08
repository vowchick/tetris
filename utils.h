#pragma once
#include <type_traits>
#include <vector>

namespace utils {

  template<typename E>
  constexpr auto to_underlying(E e) noexcept {
      return static_cast<std::underlying_type_t<E>>(e);
  }

  enum class Keys {
    Up,
    Down,
    Left,
    Right
  };

  enum class Shape {
    L,
    T,
    I
  };

  enum class RotationKey {
    Up,
    Down,
  };

  enum class MoveKey {
    Left,
    Right,
  };

  struct Coordinates {
    Coordinates() = default;
    Coordinates(int _x, int _y): x(_x), y(_y) {
    }
    int x = 0;
    int y = 0;
  };

  Coordinates operator+(const Coordinates &lhs, const Coordinates& rhs) {
    return Coordinates(lhs.x + rhs.x, lhs.y + rhs.y);
  }
  Coordinates operator-(const Coordinates &lhs, const Coordinates& rhs) {
    return Coordinates(lhs.x - rhs.x, lhs.y - rhs.y);
  }

  auto x_cmp = [](const Coordinates& lhs, const Coordinates& rhs) {
      return lhs.x < rhs.x;
    };
};