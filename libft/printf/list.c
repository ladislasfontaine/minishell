/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 07:59:41 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/06 08:09:52 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		add_element_in_list(t_list **begin, char *str, int n)
{
	t_list	*new;

	new = ft_lstnew((void *)str);
	if (!new)
		return (0);
	new->size = n;
	ft_lstadd_back(begin, new);
	return (1);
}

void	print_list(t_list *element, int *r)
{
	while (element)
	{
		if (element->size == 0)
			element->size = ft_strlen((const char *)element->content);
		ft_putstrn((char *)element->content, element->size);
		*r += element->size;
		element = element->next;
	}
}

int		read_string(t_list **begin, const char *str, int i)
{
	t_list	*new;
	int		count;

	count = 0;
	while (str[i + count] && str[i + count] != '%')
		count++;
	new = ft_lstnew((void *)ft_substr(str, i, count));
	ft_lstadd_back(begin, new);
	return (i + count);
}

void	clear_string(void *str)
{
	char	*s;

	s = (char *)str;
	ft_strdel(&s);
}
