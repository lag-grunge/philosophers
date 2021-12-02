NAME = philo
NAME_B = philo_bonus

OBJS_DIR = ./objs/mand
OBJS_DIR_B = ./objs/bonus
INCL_DIR = ./include
SRCS_DIR = ./srcs/mand
SRCS_DIR_B= ./srcs/bonus
DIRS = ${OBJ_DIR}

SRCS_LIST = init.c ft_atoi.c \
			control.c routine.c \
						display.c time.c
SRCS_LIST_B = init.c ft_atoi.c\
			control.c routine.c \
						display.c time.c
OBJS_LIST = ${SRCS_LIST:.c=.o}
OBJS_LIST_B= ${SRCS_LIST_B:.c=.o} 
OBJS = $(addprefix ${OBJS_DIR}/,${OBJS_LIST})
OBJS_B = $(addprefix ${OBJS_DIR_B}/,${OBJS_LIST_B})
DEPS = ${OBJS:.o=.d} ${OBJS_B:.o=.d}

INCLUDE = -I${INCL_DIR}
CFLAGS = -g -Wall -Werror -Wextra -MMD
LIBRARIES = -lpthread


all : ${NAME}
bonus : ${NAME_B}

${NAME} : ${SRCS_DIR}/main.c ${OBJS} 
	${CC} ${CFLAGS} ${INCLUDE} $^ -o $@ ${LIBRARIES}

${NAME_B} : ${SRCS_DIR_B}/main.c ${OBJS_B}
	${CC} ${CFLAGS} ${INCLUDE} $^ -o $@ ${LIBRARIES}

${OBJS} ${OBJS_B} : | ${OBJS_DIR} ${OBJS_DIR_B}

${OBJS} : ${OBJS_DIR}/%.o : ${SRCS_DIR}/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
${OBJS_B} : ${OBJS_DIR_B}/%.o : ${SRCS_DIR_B}/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${OBJS_DIR} ${OBJS_DIR_B} :
	mkdir -p ./objs
	mkdir -p $@

clean:
	rm -rf ${OBJS_DIR}
	rm -rf ${OBJS_DIR_B}

fclean: clean
	rm -f ${NAME}
	rm -f ${NAME_B}

re: fclean all

-include ${DEPS}

.PHONY: all bonus clean fclean re
