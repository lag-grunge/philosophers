NAME = philo
NAME_B = philo_bonus
LIBPHILO = libphilo.a

OBJS_DIR_CMN = ./objs
OBJS_DIR = ./objs/mand
OBJS_DIR_B = ./objs/bonus
INCL_DIR = ./includes
SRCS_DIR_CMN = ./srcs
SRCS_DIR = ./srcs/mand
SRCS_DIR_B= ./srcs/bonus
DIRS = ${OBJS_DIR_CMN} ${OBJS_DIR} ${OBJS_DIR_B}

SRCS_LIST_CMN = ft_atoi.c
SRCS_LIST = init.c control.c routine.c main.c utils.c test.c
SRCS_LIST_B = init.c control.c philo_control.c routine.c utils_bonus.c main.c
OBJS_LIST_CMN = ${SRCS_LIST_CMN:.c=.o}
OBJS_LIST = ${SRCS_LIST:.c=.o}
OBJS_LIST_B= ${SRCS_LIST_B:.c=.o}
OBJS_CMN = $(addprefix ${OBJS_DIR_CMN}/,${OBJS_LIST_CMN})
OBJS = $(addprefix ${OBJS_DIR}/,${OBJS_LIST})
OBJS_B = $(addprefix ${OBJS_DIR_B}/,${OBJS_LIST_B})
DEPS = ${OBJS_CMN:.o=.d} ${OBJS:.o=.d} ${OBJS_B:.o=.d}

INCLUDE = -I${INCL_DIR}
CFLAGS := -g -Wall -Werror -Wextra -MMD
LIBRARIES = -pthread -lphilo
LDFLAGS = -L.


all : ${LIBPHILO} ${NAME}
bonus : ${LIBPHILO} ${NAME_B}
bonus : BONUS=1
dbg : all
dbg : CFLAGS += -g -fsanitize=address
dbg : LIBRARIES += -lasan
dbg_bonus : bonus
dbg_bonus : CFLAGS += -g -fsanitize=address
dbg_bonus : LIBRARIES += -lasan


${NAME} : ${OBJS} ${LIBPHILO}
	${CC} ${INCLUDE} ${LDFLAGS} $(filter-out ${LIBPHILO},$^) -o $@ ${LIBRARIES}

${NAME_B} : ${OBJS_B} ${LIBPHILO}
	${CC} ${INCLUDE} ${LDFLAGS} $(filter-out ${LIBPHILO},$^) -o $@ ${LIBRARIES}

${LIBPHILO} : ${OBJS_CMN}
	ar rcs $@ $?

${OBJS_CMN} ${OBJS} ${OBJS_B} : | ${DIRS}

${OBJS_CMN} : ${OBJS_DIR_CMN}/%.o : ${SRCS_DIR_CMN}/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
${OBJS} : ${OBJS_DIR}/%.o : ${SRCS_DIR}/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
${OBJS_B} : ${OBJS_DIR_B}/%.o : ${SRCS_DIR_B}/%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${DIRS} :
	mkdir -p $@

clean:
	rm -rf ${OBJS_DIR_CMN}

fclean: clean
	rm -f ${NAME}
	rm -f ${NAME_B}
	rm -f ${LIBPHILO}

re: fclean all

-include ${DEPS}

.PHONY: all bonus clean fclean re
