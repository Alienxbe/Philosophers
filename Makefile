# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marykman <marykman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 15:44:08 by marykman          #+#    #+#              #
#    Updated: 2024/09/02 17:55:39 by marykman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -----------------------------------Colors------------------------------------

RED				:=	[38;5;9m
GREEN			:=	[38;5;10m
BLUE			:= 	[38;5;14m
YELLOW			:=	[38;5;226m
RESET			:=	[38;5;7m
PREFIX			=	[${YELLOW}${NAME}${RESET}]		

# ---------------------------------Compilation---------------------------------

CC					:=	@gcc
CFLAGS				:=	-Wall -Wextra -Werror

# ---------------------------------Librairies----------------------------------

INCLUDES			:= -I ./includes
LIBRARIES			:=

# --------------------------------Source files---------------------------------

NAME				:=	philo
FILES				:=	main.c \
						parsing.c
FILES_UTILS			:=	ft_index.c \
						ft_isspace.c \
						ft_strlen.c \
						ft_strtol.c
SRCS				:=	$(addprefix srcs/, ${FILES})
SRCS				+=	$(addprefix srcs/utils/, ${FILES_UTILS})
OBJS				:=	$(patsubst srcs%.c, objs%.o, ${SRCS})
FILES				:=	philo.h \
						utils.h
HEADERS				:=	$(addprefix includes/, ${FILES});

# -----------------------------------Rules-------------------------------------

objs/%.o:	srcs/%.c ${HEADERS}
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@
	@echo "${PREFIX}Compilation of $<..."
	

$(NAME):	${OBJS} ${HEADERS}
	${CC} ${CFLAGS} ${OBJS} ${LIBRARIES} -o $@
	@echo "${PREFIX}${NAME} compiled!"

all:	${NAME}

clean:
	@rm -f ${OBJS}

fclean:
	@rm -f ${NAME} ${OBJS}

re:		fclean all

# -----------------------------------.PHONY------------------------------------

.PHONY:	all clean fclean re