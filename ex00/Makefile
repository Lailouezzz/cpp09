CXX			:=	c++

CPPFLAGS	:=	-Wall -Wextra -Werror -std=c++98

NAME		:=	btc

BUILD_DIR	:=	build

RM			:=	rm -f

FILES		:=					\
				main			\
				BitcoinExchange

SRCS		:=	$(addsuffix .cpp,$(FILES))

OBJS		:=	$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(FILES)))

.PHONY: all clean fclean re

all: $(NAME)

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS) $(BUILD_DIR)/data.csv.o
	$(CXX) -o $@ $^ $(LFLAGS)

$(BUILD_DIR)/data.csv.o: data.csv
	@mkdir -p $(@D)
	ld --format=binary -r $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -o $@ -c $< $(CPPFLAGS)