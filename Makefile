##
## EPITECH PROJECT, 2025
## makefile
## File description:
## makefile
##

CXX := clang++

SRC += src/Server.cpp
SRC += src/Client.cpp
SRC += src/commandManager.cpp
SRC += src/Commands/commandQUIT.cpp
SRC += src/Commands/commandUSER.cpp
SRC += src/Commands/commandPASS.cpp
SRC += src/Commands/commandSYST.cpp
SRC += src/Commands/commandFEAT.cpp

SRC_MAIN = src/main.cpp

SRC_TEST =

OBJDIR = obj

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)
OBJ_MAIN = $(SRC_MAIN:%.cpp=$(OBJDIR)/%.o)

NAME = myftp

INCLUDE = -Isrc -I/usr/local/include

CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -stdlib=libstdc++
CFLAGS_DEBUGS = -fanalyzer -g

all: $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ_MAIN) $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests
	rm -f *.gc*

re: fclean all

debug:
	make re CXXFLAGS+="$(CFLAGS_DEBUGS)"

tests_run: fclean
	$(CXX) -o unit_tests $(SRC_TEST) $(SRC) --coverage -lcriterion $(INCLUDE) $(CXXFLAGS) $(SFML_FLAGS)
	./unit_tests
