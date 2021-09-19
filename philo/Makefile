NAME = philo

NAME2 = philos2

PHIL = libphi.a

PHILD = ./lib/

SRCD = ./srcs/

SANIT = -pthread -Wall -Wextra -Werror -fsanitize=thread

SANIT2 = -pthread -Wall -Wextra -Werror -fsanitize=address -fno-omit-frame-pointer

COMPILE = gcc

CFLAGS = -pthread -Wall -Wextra -Werror -fsanitize=thread

SRC =	$(SRCD)init_philo.c		\
		$(SRCD)init_game.c		\
		$(SRCD)utils.c		\
		$(SRCD)utils2.c		\
		$(SRCD)utils3.c		\
		$(SRCD)unlock_waves.c	\
		$(SRCD)stopper.c	\
		$(SRCD)routine.c	\
		$(SRCD)show.c		\
		$(SRCD)custom_usleep.c	\
		$(SRCD)routine_eat.c \
		$(SRCD)routine_sleep.c \
		$(SRCD)routine_think.c \
		$(SRCD)routine_die.c \
		$(SRCD)waiter.c			\
		$(SRCD)waiter_init.c			\
		$(SRCD)waiter_w.c			\
		$(SRCD)waiter_w2.c			\
		$(SRCD)waiter_w3.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(COMPILE) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ) $(SRCD)/main.c
		rm -rf $(NAME)
		ar rc $(PHILD)$(PHIL) $(OBJ)
		ranlib $(PHILD)$(PHIL)
		$(COMPILE) $(CFLAGS) -o $(NAME) $(SRCD)/main.c  $(PHILD)$(PHIL)

sanit2: $(NAME2)

$(NAME2) : $(OBJ) $(SRCD)/main.c
		rm -rf $(NAME)
		ar rc $(PHILD)$(PHIL) $(OBJ)
		ranlib $(PHILD)$(PHIL)
		$(COMPILE) $(SANIT2) -o $(NAME) $(SRCD)/main.c  $(PHILD)$(PHIL)

sanit: $(NAME1)

$(NAME1) : $(OBJ) $(SRCD)/main.c
		rm -rf $(NAME)
		ar rc $(PHILD)$(PHIL) $(OBJ)
		ranlib $(PHILD)$(PHIL)
		$(COMPILE) $(SANIT) -o $(NAME) $(SRCD)/main.c  $(PHILD)$(PHIL)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(PHILD)$(PHIL)

re: fclean all

.PHONY: clean fclean all re
