#pragma once

#include <exception>
#include <ostream>

class Bureaucrat;

class Form {
 public:
  class GradeTooHighException : public std::exception {
   public:
    const char* what() const throw();
  };

  class GradeTooLowException : public std::exception {
   public:
    const char* what() const throw();
  };

  Form();
  Form(const char* name, int gradeToSign, int gradeToExecute);
  Form(const Form& other);
  Form& operator=(const Form& other);
  ~Form();

  const char* getName() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;
  bool isSigned() const;

  void beSigned(const Bureaucrat& bureaucrat);

  static const int s_highestGrade = 1;
  static const int s_lowestGrade = 150;

 private:
  const char* m_name;
  const int m_gradeToSign;
  const int m_gradeToExecute;
  bool m_isSigned;
};

std::ostream& operator<<(std::ostream& os, const Form& form);
