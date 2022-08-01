CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror
SRCS =	main.c	\
		parsing.c	\
		util.c		\
		util2.c		\
		init.c		\
		philo_func.c	\
		philo_behave.c	\
		philo_thinking.c	\
		watcher_func.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

$(NAME) : ${OBJS}
	${CC} -o ${NAME} ${CFLAGS} ${OBJS}

%.o:%.c
	${CC} ${CFLAGS} -o $@ -c $<

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

.PHONY : all clean fclean bonus re

re : fclean all
