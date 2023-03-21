/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmoreil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:36:58 by thmoreil          #+#    #+#             */
/*   Updated: 2023/03/20 17:37:02 by thmoreil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_bufferjoin(char *dest, char *src)
{
	char		*joined;
	size_t		len;
	int			i;

	if (!dest)
	{
		dest = calloc(1, sizeof(char));
		if (!dest)
			return (0);
	}
	len = strlen(dest) + strlen(src);
	joined = malloc((len + 1) * sizeof(char));
	if (!joined)
		return (0);
	i = 0;
	while (dest[i])
		*joined++ = dest[i++];
	free(dest);
	i = 0;
	while (src[i])
		*joined++ = src[i++];
	*joined = 0;
	return (joined - len);
}

char	*ft_linetrim(char *str)
{
	char	*tstr;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i + len])
		len++;
	tstr = malloc((len + 1) * sizeof(char));
	if (!tstr)
		return (0);
	while (str[i])
		*tstr++ = str[i++];
	*tstr = 0;
	str[i - len] = 0;
	return (tstr - len);
}

static int	ft_is_nl(char *str)
{
	int		times;

	times = 0;
	if (!str)
		return (times);
	while (*str)
	{
		if (*str == '\n')
			times++;
		str++;
	}
	return (times);
}

char	*ft_read(int fd, char *stash, char *get_line, char *line)
{
	char	*buffer;
	ssize_t	check;

	buffer = calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (0);
	check = BUFFER_SIZE;
	while (check == BUFFER_SIZE && !ft_is_nl(stash))
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == -1)
		{
			free(line);
			free(stash);
			return (0);
		}
		buffer[check] = 0;
		stash = ft_bufferjoin(stash, buffer);
	}
	free(buffer);
	get_line = ft_bufferjoin(get_line, stash);
	free(stash);
	return (get_line);
}

char	*ft_checktrim(char *not_trimmed_line)
{
	char	*stash;
	int		i;

	stash = 0;
	i = 0;
	if (ft_is_nl(not_trimmed_line) == 1)
	{
		while (not_trimmed_line[i + 1])
			i++;
		if (not_trimmed_line[i] != '\n')
			stash = ft_linetrim(not_trimmed_line);
	}
	if (ft_is_nl(not_trimmed_line) > 1)
		stash = ft_linetrim(not_trimmed_line);
	return (stash);
}
