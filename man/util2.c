/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:24:35 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/01 23:56:56 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	paras_is_in_valid_range(t_union *info_union, int argc)
{
	if ((info_union->num_of_philo == 0) || (info_union->time_to_die == 0) \
		|| (info_union->time_to_eat == 0) || (info_union->time_to_sleep == 0) \
		|| (info_union->num_of_philo > INT_MAX) \
		|| (info_union->time_to_die > INT_MAX) \
		|| (info_union->time_to_eat > INT_MAX) \
		|| (info_union->time_to_sleep > INT_MAX))
		return (ERROR);
	if ((argc == 6) && ((info_union->num_each_philo_must_eat == 0) || \
						(info_union->num_each_philo_must_eat > INT_MAX)))
		return (ERROR);
	return (TRUE);
}

void	*ft_calloc(size_t size)
{
	void	*p_mem;

	p_mem = malloc(size);
	if (p_mem != NULL)
		memset(p_mem, 0, size);
	return (p_mem);
}

void	destroy_all_mutex(t_union *info_union)
{
	int	n_philo;

	n_philo = -1;
	while (++n_philo < (int)info_union->num_of_philo)
		pthread_mutex_destroy(info_union->fork_arr[n_philo]);
	pthread_mutex_destroy(&info_union->voice);
	pthread_mutex_destroy(&info_union->start_key);
}

void	error_in_making_philo(t_union *info_union, t_philo **info_philo_arr)
{
	destroy_all_mutex(info_union);
	free_all_resources(info_union, info_philo_arr);
	ft_error();
}
