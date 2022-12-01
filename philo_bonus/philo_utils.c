/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:45:09 by tliangso          #+#    #+#             */
/*   Updated: 2022/11/16 22:53:56 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ismember(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_checkset(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ismember(str[i], set))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	state;
	int	number;
	int	negative;

	state = 1;
	number = 0;
	negative = -1;
	while (*str != '\0')
	{
		if (state <= 3 && ft_isdigit(*str))
		{
			state = 3;
			number = (number * 10) - (*str - '0');
		}
		else if (state <= 2 && (*str == '+' || *str == '-'))
		{
			state = 3;
			if (*str == '-')
				negative = -negative;
		}
		else if (state != 1 || !ft_isspace(*str))
			break ;
		str++;
	}
	return (number * negative);
}
