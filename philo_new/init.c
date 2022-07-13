/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 01:38:35 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/13 13:45:30 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_in_union_resources(t_union *info_union)
{
	info_union->philo_thread = (pthread_t *)malloc(sizeof(pthread_t) * \
													info_union->num_of_philo);
	info_union->fork_key = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
													info_union->num_of_philo);
	info_union->fork_status = (int *)malloc(sizeof(int) * \
													info_union->num_of_philo);
	if ((info_union->philo_thread == NULL) || (info_union->fork_key == NULL) || \
											(info_union->fork_status == NULL))
		return (TRUE);
	return (FALSE);
}

void	free_memory_in_union(t_union *info_union)
{
	if (info_union->philo_thread != NULL)
		free(info_union->philo_thread);
	if (info_union->fork_key != NULL)
		free(info_union->fork_key);
	if (info_union->fork_status != NULL)
		free(info_union->fork_status);
}

void	link_all_philo_and_union(t_philo *info_philo_arr, t_union *info_union)
{
	int	philo_count;

	philo_count = 0;
	while (philo_count < info_union->num_of_philo)
	{
		info_philo_arr[philo_count].info_union = info_union;
		philo_count++;
	}
}

void	init_mutex_and_make_philos(t_philo **info_philo_arr)
{
	t_union	*info_union;
	long	philo_count;
	long	num_of_philo;

	info_union = (*info_philo_arr)->info_union;
	num_of_philo = info_union->num_of_philo;
	philo_count = 0;
	pthread_mutex_init(&info_union->start_line, NULL);
	pthread_mutex_init(&info_union->voice, NULL);
	pthread_mutex_lock(&info_union->start_line);
	while (philo_count < num_of_philo)
	{
		pthread_mutex_init(&info_union->fork_key[philo_count], NULL);
		info_union->fork_status[philo_count] = UNLOCK;
		info_philo_arr[philo_count]->my_id = philo_count;
		info_philo_arr[philo_count]->eat_count = 0;
		if (philo_count % 2 == 0)
			pthread_create(&info_union->philo_thread[philo_count], \
						NULL, philo_even, info_philo_arr[philo_count]);
		else
			pthread_create(&info_union->philo_thread[philo_count], \
						NULL, philo_odd, info_philo_arr[philo_count]);
		philo_count++;
	}
	pthread_mutex_unlock(&info_union->start_line);
}
