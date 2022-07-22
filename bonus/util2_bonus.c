/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:24:35 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/21 04:09:48 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	paras_is_in_valid_range(t_union *info_union, int argc)
{
	if ((info_union->num_of_philo == 0) || (info_union->time_to_die == 0)\
		|| (info_union->time_to_eat == 0) || (info_union->time_to_sleep == 0) ||
		(info_union->num_of_philo > INT_MAX) || \
		(info_union->time_to_die > INT_MAX) || \
		(info_union->time_to_eat > INT_MAX) || \
		(info_union->time_to_sleep > INT_MAX))
		return (ERROR);
	if ((argc == 6) && ((info_union->num_each_philo_must_eat == 0) || \
						(info_union->num_each_philo_must_eat > INT_MAX)))
		return (ERROR);
	return (TRUE);
}

void	check_is_dead(t_philo *info_philo)
{
	if (info_philo->info_union->time_to_die >= \
							get_cur_time() - info_philo->time_of_last_meal)
		exit(DEAD);
}

void	*ft_calloc(size_t size)
{
	void	*p_mem;

	p_mem = malloc(size);
	if (p_mem != NULL)
		memset(p_mem, 0, size);
	return (p_mem);
}

size_t	get_time_stamp(t_union *info_union)
{
	return (get_cur_time() - info_union->time_to_start);
}
