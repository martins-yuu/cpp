#include "Intern.h"

#include <cstring>
#include <iostream>

#include "Bureaucrat.h"
#include "PresidentialPardonForm.h"
#include "RobotomyRequestForm.h"
#include "ShrubberyCreationForm.h"

Intern::FormType::Type Intern::FormType::next(FormType::Type type) {
  return static_cast<FormType::Type>(type + 1);
}

const char* Intern::FormType::toString(FormType::Type type) {
  if (type < FormType::begin || type >= FormType::end) {
    return NULL;
  }

  return s_names[type];
}

Intern::FormType::Type Intern::FormType::fromString(const char* name) {
  for (FormType::Type type = FormType::begin; type != FormType::end;
       type = FormType::next(type)) {
    if (std::strncmp(name, toString(type), std::strlen(toString(type) + 1)) ==
        0) {
      return type;
    }
  }
  return FormType::invalid;
}

const char* const Intern::FormType::s_names[] = {
    NULL,
    "shrubbery creation",
    "robotomy request",
    "presidential pardon",
};

Intern::Intern() {}

Intern::Intern(const Intern&) {}

Intern::~Intern() {}

Intern& Intern::operator=(Intern const&) { return *this; }

AForm* Intern::makeForm(const char* formName, const std::string& target) {
  FormType::Type formType = FormType::fromString(formName);

  if (!formType) {
    std::cout << "Intern cannot create " << formName << '\n';
    return NULL;
  }

  std::cout << "Intern creates " << formName << '\n';

  switch (formType) {
    case FormType::shrubberyCreation:
      return new ShrubberyCreationForm(target);
    case FormType::robotomyRequest:
      return new RobotomyRequestForm(target);
    case FormType::presidentialPardon:
      return new PresidentialPardonForm(target);
    default:
      return NULL;
  }
}
