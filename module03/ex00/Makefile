NAME		:= claptrap

# **************************************************************************** #
#    Dependencies                                                              #
# **************************************************************************** #

LIBS		:= \

INCS		:= \

# **************************************************************************** #
#    Sources                                                                   #
# **************************************************************************** #

SRC_DIR		:= .

SRCS		:= $(shell find $(SRC_DIR) -name '*.cpp')

SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))

# **************************************************************************** #
#    Build                                                                     #
# **************************************************************************** #

BUILD_DIR	:= build

OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98

CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(dir $(LIBS)))
LDLIBS		:=

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
RESET		:= $(shell tput sgr0)
CLEAR		:= $(shell tput cuu1; tput el)
TITLE		:= $(YELLOW)$(basename $(NAME))$(RESET)

# 1: action, 2: target, 3: color
define message
	$(info [$(TITLE)] $(3)$(1)$(RESET) $(2))
endef

ifdef WITH_DEBUG
	TITLE		+= $(MAGENTA)debug$(RESET)
	CXXFLAGS	+= -g3
else
	CXXFLAGS	+= -O3
endif

ifdef WITH_SANITIZER
	TITLE		+= $(MAGENTA)sanitizer$(RESET)
	CXXFLAGS	+= -fsanitize=address
endif

# **************************************************************************** #
#    Targets                                                                   #
# **************************************************************************** #

all: $(NAME) ## Build the program

$(NAME): $(LIBS) $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(call message,CREATED,$(NAME),$(BLUE))

$(LIBS):
	$(MAKE) -C $(@D)

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

run: ## Run the program
	./$(NAME)

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
	echo "Usage: make [<name>=<value>...] [target...]"
	echo
	echo "Targets:"
	grep -E '^[a-zA-Z_.%-]+:.*?## .*$$' Makefile \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "%2s$(CYAN)%-20s$(RESET) %s\n", "", $$1, $$2}'

.PHONY: all clean fclean re help
.SILENT:
.IGNORE: clean fclean run update help
.DELETE_ON_ERROR:

-include $(DEPS)
