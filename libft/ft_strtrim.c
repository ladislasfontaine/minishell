/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:07:56 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/04 08:36:17 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		t_len;
	int		before;
	int		after;

	t_len = ft_strlen(s1);
	before = 0;
	after = 0;
	while (s1[before] && ft_strchr(set, (int)s1[before]))
		before++;
	if (t_len - before <= 0)
		return (ft_substr(s1, 0, 0));
	while (t_len - 1 - after >= 0 && ft_strchr(set, (int)s1[t_len - 1 - after]))
		after++;
	return (ft_substr(s1, before, t_len - before - after));
}
