/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/20 11:32:51 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 16:55:49 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	print_list(t_read *list)
{
	if (list != NULL)
	{
		print_list(list->next);
		ft_putendl(list->original_line);
	}
}

int		pull_ants_and_print(t_edge *path, int ant, int printed)
{
	path->vertex->new_ant = ant;
	while (path->next)
	{
		path->next->prev = path;
		path->next->vertex->new_ant = path->vertex->ant;
		path = path->next;
	}
	while (path)
	{
		path->vertex->ant = path->vertex->new_ant;
		if (path->vertex->ant)
		{
			if (printed)
				ft_putstr(" ");
			ft_putstr("L");
			ft_putnbr(path->vertex->ant);
			ft_putstr("-");
			ft_putstr(path->vertex->name);
			printed++;
		}
		path = path->prev;
	}
	return (printed);
}

void	print_solution(t_paths *path_list, t_lem_in *lem_in, int ant)
{
	int		printed;
	t_edge	*current_path;
	t_paths	*temp_path_list;

	printed = 1;
	while (printed)
	{
		printed = 0;
		temp_path_list = path_list;
		while (temp_path_list)
		{
			current_path = temp_path_list->path->next;
			if (ant <= lem_in->n_ants && temp_path_list->ants)
			{
				printed = pull_ants_and_print(current_path, ant, printed);
				temp_path_list->ants--;
				ant++;
			}
			else
				printed = pull_ants_and_print(current_path, 0, printed);
			temp_path_list = temp_path_list->next;
		}
		if (printed)
			ft_putendl("");
	}
}

void	execute_functions(t_lem_in *lem_in)
{
	read_file(lem_in);
	if (lem_in->error)
		return ;
	lem_in->hash_table = ft_memalloc(sizeof(t_vertex *) * lem_in->n_rooms);
	index_rooms(lem_in);
	if (lem_in->error)
		return ;
	make_links(lem_in->lines, lem_in);
	if (lem_in->n_ants < 1)
		lem_in->error = "ERROR: Number of ants is incorrect!";
	if (lem_in->error)
		return ;
	pathfinding(lem_in);
	if (lem_in->error)
		return ;
}

int		main(int ac, char **av)
{
	t_lem_in	*lem_in;
	int			bonus;

	lem_in = (t_lem_in *)ft_memalloc(sizeof(t_lem_in));
	execute_functions(lem_in);
	bonus = 1;
	if (lem_in->error)
	{
		ft_putendl(lem_in->error);
		return (0);
	}
	while (ac > bonus)
	{
		bonus_flag(lem_in, av[bonus]);
		bonus++;
	}
	print_list(lem_in->lines);
	ft_putendl("");
	print_solution(lem_in->found_paths, lem_in, 1);
}
