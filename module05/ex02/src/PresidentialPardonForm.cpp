
#include "PresidentialPardonForm.h"

#include <iostream>
#include <string>
#include <typeinfo>

#include "AForm.h"
#include "Bureaucrat.h"
#include "utils.h"

PresidentialPardonForm::PresidentialPardonForm()
    : AForm(typeid(*this).name(), s_gradeToSign, s_gradeToExecute),
      m_target("") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm(typeid(*this).name(), s_gradeToSign, s_gradeToExecute),
      m_target(target) {}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm& other)
    : AForm(other) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(
    const PresidentialPardonForm& other) {
  if (this != &other) {
    AForm::operator=(other);
  }

  return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {}

const std::string& PresidentialPardonForm::getTarget() const {
  return m_target;
}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const {
  AForm::execute(executor);

  std::cout << m_target
            << CYAN " has been pardoned by Zafod Beeblebrox\n" RESET;
}
