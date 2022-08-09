/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:31:09 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/28 17:33:27 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_even(void *info_philo)
{
	t_philo	*my_info;

	my_info = (t_philo *)info_philo;
	pthread_mutex_lock(&my_info->info_union->start_key);
	pthread_mutex_unlock(&my_info->info_union->start_key);
	while (my_info->info_union->stop_eating == FALSE)
	{
		get_my_left_fork(my_info);
		get_my_right_fork(my_info);
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
	pthread_mutex_lock(&my_info->info_union->start_key);
	pthread_mutex_unlock(&my_info->info_union->start_key);
	usleep(1000);
	while (my_info->info_union->stop_eating == FALSE)
	{
		get_my_right_fork(my_info);
		get_my_left_fork(my_info);
		philo_eat(my_info);
		philo_sleep(my_info);
		philo_think(my_info);
		usleep(300);
	}
	return (NULL);
}
