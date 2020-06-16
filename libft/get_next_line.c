/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 20:17:15 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 11:45:20 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_buf_to_line(char *buf, int n, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while (buf[n + i] && buf[n + i] != '\n')
		i++;
	temp = ft_strdup(*line);
	free(*line);
	if (!(*line = (char *)malloc(sizeof(char) * (ft_strlen(temp) + i + 1))))
	{
		free(temp);
		return (-1);
	}
	*line[0] = '\0';
	*line = ft_strncat(*line, temp, (size_t)ft_strlen(temp));
	*line = ft_strncat(*line, buf + n, (size_t)i);
	free(temp);
	return (i);
}

static void	read_file(char *buf, int *res, int n, int fd)
{
	int		i;

	if (n == 0)
	{
		i = 0;
		while (buf[i])
		{
			buf[i] = '\0';
			i++;
		}
		if ((*res = read(fd, buf, BUFFER_SIZE)) >= 0)
			buf[*res] = '\0';
	}
}

int			get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	static int	n;
	static int	res;
	int			i;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	*line = ft_strdup("");
	while (1)
	{
		read_file(buf, &res, n, fd);
		if ((i = add_buf_to_line(buf, n, line)) == -1)
			return (-1);
		n += i;
		if (buf[n] == '\n' || res < BUFFER_SIZE)
			break ;
		if (n >= res)
			n = 0;
	}
	n += 1;
	if (!res || (res < BUFFER_SIZE && n > res))
		return (0);
	if (n >= res)
		n = 0;
	return (1);
}
