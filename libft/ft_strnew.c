/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:07:37 by lafontai          #+#    #+#             */
/*   Updated: 2020/04/27 17:07:38 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*data;
	size_t	i;

	i = 0;
	data = (char *)malloc(size + 1);
	if (!data)
		return (NULL);
	while (i < size)
	{
		data[i] = '\0';
		i++;
	}
	data[i] = '\0';
	return (data);
}
