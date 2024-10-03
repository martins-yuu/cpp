#include <cstddef>
#include <iostream>

#include "AForm.h"
#include "Bureaucrat.h"
#include "PresidentialPardonForm.h"
#include "RobotomyRequestForm.h"
#include "ShrubberyCreationForm.h"

int main() {
  AForm *forms[] = {
      new ShrubberyCreationForm("home"),
      new ShrubberyCreationForm("campus"),
      new RobotomyRequestForm("John"),
      new RobotomyRequestForm("Jane"),
      new PresidentialPardonForm("Charlie"),
      new PresidentialPardonForm("David"),
  };
  std::size_t formCount = sizeof(forms) / sizeof(forms[0]);

  for (std::size_t i = 0; i < formCount; ++i) {
    AForm *f = forms[i];

    Bureaucrat b("Alice", f->getGradeToSign());

    b.executeForm(*f);
    b.signForm(*f);
    b.executeForm(*f);

    {
      Bureaucrat b("Bob", f->getGradeToExecute());

      b.executeForm(*f);
    }

    std::cout << '\n';

    delete f;
  }
}
