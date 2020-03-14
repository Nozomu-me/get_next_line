/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:09:38 by amouassi          #+#    #+#             */
/*   Updated: 2019/12/20 13:53:27 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		read_buffer(int fd, char **buffer)
{
	int ret;

	*buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (*buffer == NULL)
		return (-1);
	if ((ret = read(fd, *buffer, BUFFER_SIZE)) > 0)
	{
		(*buffer)[ret] = '\0';
		return (1);
	}
	free(*buffer);
	if (ret == -1)
		return (-1);
	return (0);
}

int		check_errors(int fd, char **line, char **str)
{
	if (BUFFER_SIZE <= 0)
		return (1);
	if (fd < 0 || !line)
		return (1);
	if (!str[fd])
	{
		if (!(str[fd] = malloc(1)))
			return (1);
		str[fd][0] = '\0';
	}
	return (0);
}

int		ft_check(char **str, char **line)
{
	if (!ft_strlen(*str))
	{
		*line = ft_strdup("");
		return (0);
	}
	*line = ft_strdup(*str);
	free(*str);
	str[0] = 0;
	return (0);
}

int		get_helper(int fd, char **str, char **line, int *index)
{
	int		ret;
	char	*tmp;
	char	*buffer;

	while ((*index = find_index(*str, '\n')) == -1)
	{
		ret = read_buffer(fd, &buffer);
		if (ret == -1)
			return (-1);
		else if (ret == 0)
			return (ft_check(str, line));
		tmp = *str;
		*str = ft_strjoin(*str, buffer);
		*line = *str;
		free(tmp);
		free(buffer);
	}
	return (-2);
}

int		get_next_line(int fd, char **line)
{
	static char		*str[4864];
	char			*tmp;
	int				index;
	int				ret;

	if (check_errors(fd, line, str) == 1)
		return (-1);
	ret = get_helper(fd, &str[fd], line, &index);
	if (ret == -1)
		return (-1);
	else if (ret == 0)
		return (0);
	else
	{
		tmp = str[fd];
		*line = ft_substr(str[fd], 0, index);
		str[fd] = ft_strdup(&str[fd][index + 1]);
		free(tmp);
	}
	return (1);
}
