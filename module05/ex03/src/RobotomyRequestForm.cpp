#include "RobotomyRequestForm.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <typeinfo>

#include "AForm.h"
#include "Bureaucrat.h"
#include "utils.h"

RobotomyRequestForm::RobotomyRequestForm()
    : AForm(typeid(*this).name(), s_gradeToSign, s_gradeToExecute),
      m_target("") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm(typeid(*this).name(), s_gradeToSign, s_gradeToExecute),
      m_target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
    : AForm(other) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(
    const RobotomyRequestForm& other) {
  if (this != &other) {
    AForm::operator=(other);
  }

  return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

const std::string& RobotomyRequestForm::getTarget() const { return m_target; }

void RobotomyRequestForm::execute(const Bureaucrat& executor) const {
  AForm::execute(executor);

  std::cout << "*drilling noises*\n";
  if (std::srand(std::time(NULL)), std::rand() % 2 == 0) {
    std::cout << m_target << CYAN " has been robotomized successfully\n" RESET;
  } else {
    std::cout << m_target << BLUE " robotomization failed\n" RESET;
  }
}
