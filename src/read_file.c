/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 12:44:38 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 16:55:18 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_coord(char *str)
{
	str = ft_strchr(str, ' ');
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' ')
			return (0);
		str++;
	}
	return (1);
}

void	get_line_type(t_lem_in *lem_in, t_read *new_line, char *line)
{
	if (ft_cntwords(line, '-') == 2)
		new_line->type = L_LINK;
	if (ft_cntwords(line, ' ') == 3)
		if (is_coord(line))
			new_line->type = L_ROOM;
	if (ft_isnumber(line))
		new_line->type = L_ANTS;
	if (line[0] == '#')
		new_line->type = L_IGNO;
	if (new_line->type == L_ROOM)
		lem_in->n_rooms++;
	if (new_line->type == 0 || ft_strlen(line) == 0 ||\
		(ft_strchr(line, 'L') && new_line->type != L_COMM))
		lem_in->error = "ERROR: File not well formatted!";
	if (ft_strcmp(new_line->line, "##start") == 0 ||\
		ft_strcmp(new_line->line, "##end") == 0)
	{
		new_line->type = L_COMM;
		lem_in->n_ants++;
	}
}

void	read_to_list(t_lem_in *lem_in, char *line)
{
	t_read	*new_line;

	new_line = (t_read *)ft_memalloc(sizeof(t_read));
	new_line->line = ft_strdup(line);
	new_line->original_line = ft_strdup(line);
	get_line_type(lem_in, new_line, line);
	new_line->next = lem_in->lines;
	lem_in->lines = new_line;
}

void	read_file(t_lem_in *lem_in)
{
	char		*line;
	int			link_count;

	line = NULL;
	link_count = 0;
	while (get_next_line(0, &line))
	{
		read_to_list(lem_in, line);
		if (lem_in->lines->type == L_LINK)
			link_count = 1;
		if (lem_in->lines->type == L_ROOM && link_count != 0)
			lem_in->error = "ERROR: File not well formatted!";
		free(line);
	}
	if (link_count == 0)
		lem_in->error = "ERROR: No links!";
	if (lem_in->n_ants > 2)
		lem_in->error = "ERROR: Multiple start/end rooms!";
}
