#include <iostream>

#include "Bureaucrat.h"

int main() {
  {
    try {
      Bureaucrat b("Alice", Bureaucrat::s_lowestGrade + 1);
      std::cout << b << '\n';
    } catch (std::exception &e) {
      std::cout << e.what() << '\n';
    }
  }

  {
    try {
      Bureaucrat b("Bob", Bureaucrat::s_highestGrade - 1);
      std::cout << b << '\n';
    } catch (std::exception &e) {
      std::cout << e.what() << '\n';
    }
  }

  {
    Bureaucrat b("John", Bureaucrat::s_highestGrade);
    std::cout << b << '\n';

    try {
      b.incrementGrade();
    } catch (std::exception &e) {
      std::cout << e.what() << '\n';
    }
  }

  {
    Bureaucrat b("Jane", Bureaucrat::s_lowestGrade);
    std::cout << b << '\n';

    try {
      b.decrementGrade();
    } catch (std::exception &e) {
      std::cout << e.what() << '\n';
    }
  }

  return 0;
}
