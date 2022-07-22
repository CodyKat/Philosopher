/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:18:01 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/20 21:32:01 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_all_resources(t_union *info_union, t_philo **info_philo_arr, \
																int n_philo)
{
	int	num_of_philo;

	num_of_philo = info_union->num_of_philo;
	info_union->fork_status = (int *)ft_calloc(sizeof(int) * num_of_philo);
	info_union->philo_arr = \
					(pthread_t **)malloc(sizeof(pthread_t *) * num_of_philo);
	info_union->fork_arr = \
	(pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * num_of_philo);
	*info_philo_arr = (t_philo *)ft_calloc(sizeof(t_philo) * num_of_philo);
	if ((*info_philo_arr == NULL) || (info_union->philo_arr == NULL) \
		|| (info_union->fork_arr == NULL) || (info_union->fork_status == NULL))
		return (ERROR);
	while (++n_philo < num_of_philo)
	{
		info_union->philo_arr[n_philo] = (pthread_t *)malloc(sizeof(pthread_t));
		info_union->fork_arr[n_philo] = \
							(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if ((info_union->philo_arr[n_philo] == NULL) || \
				(info_union->fork_arr[n_philo] == NULL))
			return (ERROR);
	}
	return (TRUE);
}

void	free_all_resources(t_union *info_union, t_philo **info_philo_arr)
{
	return ;
}

void	init_all_resources(t_union *info_union, t_philo *info_philo_arr)
{
	size_t	philo_count;

	pthread_mutex_init(&info_union->voice, NULL);
	pthread_mutex_init(&info_union->start_key, NULL);
	philo_count = -1;
	while (++philo_count < info_union->num_of_philo)
	{
		info_philo_arr[philo_count].my_id = philo_count;
		info_philo_arr[philo_count].right_fork_id = \
								(philo_count + 1) % info_union->num_of_philo;
		info_philo_arr[philo_count].left_fork_id = philo_count;
		info_philo_arr[philo_count].info_union = info_union;
		pthread_mutex_init(info_union->fork_arr[philo_count], NULL);
	}
}

int	malloc_and_init_resources(t_union *info_union, t_philo **info_philo_arr)
{
	if (malloc_all_resources(info_union, info_philo_arr, -1) == ERROR)
	{
		free_all_resources(info_union, info_philo_arr);
		return (ERROR);
	}
	init_all_resources(info_union, *info_philo_arr);
	return (TRUE);
}
