/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:07:37 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 13:08:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*data;
	size_t	i;

	i = 0;
	data = (char *)malloc(size + 2);
	if (!data)
		return (NULL);
	while (i <= size)
	{
		data[i] = '\0';
		i++;
	}
	data[i] = '\0';
	return (data);
}
