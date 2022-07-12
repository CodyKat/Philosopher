/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 03:08:41 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/13 04:18:57 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_even(void *info_philo)
{
	t_philo	*my_info;

	my_info = (t_philo *)info_philo;
	my_info->my_left_fork_id = my_info->my_id;
	my_info->my_right_fork_id = \
					(my_info->my_id + 1) % my_info->info_union->num_of_philo;
	pthread_mutex_unlock(&my_info->info_union->start_line);
	pthread_mutex_lock(&my_info->info_union->start_line);
	while (my_info->info_union->is_someone_dead != DEAD)
	{
		get_my_rigth_fork(my_info);
		get_my_left_fork(my_info);
		philo_eat(my_info);
		philo_sleep(my_info);
		philo_think(my_info);
	}
	return (NULL);
}

void	*philo_odd(void *info_philo)
{
	t_philo	*my_info;

	my_info = (t_philo *)info_philo;
	my_info->my_left_fork_id = my_info->my_id;
	my_info->my_right_fork_id = \
					(my_info->my_id + 1) % my_info->info_union->num_of_philo;
	pthread_mutex_unlock(&my_info->info_union->start_line);
	pthread_mutex_lock(&my_info->info_union->start_line);
	while (my_info->info_union->is_someone_dead != DEAD)
	{
		get_my_left_fork(my_info);
		get_my_rigth_fork(my_info);
		philo_eat(my_info);
		philo_sleep(my_info);
		philo_think(my_info);
	}
	return (NULL);
}
