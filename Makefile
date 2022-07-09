CC = cc
NAME = philo
#CFLAGS = -g -Wall -Wextra -Werror
SRCS =	main.c	\
		util_1.c

OBJS = ${SRCS:.c=.o}

all : ${NAME}

$(NAME) : ${OBJS}
	${CC} -o ${NAME} ${CFLAGS} ${OBJS}

clean : 
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

.PHONY : all clean fclean bonus re

re : fclean all
