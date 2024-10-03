#pragma once

#include <string>

#include "AForm.h"

class Bureaucrat;

class ShrubberyCreationForm : public AForm {
 public:
  ShrubberyCreationForm();
  ShrubberyCreationForm(const std::string& target);
  ShrubberyCreationForm(const ShrubberyCreationForm& other);
  ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
  ~ShrubberyCreationForm();

  const std::string& getTarget() const;

  void execute(const Bureaucrat& executor) const;

  static const int s_gradeToSign = 145;
  static const int s_gradeToExecute = 137;

 private:
  std::string m_target;
};
