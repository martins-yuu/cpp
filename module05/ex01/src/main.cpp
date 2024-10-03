#include "Bureaucrat.h"
#include "Form.h"

int main() {
  {
    Bureaucrat b("Alice", 42);
    Form f("Form", 41, 43);

    b.signForm(f);
  }

  {
    Bureaucrat b("Bob", 42);

    {
      Form f("Form", 50, 50);

      b.signForm(f);
    }

    {
      Form f("Form", 38, 50);

      b.signForm(f);
    }
  }

  {
    Bureaucrat b("John", 1);
    Form f("Form", 50, 50);

    b.signForm(f);
  }

  {
    Bureaucrat b("Jane", 150);
    Form f("Form", 150, 150);

    b.signForm(f);
  }
}
