/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   edge_direction_breath_first_search.c               :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 16:21:01 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/25 18:24:48 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	edit_edge_direction(t_vertex *room_a, t_vertex *room_b)
{
	t_edge		*edge;

	edge = room_a->edges;
	while (edge->vertex != room_b)
		edge = edge->next;
	edge->direction = 0;
	edge->visible = 1;
	edge = room_b->edges;
	while (edge->vertex != room_a)
		edge = edge->next;
	edge->direction = 1;
	edge->visible = 1;
}

int		get_edge_direction(t_vertex *room_a, t_vertex *room_b)
{
	t_edge		*edge;

	edge = room_b->edges;
	while (edge->vertex != room_a)
		edge = edge->next;
	return (edge->direction);
}

void	place_edge_directions(t_lem_in *lem_in)
{
	t_vertex	*current;

	current = lem_in->begin;
	while (current != lem_in->end)
	{
		edit_edge_direction(current, current->prev_in_bfs);
		current = current->prev_in_bfs;
	}
}

t_edge	*ed_bfs_loop_edges(t_edge *queue)
{
	t_edge		*edges;

	edges = queue->vertex->edges;
	while (edges)
	{
		if (edges->vertex->visited == 0 &&\
			get_edge_direction(queue->vertex, edges->vertex))
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

int		edge_direction_breath_first_search(t_lem_in *lem_in)
{
	t_edge		*queue;
	t_edge		*queue_start;

	queue = ft_memalloc(sizeof(t_edge));
	queue->vertex = lem_in->end;
	queue_start = queue;
	lem_in->end->visited = 1;
	lem_in->begin->visited = 0;
	while (queue != NULL)
	{
		if (lem_in->begin->visited == 1)
		{
			place_edge_directions(lem_in);
			clean_queue(queue_start);
			unvisit(lem_in);
			return (1);
		}
		queue = ed_bfs_loop_edges(queue);
	}
	clean_queue(queue_start);
	return (0);
}
