#include "ShrubberyCreationForm.h"

#include <fstream>
#include <string>
#include <typeinfo>

#include "AForm.h"
#include "Bureaucrat.h"

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm(typeid(*this).name(), s_gradeToSign, s_gradeToExecute),
      m_target("") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm(typeid(*this).name(), s_gradeToSign, s_gradeToExecute),
      m_target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(
    const ShrubberyCreationForm& other) {
  if (this != &other) {
    AForm::operator=(other);
  }

  return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

const std::string& ShrubberyCreationForm::getTarget() const { return m_target; }

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
  AForm::execute(executor);

  std::string filename = m_target + "_shrubbery";
  std::ofstream outfile(filename.c_str());

  outfile << "      /\\      \n"
             "     /\\*\\     \n"
             "    /\\O\\*\\    \n"
             "   /*/\\/\\/\\   \n"
             "  /\\O\\/\\*\\/\\  \n"
             " /\\*\\/\\*\\/\\/\\ \n"
             "/\\O\\/\\/*/\\/O/\\\n"
             "      ||      \n"
             "      ||      \n"
             "      ||      \n";
}
