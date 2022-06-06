/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:50:49 by saguesse          #+#    #+#             */
/*   Updated: 2022/06/06 16:40:08 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	int	ret;
	char	buf[BUFFER_SIZE + 1];

	ret = read(fd, buf, BUFFER_SIZE); 
	buf[BUFFER_SIZE] = '\0';
	
	return (buf);
}

int	main()
{
	int	fd;

	fd = open("test", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("open() error");
		return (1);
	}
	else
		printf("%s\n", get_next_line(fd));

	if (close(fd) == -1)
	{
		ft_putstr("close() error");
		return (1);
	}
	return (0);
}
