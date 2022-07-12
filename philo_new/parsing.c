/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 01:37:24 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/13 04:09:26 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(t_union *info_union, int argc, char **argv)
{
	if ((argc == 5) || (argc == 6))
	{
		info_union->num_of_philo = ft_atol(argv[1]);
		info_union->time_to_died = ft_atol(argv[2]);
		info_union->time_to_eat = ft_atol(argv[3]);
		info_union->time_to_sleep = ft_atol(argv[4]);
		if ((info_union->num_of_philo <= 0) || (info_union->time_to_died <= 0) \
		|| (info_union->time_to_eat <= 0) || (info_union->time_to_sleep <= 0))
			return (ERROR);
		if (argc == 6)
		{
			info_union->time_to_each_must_eat = ft_atol(argv[5]);
			if (info_union->time_to_each_must_eat <= 0)
				return (ERROR);
		}
		return (TRUE);
	}
	return (ERROR);
}
