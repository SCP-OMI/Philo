/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcharouh <mcharouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:32:21 by mcharouh          #+#    #+#             */
/*   Updated: 2022/09/28 23:14:23 by mcharouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosopher.h"

int	put_error(int *err)
{
	*err = 1;
	return (255);
}

int	check_edges(long long result, int sign, int *err)
{
	if (result > 2147483647 && sign == 1)
		return (put_error(err));
	else if (result == 0)
		return (put_error(err));
	return (result *= sign);
}

int	ft_atoi(const char *str, int *err)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			return (put_error(err));
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (put_error(err));
		result = (result * 10) + str[i++] - '0';
		if (result > 2147483647)
			return (put_error(err));
	}
	return (check_edges(result, 1, err));
}
