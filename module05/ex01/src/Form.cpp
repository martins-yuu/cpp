#include "Form.h"

#include <ios>
#include <typeinfo>

#include "Bureaucrat.h"
#include "utils.h"

const char* Form::GradeTooHighException::what() const throw() {
  return "Grade is too high";
}

const char* Form::GradeTooLowException::what() const throw() {
  return "Grade is too low";
}

Form::Form()
    : m_name(""),
      m_gradeToSign(s_lowestGrade),
      m_gradeToExecute(s_lowestGrade),
      m_isSigned(false) {}

Form::Form(const char* name, int gradeToSign, int gradeToExecute)
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

Form::Form(const Form& other)
    : m_name(other.m_name),
      m_gradeToSign(other.m_gradeToSign),
      m_gradeToExecute(other.m_gradeToExecute),
      m_isSigned(other.m_isSigned) {}

Form& Form::operator=(const Form& other) {
  if (this != &other) {
    m_name = other.m_name;
    m_isSigned = other.m_isSigned;
  }

  return *this;
}

Form::~Form() {}

const char* Form::getName() const { return m_name; }

int Form::getGradeToSign() const { return m_gradeToSign; }

int Form::getGradeToExecute() const { return m_gradeToExecute; }

bool Form::isSigned() const { return m_isSigned; }

void Form::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > m_gradeToSign) {
    throw GradeTooLowException();
  }

  m_isSigned = true;
}

std::ostream& operator<<(std::ostream& os, const Form& form) {
  os << typeid(form).name() << '(';
  os << YELLOW "name: " RESET << form.getName() << ", ";
  os << YELLOW "gradeToSign: " RESET << form.getGradeToSign() << ", ";
  os << YELLOW "gradeToExecute: " RESET << form.getGradeToExecute() << ", ";
  os << YELLOW "isSigned: " RESET << std::boolalpha << form.isSigned();
  os << ')';
  return os;
}
