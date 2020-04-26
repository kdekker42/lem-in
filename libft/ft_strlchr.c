/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: twoerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 14:25:35 by twoerdem       #+#    #+#                */
/*   Updated: 2019/10/03 17:38:43 by twoerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlchr(char *s, int c)
{
	size_t		pos;

	pos = 0;
	while (s[pos])
	{
		if (s[pos] == c)
			return (pos);
		pos++;
	}
	if (c == '\0')
		return (pos);
	return (-1);
}
