#pragma once

#include <iostream>
#include <string>

class ScalarConverter {
 public:
  static void convert(const char* literal);

 private:
  ScalarConverter();
  ScalarConverter(const ScalarConverter& other);
  ScalarConverter& operator=(const ScalarConverter& other);
  ~ScalarConverter();
};
