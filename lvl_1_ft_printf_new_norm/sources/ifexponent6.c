/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifexponent6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:08:29 by tisantos          #+#    #+#             */
/*   Updated: 2021/02/23 01:26:53 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	add_zeros_unecessary_function_e(int add_zeros)
{
	add_zeros = 48;
	return (add_zeros);
}

static char	*exponent_write_zeros(t_slist *slist, char *string)
{
	char	*s;
	int		add_zeros;
	int		i;

	i = 0;
	add_zeros = slist->zero - ft_strlen(string);
	if (add_zeros > 0)
	{
		s = malloc(sizeof(char) * (ft_strlen(string) + add_zeros + 2));
		if (s == NULL)
			return (NULL);
		if (string[i] == '-' || string[i] == '+')
			s[i++] = string[0];
		while (add_zeros > 0)
			s[i++] = add_zeros_unecessary_function_e(add_zeros--);
		s[i] = '\0';
		s = exponent_write_zeros2(s, string);
		if (slist->free == 0)
			free(string);
		slist->free = 1;
		return (s);
	}
	return (string);
}

static int	exponent_write_minus_greater(t_plist *plist, t_slist *slist,
											int i, int length)
{
	int	count;

	count = i + length;
	if (length >= slist->minus)
	{
		slist->minus = 0;
		return (0);
	}
	else if (length < slist->minus)
	{
		while (count < slist->minus)
		{
			write(1, " ", 1);
			plist->final_format_lenght++;
			count++;
		}
	}
	slist->minus = 0;
	return (i);
}

int	exponent_write_width_greater(t_plist *plist, t_slist *slist,
											int i, int length)
{
	int	count;

	count = i + length;
	if (length >= slist->width)
	{
		slist->width = 0;
		return (0);
	}
	else if (length < slist->width)
	{
		while (count < slist->width)
		{
			write(1, " ", 1);
			plist->final_format_lenght++;
			count++;
		}
	}
	slist->width = 0;
	return (i);
}

void	exponent_write(t_plist *plist, char *string, t_slist *slist)
{
	int	i;
	int	length;

	i = 0;
	if (!plist || !string)
		return ;
	length = ft_strlen(string);
	if (slist->space == 1 && slist->width <= length)
		exponent_space(plist, slist, string, length);
	if (slist->zero > length)
	{
		string = exponent_write_zeros(slist, string);
		length = ft_strlen(string);
	}
	if (slist->width > 0 && slist->minus == 0)
		i = exponent_write_width_greater(plist, slist, i, length);
	write(1, string, length);
	if (slist->minus > 0)
		i = exponent_write_minus_greater(plist, slist, i, length);
	if (plist->final_format == NULL)
		plist->final_format = ft_strdup(string);
	else
		plist->final_format = ft_strjoin(plist->final_format, string);
	plist->final_format_lenght += length;
	free_string_exponent(string, slist);
}
