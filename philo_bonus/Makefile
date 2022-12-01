# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 15:41:04 by tliangso          #+#    #+#              #
#    Updated: 2022/11/11 13:37:44 by tliangso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME		= philo_bonus
BONUS_NAME	=

### DIR ###
DIRSRC		= ./
BONUS_SRC	= ./
HEAD		= ./
LIBFT_SRC	= ./
SHARE_SRC	= ./
OBJ_SRC		= objs/

### TESTER GIT URL ###
TESTER1		=
TESTER2		=
TESTER3		=
TESTER4		=

### SOURCE FILE ###
SRC		=	philo_bonus.c what_time_is_it.c

BONUS	=

SHARE	=

LIBFT	= libft.c

### PATH ###
SRCS		= ${addprefix ${DIRSRC}, ${SRC}}
BONUS_SRCS	= ${addprefix ${BONUS_SRC}, ${BONUS}}
EXTRA_SRCS	= ${addprefix ${DIRSRC}, ${EXTRA}}
LIBFT_SRCS	= ${addprefix ${LIBFT_SRC}, ${LIBFT}}
SHARE_SRCS	= ${addprefix ${SHARE_SRC}, ${SHARE}}

### OBJECT FILE ###
OBJS		= ${addprefix $(OBJ_SRC),$(SRCS:.c=.o)}
BONUS_OBJS	= ${addprefix $(OBJ_SRC),$(BONUS_SRCS:.c=.o)}
EXRTA_OBJS	= ${addprefix $(OBJ_SRC),$(EXTRA_SRCS:.c=.o)}
LIBFT_OBJS	= ${addprefix $(OBJ_SRC),$(LIBFT_SRCS:.c=.o)}
SHARE_OBJS	= ${addprefix $(OBJ_SRC),$(SHARE_SRCS:.c=.o)}

### COMPILATION ###
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g -pthread

### COLORS ###
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### RULES ###

all: ${NAME}

$(OBJ_SRC)%.o: $(DIRSRC)%.c $(HEAD)$(NAME).h
	@mkdir -p objs
	@${CC} ${CFLAGS} -I${HEAD} -c -o $@ $<
	@echo "$(BLUE)$(CC) $(WHITE)$(notdir $@)$(NOC)"

bonus: ${BONUS_NAME}

${NAME}:	${OBJS} ${LIBFT_OBJS} ${SHARE_OBJS}

	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT_OBJS} ${SHARE_OBJS}
	@echo "$(GREEN)$@$(NOC)"

${BONUS_NAME}:		${BONUS_OBJS} ${LIBFT_OBJS} ${SHARE_OBJS}
	@${CC} ${CFLAGS} -o ${BONUS_NAME} ${BONUS_OBJS} ${LIBFT_OBJS} ${SHARE_OBJS}
	@echo "$(GREEN)${BONUS_NAME}$(NOC)"

extra:	${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS} ${LIBFT_OBJS}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS} ${LIBFT_OBJS}

clean:
	@echo "$(RED)clean$(NOC)"
	@${RM} ${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS} ${LIBFT_OBJS} ${SHARE_OBJS}

fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@${RM} ${NAME} ${BONUS_NAME}

re: fclean	all

tester:
	@echo "$(YELLOW)Testers are not perfect but its good enough$(NOC)"
	git clone ${TESTER1} TESTER1
	git clone ${TESTER2} TESTER2
	git clone ${TESTER3} TESTER3
	git clone ${TESTER3} TESTER4

norm:
	norminette

gitpush:
	git add .
	git status
	git commit -m ${NAME}
	git push

help:
	@clear
	@echo "$(GREEN)Avaibles options:$(NOC)"
	@echo "$(RED)==================$(NOC)"
	@echo "$(RED)| $(YELLOW)make ${NAME} $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make ${BONUS_NAME}   $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make norm      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make tester    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make clean     $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make fclean    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make re        $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make help      $(RED)|$(NOC)"
	@echo "$(RED)==================$(NOC)"

tar:
	tar -zcvf ${NAME}.tar.gz *

.PHONY:		all	clean	fclean	re bonus norm gitpush tester help tar
