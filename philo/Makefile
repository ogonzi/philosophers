# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogonzale <ogonzale@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/18 10:00:13 by ogonzale          #+#    #+#              #
#    Updated: 2022/09/19 09:49:16 by ogonzale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard

NAME 		:= philo
INC		 	:= inc/
HEADER 		= -I$(INC)
SRC_DIR 	:= src/
OBJ_DIR 	:= obj/
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -pthread -g3
FSANITIZE	:= -fsanitize=address -g3
RM 			:= rm -f

# Colors

DEF_COLOR 	:= \033[0;39m
GRAY 		:= \033[0;90m
RED 		:= \033[0;91m
GREEN 		:= \033[0;92m
YELLOW 		:= \033[0;93m
BLUE 		:= \033[0;94m
MAGENTA 	:= \033[0;95m
CYAN 		:= \033[0;96m
WHITE 		:= \033[0;97m

#Sources

SRC_FILES	:=	philo thread ft_atoi_mod activity utils utils_2 

SRC 		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF := .cache_exists

all:	$(NAME)

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) -MT $@ -MMD -MP $(CFLAGS) $(HEADER) -O3 -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(MAND_DIR)
	@touch $(OBJF)

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) $(OBJF)
	@echo "$(BLUE)Pipex object and dependency files cleaned.$(DEF_COLOR)"

fclean:	clean
	@$(RM) $(NAME)
	@rm -rf *.dSYM
	@find . -name ".DS_Store" -delete
	@echo "$(CYAN)$(NAME) executable and junk files cleaned.$(DEF_COLOR)"

re:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME).$(DEF_COLOR)"

norm:
	@clear
	@norminette $(SRC_DIR) $(INC) $(LIBFT_DIR) | grep -v Norme -B1 || true
	
.PHONY:	all clean fclean re norm

-include $(OBJ:%.o=%.d) $(BOBJ:%.o=%.d)
