/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:04:56 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/13 04:09:50 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char *str)
{
	return (('0' <= *str) && (*str <= '9'));
}

long	ft_atol(char *str)
{
	long	return_num;

	return_num = 0;
	while (*str)
	{
		if (!is_digit(str))
			return (ERROR);
		return_num *= 10;
		return_num += (*str - '0');
		if (return_num > INT_MAX)
			return (ERROR);
		str++;
	}
	return (return_num);
}

int	ft_error(void)
{
	write(2, "ERROR\n", 6);
	return (ERROR);
}

long	get_cur_time(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return (s_time.tv_sec * 1000 + s_time.tv_usec / 1000);
}

long	ft_time_diff(long time1, long time2)
{
	if (time1 >= time2)
		return (time1 - time2);
	else
		return (time2 - time1);
}
