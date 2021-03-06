/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifexponent7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 00:45:14 by tisantos          #+#    #+#             */
/*   Updated: 2021/02/16 00:45:46 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	free_string_exponent(char *string, t_slist *slist)
{
	if (slist->free == 1)
		free(string);
}

void	exponent_space(t_plist *plist, t_slist *slist, char *string, int length)
{
	if (string[0] == '+' || string[0] == '-')
	{
		slist->width = length;
		slist->minus++;
		slist->zero++;
	}
	else
		slist->width = length + 1;
	slist->minus--;
	slist->zero--;
	if (slist->minus != 0)
		exponent_write_width_greater(plist, slist, 0, length);
}

char	*exponent_write_zeros2(char *s, char *string)
{
	if (string[0] == '-' || string[0] == '+')
		s = ft_strjoin(s, string + 1);
	else
		s = ft_strjoin(s, string);
	free(string);
	return (s);
}
