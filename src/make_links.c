/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_links.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 13:34:26 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 16:55:35 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms		*get_room_from_table(char *name, t_lem_in *lem_in)
{
	t_rooms		*room;

	room = lem_in->hash_table[get_hash_key(name, lem_in->n_rooms)];
	while (room != NULL)
	{
		if (ft_strcmp(room->name, name) == 0)
			return (room);
		room = room->next;
	}
	return (NULL);
}

void		insert_link(t_vertex *room_a, t_vertex *room_b, int direction)
{
	t_edge	*link;

	if (room_a && room_b)
	{
		link = ft_memalloc(sizeof(t_edge));
		link->vertex = room_b;
		link->direction = direction;
		link->next = NULL;
		if (room_a->edges != NULL)
			link->next = room_a->edges;
		room_a->edges = link;
	}
	if (direction != 0)
		insert_link(room_b, room_a, 0);
}

t_rooms		*init_table(char *name)
{
	t_rooms	*new_table;

	new_table = ft_memalloc(sizeof(t_rooms));
	new_table->name = name;
	new_table->in = create_vertex(name);
	new_table->out = create_vertex(name);
	return (new_table);
}

void		create_link(t_read *list, t_lem_in *lem_in)
{
	t_rooms	*room_a;
	t_rooms	*room_b;

	list->line[ft_strlen(list->line) -\
		ft_strlen(ft_strchr(list->line, '-'))] = '\0';
	room_a = get_room_from_table(list->line, lem_in);
	room_b = get_room_from_table(list->line + ft_strlen(list->line) + 1,\
		lem_in);
	if (room_a == NULL || room_b == NULL)
	{
		lem_in->error = "ERROR: Nonexisting room in link!";
		return ;
	}
	insert_link(room_a->in, room_a->out, 1);
	insert_link(room_a->out, room_b->in, 1);
	insert_link(room_b->in, room_b->out, 1);
	insert_link(room_b->out, room_a->in, 1);
}

void		make_links(t_read *list, t_lem_in *lem_in)
{
	while (list != NULL)
	{
		if (list->type == L_LINK)
		{
			create_link(list, lem_in);
		}
		list = list->next;
	}
}
