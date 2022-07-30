CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror
THREAD_FLAGS = -lpthread
SRCS =	main_bonus.c			\
		parsing_bonus.c			\
		philo_behave_bonus.c	\
		philo_bonus.c			\
		util_bonus.c			\
		util2_bonus.c			\
		philo_eat_func_bonus.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

$(NAME) : ${OBJS}
	${CC} -o ${NAME} ${THREAD_FLAGS} ${CFLAGS} ${OBJS}

%.o:%.c
	${CC} ${CFLAGS} -o $@ -c $<

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

.PHONY : all clean fclean bonus re

re : fclean all
