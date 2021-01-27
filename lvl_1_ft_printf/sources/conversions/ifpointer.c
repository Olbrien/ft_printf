/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifpointer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 07:17:07 by tisantos          #+#    #+#             */
/*   Updated: 2021/01/24 13:48:03 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static char		*precision_hexadecimal(char *string, t_slist *slist)
{
	int		length_to_zeros;
	int		total_length;
	char	*temp;
	int		i;
	int		start;

	i = 0;
	start = 2;
	length_to_zeros = slist->precision - (ft_strlen(string) - 2);
	total_length = ft_strlen(string) + length_to_zeros + 1;
	if (!(temp = malloc(sizeof(char) * total_length)))
		return (NULL);
	temp[i++] = '0';
	temp[i++] = 'x';
	while (length_to_zeros > 0)
	{
		temp[i++] = '0';
		length_to_zeros--;
	}
	while (string[start] != '\0')
		temp[i++] = string[start++];
	temp[i] = '\0';
	slist->precision = -1;
	return (temp);
}

static char		*reverse_hexadecimal(char *string, t_slist *slist)
{
	char	*temp;
	int		i;
	int		end;

	end = ft_strlen(string) - 1;
	i = 0;
	if (!(temp = malloc(sizeof(char) * (ft_strlen(string) + 1))))
		return (NULL);
	temp[i++] = '0';
	temp[i++] = 'x';
	while (string[end] != 'x')
	{
		temp[i] = string[end];
		end--;
		i++;
	}
	temp[i] = '\0';
	if (slist->precision >= 0 && slist->precision > (int)ft_strlen(temp) - 2)
		temp = precision_hexadecimal(temp, slist);
	return (temp);
}

static char		*return_if_one_digit(char *send, long long int value)
{
	char			*temp;

	temp = ft_itoa(value);
	send = ft_strjoin(send, temp);
	return (send);
}

static char		*convert_return_hexadecimal(long long int pointer_value,
											char *send, t_slist *slist)
{
	long long int	value;
	long long int	remainder;
	int				hexa;

	value = pointer_value;
	if (value >= 0 && value < 10)
		return (return_if_one_digit(send, value));
	remainder = value % 16;
	while (value >= 10)
	{
		if (remainder >= 10)
		{
			hexa = remainder + 87;
			send = ft_strjoinchr(send, hexa);
		}
		else
			send = ft_strjoinchr(send, (remainder + 48));
		value = value / 16;
		remainder = value % 16;
	}
	if (value != 0)
		send = ft_strjoinchr(send, (value + 48));
	send = reverse_hexadecimal(send, slist);
	return (send);
}

void			ifpointer(t_plist *plist, t_slist *slist, va_list *args)
{
	char			*send;
	long long int	pointer_value;

	pointer_value = va_arg(*args, long long int);
	if (pointer_value == '\0')
	{
		send = ft_strdup("(nil)");
	}
	else if (pointer_value != '\0')
	{
		send = ft_strdup("0x");
		send = convert_return_hexadecimal(pointer_value, send, slist);
	}
	slist->precision = -1;
	pointer_write(plist, send, slist);
	plist->format_count++;
}