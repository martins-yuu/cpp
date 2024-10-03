#include "AForm.h"

#include <ios>
#include <typeinfo>

#include "Bureaucrat.h"
#include "utils.h"

const char* AForm::GradeTooHighException::what() const throw() {
  return "Grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw() {
  return "Grade is too low";
}

const char* AForm::NotSignedException::what() const throw() {
  return "Form is not signed";
}

AForm::AForm()
    : m_name(""),
      m_gradeToSign(s_lowestGrade),
      m_gradeToExecute(s_lowestGrade),
      m_isSigned(false) {}

AForm::AForm(const char* name, int gradeToSign, int gradeToExecute)
    : m_name(name),
      m_gradeToSign(gradeToSign),
      m_gradeToExecute(gradeToExecute),
      m_isSigned(false) {
  if (gradeToSign < s_highestGrade || gradeToExecute < s_highestGrade) {
    throw GradeTooHighException();
  } else if (gradeToSign > s_lowestGrade || gradeToExecute > s_lowestGrade) {
    throw GradeTooLowException();
  }
}

AForm::AForm(const AForm& other)
    : m_name(other.m_name),
      m_gradeToSign(other.m_gradeToSign),
      m_gradeToExecute(other.m_gradeToExecute),
      m_isSigned(other.m_isSigned) {}

AForm& AForm::operator=(const AForm& other) {
  if (this != &other) {
    m_name = other.m_name;
    m_isSigned = other.m_isSigned;
  }

  return *this;
}

AForm::~AForm() {}

const char* AForm::getName() const { return m_name; }

int AForm::getGradeToSign() const { return m_gradeToSign; }

int AForm::getGradeToExecute() const { return m_gradeToExecute; }

bool AForm::isSigned() const { return m_isSigned; }

void AForm::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > m_gradeToSign) {
    throw GradeTooLowException();
  }

  m_isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const {
  if (!m_isSigned) {
    throw NotSignedException();
  }

  if (executor.getGrade() > m_gradeToExecute) {
    throw GradeTooLowException();
  }
}

std::ostream& operator<<(std::ostream& os, const AForm& form) {
  os << typeid(form).name() << '(';
  os << YELLOW "name: " RESET << form.getName() << ", ";
  os << YELLOW "gradeToSign: " RESET << form.getGradeToSign() << ", ";
  os << YELLOW "gradeToExecute: " RESET << form.getGradeToExecute() << ", ";
  os << YELLOW "isSigned: " RESET << std::boolalpha << form.isSigned();
  os << ')';
  return os;
}
