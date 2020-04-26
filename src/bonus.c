/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <twoerdem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 20:08:40 by twoerdem       #+#    #+#                */
/*   Updated: 2019/11/26 16:29:13 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	paths_found(t_lem_in *lem_in)
{
	t_paths		*paths;
	t_edge		*path;

	ft_putendl("Paths found: ");
	paths = lem_in->found_paths;
	while (paths)
	{
		path = paths->path;
		while (path->next)
		{
			ft_putstr(path->vertex->name);
			ft_putstr(" -> ");
			path = path->next;
		}
		ft_putendl(path->vertex->name);
		paths = paths->next;
	}
}

void	bonus_flag(t_lem_in *lem_in, char *flag)
{
	if (ft_strcmp(flag, "-l") == 0)
	{
		ft_putstr("Number of lines used: ");
		ft_putnbr(lem_in->shortest_path);
		ft_putendl("");
	}
	else if (ft_strcmp(flag, "-p") == 0)
		paths_found(lem_in);
	else
		ft_putendl("Unkown flag");
	ft_putendl("");
}
