# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: twoerdem <twoerdem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/27 16:01:54 by twoerdem       #+#    #+#                 #
#    Updated: 2019/11/26 09:11:14 by twoerdem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
FLAGS = -Wall -Werror -Wextra
SRC =	src/main.c\
		src/read_file.c\
		src/make_links.c\
		src/edge_direction_breath_first_search.c\
		src/path_finding_breath_first_search.c\
		src/queue.c\
		src/bonus.c\
		src/pathfinding.c\
		src/index_rooms.c
LIBFT = -Ilibft -Llibft -lft

all: $(NAME)

re: fclean all

$(NAME):
	@echo "\033[1;92mCompiling $(NAME)\033[0m"
	make -C libft/ fclean && make -C libft/
	gcc -o $(NAME) $(FLAGS) $(SRC) $(LIBFT)
	@echo "\033[1;92mDone!\033[0m"

clean:
	@echo "\033[1;92mCleaning $(NAME)\033[0m"
	cd libft && make clean

fclean: clean
	cd libft && make fclean
	rm -f $(NAME)
