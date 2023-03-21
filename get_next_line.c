/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmoreil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:36:33 by thmoreil          #+#    #+#             */
/*   Updated: 2023/03/20 17:36:35 by thmoreil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = calloc(1, sizeof(char));
	if (!line)
		return (0);
	line = ft_read(fd, stash[fd], line, line);
	if (!line)
	{
		stash[fd] = 0;
		return (0);
	}
	if (!*line)
	{
		free(line);
		return (0);
	}
	stash[fd] = ft_checktrim(line);
	return (line);
}
