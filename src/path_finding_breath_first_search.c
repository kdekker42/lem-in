/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_finding_breath_first_search.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 16:19:13 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 13:16:46 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge	*add_to_path(t_edge *path, t_vertex *room)
{
	t_edge *new_path;

	new_path = NULL;
	if (path != NULL)
	{
		new_path = ft_memalloc(sizeof(t_edge));
		new_path->vertex = room;
		new_path->next = path;
	}
	return (new_path);
}

void	add_to_path_list(t_lem_in *lem_in, t_edge *path, int path_length)
{
	t_paths	*list;
	t_paths	*new_list;

	new_list = ft_memalloc(sizeof(t_paths));
	list = lem_in->new_found_paths;
	new_list->next = list;
	new_list->path = path;
	new_list->path_length = path_length;
	lem_in->new_found_paths = new_list;
}

void	track_path(t_lem_in *lem_in)
{
	t_vertex	*current;
	t_edge		*path;
	int			path_lenght;

	current = lem_in->end;
	path_lenght = 0;
	path = ft_memalloc(sizeof(t_edge));
	path->vertex = current;
	while (current != lem_in->begin)
	{
		if (current->name != current->prev_in_bfs->name)
		{
			path_lenght++;
			path = add_to_path(path, current->prev_in_bfs);
		}
		current->visited = 1;
		visit_edge(current, current->prev_in_bfs);
		current = current->prev_in_bfs;
	}
	add_to_path_list(lem_in, path, path_lenght - 1);
}

t_edge	*pf_bfs_loop_edges(t_edge *queue)
{
	t_edge		*edges;

	edges = queue->vertex->edges;
	while (edges)
	{
		if (edges->vertex->visited == 0 && edges->visited == 0 &&\
			edges->direction == 0 && edges->visible == 1)
		{
			edges->vertex->visited = 1;
			edges->vertex->prev_in_bfs = queue->vertex;
			push_to_queue(queue, edges->vertex);
		}
		edges = edges->next;
	}
	queue = queue->next;
	return (queue);
}

int		path_finding_breath_first_search(t_lem_in *lem_in)
{
	t_edge		*queue;
	t_edge		*queue_start;

	queue = ft_memalloc(sizeof(t_edge));
	queue->vertex = lem_in->begin;
	queue_start = queue;
	lem_in->end->visited = 0;
	lem_in->begin->visited = 1;
	while (queue != NULL)
	{
		if (lem_in->end->visited == 1)
		{
			clean_queue(queue_start);
			track_path(lem_in);
			return (1);
		}
		queue = pf_bfs_loop_edges(queue);
	}
	clean_queue(queue_start);
	return (0);
}
