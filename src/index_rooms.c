/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index_rooms.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 12:49:06 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 16:37:20 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*extract_room_name(char *line)
{
	line[ft_strlen(line) - ft_strlen(ft_strchr(line, ' '))] = '\0';
	return (line);
}

int			get_hash_key(char *name, int size)
{
	int			key;

	key = 0;
	while (*name != '\0')
	{
		key += *name * 31;
		name++;
	}
	return (key % size);
}

t_vertex	*create_vertex(char *name)
{
	t_vertex	*vertex;

	vertex = ft_memalloc(sizeof(t_vertex));
	vertex->next = NULL;
	vertex->name = name;
	vertex->visited = 0;
	return (vertex);
}

void		add_room_to_table(t_read *list, t_read *prev, t_lem_in *lem_in)
{
	int		key;
	char	*name;
	t_rooms	*table;
	t_rooms	*new_table;

	name = extract_room_name(list->line);
	if (get_room_from_table(name, lem_in) != NULL)
		lem_in->error = "ERROR: Duplicate Rooms!";
	key = get_hash_key(name, lem_in->n_rooms);
	table = lem_in->hash_table[key];
	new_table = init_table(name);
	if (table != NULL)
		new_table->next = table;
	if (ft_strcmp(prev->line, "##start") == 0)
	{
		do_stuff(lem_in, new_table);
		new_table->in = NULL;
	}
	else if (ft_strcmp(prev->line, "##end") == 0)
	{
		lem_in->end = new_table->in;
		free(new_table->out);
		new_table->out = NULL;
	}
	lem_in->hash_table[key] = new_table;
}

void		index_rooms(t_lem_in *lem_in)
{
	t_read	*list;
	t_read	*prev;

	list = lem_in->lines;
	prev = list;
	lem_in->n_ants = -1;
	while (list)
	{
		if (list->type == L_COMM && prev->type != L_ROOM)
			lem_in->error = "ERROR: Found command in the wrong place!";
		if (prev->type == L_ROOM)
			add_room_to_table(prev, list, lem_in);
		if ((list->type == L_ROOM || list->type == L_LINK) &&\
			lem_in->n_ants != -1)
			lem_in->error = "ERROR: Found ants in the wrong place!";
		if (list->type == L_ANTS && list->line[0] != '-')
			lem_in->n_ants = ft_atoi(list->line);
		prev = list;
		if (list->next == NULL)
			break ;
		while ((list->type == L_IGNO || prev == list) && list->next != NULL)
			list = list->next;
	}
	if (lem_in->end == NULL || lem_in->begin == NULL)
		lem_in->error = "ERROR: Missing start/end room!";
}
