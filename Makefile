# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 10:48:22 by tzanchi           #+#    #+#              #
#    Updated: 2023/08/30 11:48:34 by tzanchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler targets and libraries
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
CLIENT		=	client
SERVER		=	server
LIBFT		=	libft.a

# Directories
SRCS_DIR	=	./sources/
HEAD_DIR	=	./includes/
LIBFT_DIR	=	./libft/

OBJ_DIR		=	${SRCS_DIR}.o

# Colours, symbols and utils
GREEN		=	\033[1;32m
CYAN		=	\033[1;36m
YELLOW		=	\033[1;33m
RED			=	\033[1;31m
NC			=	\033[0m
BOLD		=	\033[1m
TICK		=	✓

CLIENT_SRC	=	client.c
SERVER_SRC	=	server.c
COMMON_SRC	=	common_utils.c

CLIENT_SRCS	=	$(addprefix ${SRCS_DIR}, ${CLIENT_SRC})
SERVER_SRCS	=	$(addprefix ${SRCS_DIR}, ${SERVER_SRC})
COMMON_SRCS	=	$(addprefix ${SRCS_DIR}, ${COMMON_SRC})
SRC_NR		=	$(shell expr $(words ${CLIENT_SRCS}) + $(words ${SERVER_SRCS}) + $(words ${COMMON_SRCS}))

CLIENT_OBJS	=	$(addprefix ${OBJ_DIR}/, $(notdir $(CLIENT_SRCS:.c=.o)))
SERVER_OBJS	=	$(addprefix ${OBJ_DIR}/, $(notdir $(SERVER_SRCS:.c=.o)))
COMMON_OBJS	=	$(addprefix ${OBJ_DIR}/, $(notdir $(COMMON_SRCS:.c=.o)))

all:			project_logo ${OBJ_DIR}
				@make -s ${LIBFT}
				@make -s ${SERVER}
				@make -s ${CLIENT}

${LIBFT}:
				@echo "${CYAN}\nCOMPILING $$(echo ${LIBFT} | tr '[:lower:]' '[:upper:]')${NC}"
				@if [ -d ${LIBFT_DIR} ]; \
				then git -C ${LIBFT_DIR} pull; \
				else git clone git@github.com:theozanchi/42_Berlin_libft.git ${LIBFT_DIR}; \
				fi
				make -C ${LIBFT_DIR}
				@echo "${YELLOW}Moving ${LIBFT} at the root of the repository${NC}"
				@mv ${LIBFT_DIR}/${LIBFT} .

${SERVER}:		entry_message ${SERVER_OBJS} ${COMMON_OBJS}
				@${CC} ${CFLAGS} ${SERVER_SRCS} ${COMMON_SRCS} -I${HEAD_DIR} ${LIBFT} -o ${SERVER}

${CLIENT}:		${CLIENT_OBJS} ${COMMON_OBJS}
				@${CC} ${CFLAGS} ${CLIENT_SRCS} ${COMMON_SRCS} -I${HEAD_DIR} ${LIBFT} -o ${CLIENT}
				@echo "${YELLOW}\nCompilation complete, ${CLIENT} and ${SERVER} executable at the root of the directory${NC}\n"

${OBJ_DIR}:
				@if [ ! -d "${OBJ_DIR}" ]; \
				then mkdir -p "${OBJ_DIR}"; \
				fi

$(OBJ_DIR)/%.o:	$(SRCS_DIR)%.c
				@echo -n "Compiling $(notdir $<)"; \
				${CC} ${CFLAGS} -I${HEAD_DIR} -c $< -o $@; \
				echo "${GREEN} ${TICK}${NC}"; 

clean:
				@make -sC ${LIBFT_DIR} clean >/dev/null 2>&1
				@if [ ! -d "${OBJ_DIR}" ]; \
				then \
					echo "Repo already clean"; \
				else \
					echo "Removing all .o files"; \
					rm -r ${OBJ_DIR}; \
				fi

fclean:			clean
				@make -sC ${LIBFT_DIR} fclean >/dev/null 2>&1
				@echo "Removing ${NAME} and ${LIBFT} files from root"
				@rm -f ${NAME} ${LIBFT}

re:				fclean all

project_logo:
				@echo "${RED}   _     _     _     _     _     _     _     _  \n  / \   / \   / \   / \   / \   / \   / \   / \ \n ( ${CYAN}m${NC}${RED} ) ( ${CYAN}i${NC}${RED} ) ( ${CYAN}n${NC}${RED} ) ( ${CYAN}i${NC}${RED} ) ( ${CYAN}t${NC}${RED} ) ( ${CYAN}a${NC}${RED} ) ( ${CYAN}l${NC}${RED} ) ( ${CYAN}k${NC}${RED} )\n  \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/    ${NC}a 42 project by Théo Zanchi"

entry_message:
				@echo "${CYAN}\nCOMPILING $$(echo ${SERVER} | tr '[:lower:]' '[:upper:]') and $$(echo ${CLIENT} | tr '[:lower:]' '[:upper:]')\n${NC}${BOLD}Compiling necessary .o files out of ${SRC_NR} .c files in total${NC}"

.PHONY:			all clean fclean re project_logo entry_message
