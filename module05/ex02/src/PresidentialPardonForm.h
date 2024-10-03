#pragma once

#include <string>

#include "AForm.h"

class Bureaucrat;

class PresidentialPardonForm : public AForm {
 public:
  PresidentialPardonForm();
  PresidentialPardonForm(const std::string& target);
  PresidentialPardonForm(const PresidentialPardonForm& other);
  PresidentialPardonForm& operator=(const PresidentialPardonForm& other);
  ~PresidentialPardonForm();

  const std::string& getTarget() const;

  void execute(const Bureaucrat& executor) const;

  static const int s_gradeToSign = 25;
  static const int s_gradeToExecute = 5;

 private:
  std::string m_target;
};
