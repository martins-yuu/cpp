NAME		:= converter

# **************************************************************************** #
#    Dependencies                                                              #
# **************************************************************************** #

LIBS		:= \

INCS		:= \

# **************************************************************************** #
#    Sources                                                                   #
# **************************************************************************** #

SRC_DIR		:= src

SRCS		:= $(shell find $(SRC_DIR) -name '*.cpp')

# **************************************************************************** #
#    Build                                                                     #
# **************************************************************************** #

BUILD_DIR	:= build

OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CXX			:= c++
CXXFLAGS	:= -std=c++98 -Wall -Wextra -Werror -pedantic

CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(dir $(LIBS)))
LDLIBS		:= \

# **************************************************************************** #
#    Misc                                                                      #
# **************************************************************************** #

RM			:= rm -f
MAKEFLAGS	+= --no-print-directory

RED			:= $(shell tput setaf 1)
GREEN		:= $(shell tput setaf 2)
YELLOW		:= $(shell tput setaf 3)
BLUE		:= $(shell tput setaf 4)
MAGENTA		:= $(shell tput setaf 5)
CYAN		:= $(shell tput setaf 6)
WHITE		:= $(shell tput setaf 7)
ERROR		:= $(shell tput setab 1)$(WHITE)
SUCCESS		:= $(shell tput setab 2)$(WHITE)
WARNING		:= $(shell tput setab 3)$(WHITE)
INFO		:= $(shell tput setab 4)$(WHITE)
BOLD		:= $(shell tput bold)
RESET		:= $(shell tput sgr0)
CLEAR		:= $(shell tput cuu1; tput el)
TITLE		:= $(YELLOW)$(basename $(NAME))$(RESET)

# 1: action, 2: target, 3: color
define message
	$(info [$(TITLE)] $(3)$(1)$(RESET) $(2))
endef

ifdef WITH_DEBUG
	TITLE	+= $(MAGENTA)debug$(RESET)
	CFLAGS	+= -g3
else
	CFLAGS	+= -O3
endif

ifdef WITH_SANITIZER
	TITLE	+= $(MAGENTA)sanitizer$(RESET)
	CFLAGS	+= -fsanitize=address,undefined
endif

# **************************************************************************** #
#    Targets                                                                   #
# **************************************************************************** #

all: $(NAME) ## Build the program

debug: ## Build the program with debug symbols
	$(MAKE) WITH_DEBUG=1 all

sanitizer: ## Build the program with debug symbols and sanitizer
	$(MAKE) WITH_DEBUG=1 WITH_SANITIZER=1 all

loose: ## Build the program ignoring warnings
	$(MAKE) CFLAGS="$(filter-out -Werror,$(CFLAGS))" all

$(NAME): $(LIBS) $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(call message,CREATED,$(NAME),$(BLUE))

$(LIBS):
	$(MAKE) -C $(@D) -j4

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
	$(call message,CREATED,$(basename $(notdir $@)),$(GREEN))

clean: ## Remove all generated object files
	for lib in $(dir $(LIBS)); do $(MAKE) -C $$lib clean; done
	$(RM) -r $(BUILD_DIR)
	$(call message,DELETED,$(BUILD_DIR),$(RED))

fclean: clean ## Remove all generated files
	for lib in $(dir $(LIBS)); do $(MAKE) -C $$lib fclean; done
	$(RM) $(NAME)
	$(call message,DELETED,$(NAME),$(RED))

re: ## Rebuild the program
	$(MAKE) fclean
	$(MAKE) all

re.%: ## Force execution of a target recipe (usage: make re.<target>)
	$(MAKE) --always-make $*

run: $(NAME) ## Run the program
	$(call message,RUNNING,./$(NAME),$(CYAN))
	./$(NAME)

run.%: $(NAME) ## Run the program with arguments (usage: make run.<args>)
	$(call message,RUNNING,./$(NAME) $*,$(CYAN))
	./$(NAME) $*

valgrind: $(NAME) ## Run valgrind on the program
	$(call message,RUNNING,valgrind ./$(NAME),$(CYAN))
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

valgrind.%: $(NAME) ## Run valgrind on the program passing arguments (usage: make run.valgrind.<args>)
	$(call message,RUNNING,valgrind ./$(NAME) $*,$(CYAN))
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) $*

update: ## Update the repository and its submodules
	git stash
	git pull
	git submodule update --init
	git stash pop

info.%: ## Print the target recipe (usage: make info.<target>)
	$(MAKE) --dry-run --always-make $* | grep -v "info"

print.%: ## Print the value of a variable (usage: make print.<variable>)
	$(info '$*'='$($*)')

help: ## Show this message
	echo "$(BOLD)Usage: make [<name>=<value>...]$(RESET) $(BOLD)$(CYAN)[target...]$(RESET)"
	echo
	echo "$(BOLD)Targets:$(RESET)"
	grep -E '^[a-zA-Z_.%-]+:.*?## .*$$' Makefile \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "%2s$(CYAN)%-20s$(RESET) %s\n", "", $$1, $$2}'

.PHONY: all debug sanitizer loose clean fclean re run valgrind update help
.SILENT:
.IGNORE: clean fclean run update help
.DELETE_ON_ERROR:

-include $(DEPS)
