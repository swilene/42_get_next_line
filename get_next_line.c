/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:52:23 by saguesse          #+#    #+#             */
/*   Updated: 2022/06/14 17:23:26 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dup;

	i = 0;
	dup = (char *)malloc(sizeof(*dup) * (ft_strlen(src) + 1));
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_bzero(void *s, size_t n)
{
	char		*str;
	size_t		i;

	i = 0;
	str = s;
	while (i != n)
	{
		str[i] = '\0';
		i++;
	}
}

char	*write_line(char *line, int i)
{
	int		j;
	char	*str;

	j = 0;
	str = (char *)malloc(sizeof(*str) * i + 1);
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	free(line);
	return (str[j] = '\0', str);
}

char	*write_buf(char *line, char *buf)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	i++;
	len = i;
	while (line[i])
	{
		buf[j] = line[i];
		i++;
		j++;
	}
	line = write_line(line, len);
	return (line);
}

char	*ft_strjoin(char *line, char *buf, int ret)
{
	int		i;
	int		j;
	char	*str;

	if (line == NULL)
		return (buf);
	i = ft_strlen(line);
	j = 0;
	str = (char *)malloc(sizeof(*str) * (i + ret) + 1);
	if (!str)
		return (NULL);
	while (line[j])
	{
		str[j] = line[j];
		j++;
	}
	j = 0;
	while (buf[j])
	{
		str[i + j] = buf[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

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

char	*get_next_line(int fd)
{
	int			ret;
	static char	buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd == -1)
		return (NULL);
	if (buf[0] != '\0')
		line = ft_strdup(buf);
	else
		line = NULL;
	while (ft_strchr(buf) == NULL)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1 || ret == 0)
			return (NULL);
		buf[ret] = '\0';
		if (line == NULL)
			line = ft_strdup(buf);
		else
			line = ft_strjoin(line, buf, ret);
	}
	ft_bzero(buf, BUFFER_SIZE + 1);
	line = write_buf(line, buf);
	return (line);
}

int	main()
{
	int		fd;
	char	*line;

	fd = open("test", O_RDONLY);
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
