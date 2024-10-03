#pragma once

#include <iostream>
#include <string>

#include "Bureaucrat.h"

class Intern {
 public:
  struct FormType {
   public:
    enum Type {
      invalid = 0,
      shrubberyCreation,
      robotomyRequest,
      presidentialPardon,
      count,
      begin = invalid + 1,
      end = count
    };

    static Type next(Type type);
    static const char* toString(Type type);
    static Type fromString(const char* name);

   private:
    static const char* const s_names[];
  };

  Intern();
  Intern(const Intern& other);
  Intern& operator=(const Intern& other);
  ~Intern();

  AForm* makeForm(const char* formName, const std::string& target);
};
