NAME = philo

LIBPHILO = libphilo.a

OBJS_DIR = ./objs
INCL_DIR = ./include
SRCS_DIR = ./srcs/mand
BONUS_SRCS_DIR = ./srcs/bonus
DIRS = ${OBJ_DIR}

SRCS_LIST = init.c start.c stop.c time.c routine.c display.c ft_atoi.c
BONUS_SRCS_LIST = 

OBJS_LIST = ${SRCS_LIST:.c=.o}
BONUS_OBJS_LIST = ${BONUS_SRCS_LIST:.c=.o} 
OBJS = $(addprefix ${OBJS_DIR}/,${OBJS_LIST})
BONUS_OBJS = $(addprefix ${OBJS_DIR}/,${BONUS_OBJS_LIST})
DEPS = ${OBJS:.o=.d} ${BONUS_OBJS:.o=.d}

INCLUDE = -I${INCL_DIR}
CFLAGS = -g -Wall -Werror -Wextra -MMD
LDFLAGS = -L.
LIBRARIES = -lphilo


all : ${LIBPHILO} ${NAME}

bonus :   BONUS=1 all

${NAME} : $(if $(findstring bonus,${MAKECMDGOALS}), ${BONUS_SRCS_DIR}/main.c, ${SRCS_DIR}/main.c)
	${CC} ${CFLAGS} ${INCLUDE} ${LDFLAGS} $< -o $@ ${LIBRARIES}

${OBJS} ${BONUS_OBJS} : | ${OBJS_DIR}

${OBJS} : ${OBJS_DIR}/%.o : ${SRCS_DIR}/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
${BONUS_OBJS} : ${OBJS_DIR}/%.o : ${BONUS_SRCS_DIR}/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${LIBPHILO} : $(if $(findstring bonus,${MAKECMDGOALS}), ${OBJS_DIR}/${BONUS_OBJS}, ${OBJS})
	ar rcs $@ $?

${OBJS_DIR}:
	mkdir -p $@

clean:
	rm -rf ${OBJS} ${DEPS}

fclean: clean
	rm -f ${LIBPHILO}
	rm -f ${NAME}

re: fclean all

-include ${DEPS}

.PHONY: all bonus clean fclean re
