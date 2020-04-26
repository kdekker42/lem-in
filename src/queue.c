/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 16:25:06 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 13:18:44 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	visit_edge(t_vertex *room_a, t_vertex *room_b)
{
	t_edge		*edge;

	edge = room_a->edges;
	while (edge->vertex != room_b)
		edge = edge->next;
	edge->visited = 1;
	edge = room_b->edges;
	while (edge->vertex != room_a)
		edge = edge->next;
	edge->visited = 1;
}

void	do_stuff(t_lem_in *lem_in, t_rooms *new_table)
{
	lem_in->begin = new_table->out;
	free(new_table->in);
}

void	unvisit_edges(t_rooms *table)
{
	t_edge		*edges;

	if (table->in)
	{
		edges = table->in->edges;
		while (edges)
		{
			edges->visited = 0;
			edges = edges->next;
		}
		table->in->visited = 0;
	}
	if (table->out)
	{
		edges = table->out->edges;
		while (edges)
		{
			edges->visited = 0;
			edges = edges->next;
		}
		table->out->visited = 0;
	}
}

void	clean_queue(t_edge *queue)
{
	t_edge		*temp_queue;

	while (queue != NULL)
	{
		temp_queue = queue->next;
		queue->vertex->visited = 0;
		free(queue);
		queue = temp_queue;
	}
}

void	push_to_queue(t_edge *queue, t_vertex *room)
{
	t_edge		*temp_queue;
	t_edge		*new_queued;

	temp_queue = queue;
	new_queued = ft_memalloc(sizeof(t_edge));
	new_queued->vertex = room;
	while (temp_queue->next != NULL)
		temp_queue = temp_queue->next;
	temp_queue->next = new_queued;
}
