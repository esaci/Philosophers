NAME = philo_bonus

PHIL = libphi_bonus.a

PHILD = ./lib/

SRCD = ./srcs/

SANIT = -pthread -Wall -Wextra -Werror -fsanitize=thread

SANIT2 = -pthread -Wall -Wextra -Werror -fsanitize=address -fno-omit-frame-pointer

COMPILE = gcc

CFLAGS = -pthread -Wall -Wextra -Werror

SRC =	$(SRCD)init_philo_bonus.c			\
		$(SRCD)init_game_bonus.c			\
		$(SRCD)routine_bonus.c				\
		$(SRCD)routine_eat_bonus.c			\
		$(SRCD)routine_sleep_bonus.c		\
		$(SRCD)routine_think_bonus.c		\
		$(SRCD)routine_die_bonus.c			\
		$(SRCD)fast_wait_bonus.c			\
		$(SRCD)waiter_end_bonus.c			\
		$(SRCD)return_bonus.c				\
		$(SRCD)stopper_bonus.c				\
		$(SRCD)time_bonus.c					\
		$(SRCD)utils_bonus.c				\
		$(SRCD)utils2_bonus.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(COMPILE) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ) $(SRCD)/main_bonus.c
		rm -rf $(NAME)
		ar rc $(PHILD)$(PHIL) $(OBJ)
		ranlib $(PHILD)$(PHIL)
		$(COMPILE) $(CFLAGS) -o $(NAME) $(SRCD)/main_bonus.c  $(PHILD)$(PHIL)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(PHILD)$(PHIL)

re: fclean all

.PHONY: clean fclean all re
