#pragma once

#include <exception>
#include <ostream>

class AForm;

class Bureaucrat {
 public:
  class GradeTooHighException : public std::exception {
   public:
    const char* what() const throw();
  };

  class GradeTooLowException : public std::exception {
   public:
    const char* what() const throw();
  };

  Bureaucrat();
  Bureaucrat(const char* name, int grade);
  Bureaucrat(const Bureaucrat& other);
  Bureaucrat& operator=(const Bureaucrat& other);
  ~Bureaucrat();

  const char* getName() const;
  int getGrade() const;

  void incrementGrade();
  void decrementGrade();
  void signForm(AForm& form) const;
  void executeForm(const AForm& form) const;

  static const int s_highestGrade = 1;
  static const int s_lowestGrade = 150;

 private:
  const char* m_name;
  int m_grade;
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);
