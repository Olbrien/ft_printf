/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned_long.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:15:08 by marvin            #+#    #+#             */
/*   Updated: 2021/02/23 01:30:39 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_itoa_len(unsigned long n)
{
	long int			len;

	len = 0;
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

static void	ft_itoa_write(char *finish, unsigned long len,
								unsigned long n)
{
	while (n > 9)
	{
		finish[len--] = (n % 10) + '0';
		n = n / 10;
	}
	finish[len] = n + '0';
}

char	*ft_itoa_unsigned_long(unsigned long int n)
{
	unsigned long int				len;
	char							*finish;

	len = ft_itoa_len(n);
	finish = malloc((len + 1) * sizeof(char));
	if (finish == NULL)
		return (NULL);
	finish[len--] = '\0';
	ft_itoa_write(finish, len, n);
	return (finish);
}
