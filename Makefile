NAME = philo

PHIL = libphi.a

PHILD = ./lib/

SRCD = ./srcs/

SANIT = -fsanitize=thread

COMPILE = gcc

CFLAGS = -g -pthread -Wall -Wextra -Werror

SRC =	$(SRCD)init_philo.c		\
		$(SRCD)init_game.c		\
		$(SRCD)utils.c		\
		$(SRCD)utils2.c		\
		$(SRCD)stopper.c	\
		$(SRCD)routine.c	\
		$(SRCD)show.c		\
		$(SRCD)custom_usleep.c	\
		$(SRCD)routine_eat.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(COMPILE) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ) $(SRCD)/main.c
		rm -rf $(NAME)
		ar rc $(PHILD)$(PHIL) $(OBJ)
		ranlib $(PHILD)$(PHIL)
		$(COMPILE) $(CFLAGS) -o $(NAME) $(SRCD)/main.c  $(PHILD)$(PHIL)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(PHILD)$(PHIL)

re: fclean all

.PHONY: clean fclean all re
