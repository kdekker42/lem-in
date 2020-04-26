/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfinding.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 18:52:10 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 13:16:50 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	spread_ants(t_lem_in *lem_in, t_paths *path_list)
{
	int			ants;
	t_paths		*path;
	t_paths		*lowest;

	ants = lem_in->n_ants;
	lowest = path_list;
	while (ants != 0)
	{
		path = path_list;
		while (path)
		{
			if (path->path_length + path->ants <\
				lowest->path_length + lowest->ants)
				lowest = path;
			path = path->next;
		}
		if (lowest == NULL)
		{
			lem_in->error = "ERROR: No possible solution!";
			return ;
		}
		lowest->ants++;
		ants--;
	}
}

int		calculate_longest_path(t_paths *path_list)
{
	int		longest;

	longest = 0;
	while (path_list)
	{
		if (path_list->ants && longest <\
			path_list->path_length + path_list->ants)
			longest = path_list->path_length + path_list->ants;
		path_list = path_list->next;
	}
	return (longest);
}

void	unvisit(t_lem_in *lem_in)
{
	int			index;
	t_rooms		*table;

	index = 0;
	while (index < lem_in->n_rooms)
	{
		table = lem_in->hash_table[index];
		while (table)
		{
			unvisit_edges(table);
			table = table->next;
		}
		index++;
	}
}

void	clean_paths(t_paths *paths, t_lem_in *lem_in)
{
	t_paths		*temp_paths;

	while (paths != NULL)
	{
		temp_paths = paths->next;
		clean_queue(paths->path);
		free(paths);
		paths = temp_paths;
	}
	lem_in->found_paths = lem_in->new_found_paths;
	lem_in->new_found_paths = NULL;
}

void	pathfinding(t_lem_in *lem_in)
{
	int		path_length;
	int		edge_succes;
	int		pathfinding_succes;

	edge_succes = 1;
	lem_in->shortest_path = -1;
	while (edge_succes == 1)
	{
		edge_succes = edge_direction_breath_first_search(lem_in);
		pathfinding_succes = 1;
		while (pathfinding_succes == 1)
			pathfinding_succes = path_finding_breath_first_search(lem_in);
		unvisit(lem_in);
		spread_ants(lem_in, lem_in->new_found_paths);
		path_length = calculate_longest_path(lem_in->new_found_paths);
		if (lem_in->shortest_path < path_length && lem_in->shortest_path != -1)
			break ;
		lem_in->shortest_path = path_length;
		clean_paths(lem_in->found_paths, lem_in);
	}
}
