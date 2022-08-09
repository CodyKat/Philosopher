/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:31:09 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/10 04:37:19 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_stop_eating_flag_on(t_union *info_union)
{
	pthread_mutex_lock(&info_union->m_stop_eating);
	if (info_union->stop_eating == TRUE)
	{
		pthread_mutex_unlock(&info_union->m_stop_eating);
		return (TRUE);
	}
	return (FALSE);
}

void	*philo_even(void *info_philo)
{
	t_philo	*my_info;

	my_info = (t_philo *)info_philo;
	pthread_mutex_lock(&my_info->info_union->start_key);
	pthread_mutex_unlock(&my_info->info_union->start_key);
	while (1)
	{
		if (is_stop_eating_flag_on(my_info->info_union) == TRUE)
			return (NULL);
		pthread_mutex_unlock(&my_info->info_union->m_stop_eating);
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
	while (1)
	{
		if (is_stop_eating_flag_on(my_info->info_union) == TRUE)
			return (NULL);
		pthread_mutex_unlock(&my_info->info_union->m_stop_eating);
		get_my_right_fork(my_info);
		get_my_left_fork(my_info);
		philo_eat(my_info);
		philo_sleep(my_info);
		philo_think(my_info);
		usleep(300);
	}
	return (NULL);
}
