#include "Bureaucrat.h"

#include <iostream>
#include <typeinfo>

#include "AForm.h"
#include "utils.h"

const char* Bureaucrat::GradeTooHighException::what() const throw() {
  return "Grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
  return "Grade is too low";
}

Bureaucrat::Bureaucrat() : m_name(""), m_grade(s_lowestGrade) {}

Bureaucrat::Bureaucrat(const char* name, int grade)
    : m_name(name), m_grade(grade) {
  if (grade < s_highestGrade) {
    throw GradeTooHighException();
  } else if (grade > s_lowestGrade) {
    throw GradeTooLowException();
  }
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
    : m_name(other.m_name), m_grade(other.m_grade) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
  if (this != &other) {
    m_name = other.m_name;
    m_grade = other.m_grade;
  }

  return *this;
}

Bureaucrat::~Bureaucrat() {}

const char* Bureaucrat::getName() const { return m_name; }

int Bureaucrat::getGrade() const { return m_grade; }

void Bureaucrat::incrementGrade() {
  if (m_grade - 1 < s_highestGrade) {
    throw GradeTooHighException();
  }

  m_grade--;
}

void Bureaucrat::decrementGrade() {
  if (m_grade + 1 > s_lowestGrade) {
    throw GradeTooLowException();
  }

  m_grade++;
}

void Bureaucrat::signForm(AForm& form) const {
  try {
    form.beSigned(*this);
    std::cout << *this << GREEN " signed " RESET << form << '\n';
  } catch (const AForm::GradeTooLowException& e) {
    std::cout << *this << RED " couldn't sign " RESET << form
              << MAGENTA " because " RESET << e.what() << '\n';
  }
}

void Bureaucrat::executeForm(const AForm& form) const {
  try {
    form.execute(*this);
    std::cout << *this << GREEN " executed " RESET << form << '\n';
  } catch (const std::exception& e) {
    std::cout << *this << RED " couldn't execute " RESET << form
              << MAGENTA " because " RESET << e.what() << '\n';
  }
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat) {
  os << typeid(bureaucrat).name() << '(';
  os << YELLOW "name: " RESET << bureaucrat.getName() << ", ";
  os << YELLOW "grade: " RESET << bureaucrat.getGrade();
  os << ')';
  return os;
}
