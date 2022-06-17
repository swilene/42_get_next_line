/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:52:23 by saguesse          #+#    #+#             */
/*   Updated: 2022/06/17 17:23:11 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == '\n')
			return ((char *)s);
		s++;
	}
	return (NULL);
}

int	ft_read_fd(int fd, char **l, char *buf)
{
	int		ret;
	char	*line;

	line = *l;
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == -1)
		return (1);
	if (ret == 0)
		return (2);
	buf[ret] = '\0';
	if (line == NULL)
	{
		line = ft_strdup(buf);
		if (line == NULL)
			return (1);
	}
	else
	{
		line = ft_strjoin(line, buf, ret);
		if (line == NULL)
			return (1);
	}
	*l = line;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 0;
	line = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 0)
		return (NULL);
	if (*buf)
	{
		line = ft_strdup(buf);
		if (line == NULL)
			return (NULL);
	}
	while (ft_strchr(buf) == NULL && i == 0)
		i = ft_read_fd(fd, &line, buf);
	if (i == 1)
		return (NULL);
	ft_bzero(buf, BUFFER_SIZE + 1);
	if (i == 0)
		write_buf(line, buf);
	return (line);
}

int	main()
{
	int		fd;
	char	**line;

	fd[3] = open("test", O_RDONLY);
	fd[4] = open("test2", O_RDONLY);
	fd[5] = open("test3", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	if (close(fd) == -1)
	{
		printf("close() error");
		return (1);
	}
	return (0);
}
