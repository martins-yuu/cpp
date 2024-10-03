#include "AForm.h"
#include "Bureaucrat.h"
#include "Intern.h"
#include "PresidentialPardonForm.h"
#include "RobotomyRequestForm.h"
#include "ShrubberyCreationForm.h"

int main() {
  for (Intern::FormType::Type type = Intern::FormType::begin;
       type != Intern::FormType::end; type = Intern::FormType::next(type)) {
    Intern intern;
    AForm* form = intern.makeForm(Intern::FormType::toString(type), "target");

    form->beSigned(Bureaucrat("signer", form->getGradeToSign()));
    form->execute(Bureaucrat("executor", form->getGradeToExecute()));

    delete form;
  }
}
