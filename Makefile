NAME = Philosophers
CFLAGS = -Wall -Werror -Werror 

SRCS = philo.c philo_utils.c ft_atoi.c routine.c
OBJS =	$(SRCS:.c=.o)
RM =	rm -f

all:	$(NAME)


%.o:	%.c
		@$(CC) $(CFLAGS) -c  $<

$(NAME): $(OBJS)
		@$(CC) -pthread -g -fsanitize=address $(OBJS) -o $(NAME)
		@tput setaf 2; echo "object files generated"
		@tput setaf 2; echo "philo compiled"


clean:
		@$(RM) $(OBJS)
				@tput setaf 1; echo "object files removed"

fclean:	clean
		@$(RM) $(NAME)
				@tput setaf 1; echo "executable removed"


re:		fclean all
