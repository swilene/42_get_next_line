/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:50:49 by saguesse          #+#    #+#             */
/*   Updated: 2022/06/07 17:45:32 by saguesse         ###   ########.fr       */
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

char	*write_stash(char *stash)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] != '\n')
		i++;
	i++;
	str = (char *)malloc(sizeof(*str) * (ft_strlen(stash) - i) + 1);
	if (!str)
		return (NULL);
	while (stash[i])
	{
		str[j] = stash[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*write_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(*line) * i + 2);
	if (!line)
		return (NULL);
	while (j <= i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\n';
	line[j++] = '\0';
	return (line);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i1;
	int		i2;
	int		j;
	char	*str;

	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	j = 0;
	str = (char *)malloc(sizeof(*str) * (i1 + i2) + 1);
	if (!(str))
		return (NULL);
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	j = 0;
	while (s2[j])
	{
		str[i1 + j] = s2[j];
		j++;
	}
	str[i1 + j] = '\0';
	return (str);
}

char	*ft_strchr(const char *s)
{
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
	static size_t	ret;
	char			buf[BUFFER_SIZE + 1];
	char			*stash;
	char			*line;

	while (ft_strchr(stash) == NULL)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	line = write_line(stash);
	stash = write_stash(stash);
	printf("stash = %s\t", stash);
	return (line);
}

int	main()
{
	int	fd;

	fd = open("test", O_RDONLY);
	if (fd == -1)
	{
		printf("open() error");
		return (1);
	}
	printf("line = %s", get_next_line(fd));
	printf("line = %s", get_next_line(fd));
	printf("line = %s", get_next_line(fd));
	//printf("line = %s", get_next_line(fd));
	if (close(fd) == -1)
	{
		printf("close() error");
		return (1);
	}
	return (0);
}
