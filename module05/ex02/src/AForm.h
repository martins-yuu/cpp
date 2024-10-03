#pragma once

#include <exception>
#include <ostream>
#include <string>

class Bureaucrat;

class AForm {
 public:
  class GradeTooHighException : public std::exception {
   public:
    const char* what() const throw();
  };

  class GradeTooLowException : public std::exception {
   public:
    const char* what() const throw();
  };

  class NotSignedException : public std::exception {
   public:
    const char* what() const throw();
  };

  AForm();
  AForm(const char* name, int gradeToSign, int gradeToExecute);
  AForm(const AForm& other);
  AForm& operator=(const AForm& other);
  virtual ~AForm();

  const char* getName() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;
  bool isSigned() const;

  void beSigned(const Bureaucrat& bureaucrat);
  virtual void execute(const Bureaucrat& executor) const = 0;

  static const int s_highestGrade = 1;
  static const int s_lowestGrade = 150;

 private:
  const char* m_name;
  const int m_gradeToSign;
  const int m_gradeToExecute;
  bool m_isSigned;
};

std::ostream& operator<<(std::ostream& os, const AForm& form);
