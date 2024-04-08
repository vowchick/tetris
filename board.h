#pragma once
#include <cstdint>
#include <iostream>
#include <optional>

class Board {
public:
  Board(int _n, int _m) : n(_n), m(_m){}

  void print() const {
    std::cout << "Printing Board\n";
  }

  bool update(uint64_t secs_passed, std::optional<char> key_pressed) {
    if (key_pressed) {
      react_to_pressed_key(key_pressed.value());
    }
    return true;
  }

private:
  void react_to_pressed_key(char key) {
    std::cout << "Reacting to key: " << key << std::endl;
    return;
  };
  
private:
  const int n;
  const int m;
};