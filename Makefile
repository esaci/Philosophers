NAME = philo

PHIL = libphi.a

PHILD = ./lib/

SRCD = ./srcs/

COMPILE = gcc

CFLAGS = -Wall -Wextra -Werror

SRC =	$(SRCD)main.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(COMPILE) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ) $(SRCD)/main.c
		rm -rf $(NAME)
		ar rc $(PHILD)$(PHIL) $(OBJ)
		ranlib $(PHILD)$(PHIL)
		$(COMPILE) -o $(NAME) $(SRCD)/main.c  $(PHILD)$(PHIL)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(PHILD)$(PHIL)

re: fclean all

.PHONY: clean fclean all re
