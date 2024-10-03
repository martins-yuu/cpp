#pragma once

#include <string>

#include "AForm.h"

class Bureaucrat;

class RobotomyRequestForm : public AForm {
 public:
  RobotomyRequestForm();
  RobotomyRequestForm(const std::string& target);
  RobotomyRequestForm(const RobotomyRequestForm& other);
  RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
  ~RobotomyRequestForm();

  const std::string& getTarget() const;

  void execute(const Bureaucrat& executor) const;

  static const int s_gradeToSign = 72;
  static const int s_gradeToExecute = 45;

 private:
  std::string m_target;
};
