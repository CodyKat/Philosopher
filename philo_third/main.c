/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:40:51 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/14 03:23:51 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_all_resources(t_union *info_union, t_philo **info_philo_arr, \
																int n_philo)
{
	info_union->fork_status = \
					(int *)ft_calloc(sizeof(int) * info_union->num_of_philo);
	info_union->philo_arr = \
		(pthread_t **)malloc(sizeof(pthread_t *) * info_union->num_of_philo);
	info_union->fork_arr = \
	(pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * \
													info_union->num_of_philo);
	*info_philo_arr = \
			(t_philo *)ft_calloc(sizeof(t_philo) * info_union->num_of_philo);
	if ((*info_philo_arr == NULL) || (info_union->philo_arr == NULL) \
		|| (info_union->fork_arr == NULL) || (info_union->fork_status == NULL))
		return (ERROR);
	while (++n_philo < info_union->num_of_philo)
	{
		info_union->philo_arr[n_philo] = (pthread_t *)malloc(sizeof(pthread_t));
		info_union->fork_arr[n_philo] = \
							(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if ((info_philo_arr[n_philo] == NULL) || \
				(info_union->fork_arr[n_philo] == NULL))
			return (ERROR);
	}
	return (TRUE);
}

void	free_all_resources(t_union *info_union, t_philo **info_philo_arr)
{
	return ;
}

void	init_all_resources(t_union *info_union, t_philo **info_philo_arr)
{
	size_t	philo_count;

	pthread_mutex_init(&info_union->voice, NULL);
	pthread_mutex_init(&info_union->start_key, NULL);
	pthread_mutex_init(&info_union->key_of_deadflag_box, NULL);
	philo_count = -1;
	while (++philo_count < info_union->num_of_philo)
	{
		info_philo_arr[philo_count]->my_id = philo_count;
		info_philo_arr[philo_count]->right_fork_id = \
								(philo_count + 1) % info_union->num_of_philo;
		info_philo_arr[philo_count]->left_fork_id = philo_count;
		info_philo_arr[philo_count]->info_union = info_union;
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
	init_all_resources(info_union, info_philo_arr);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_union	info_union;
	t_philo	*info_philo_arr;

	memset(&info_union, 0, sizeof(t_union));
	if (parsing(&info_union, argc, argv) == ERROR)
		return (ft_error());
	// debuging {OK}
	if (malloc_and_init_resources(&info_union, &info_philo_arr) == ERROR)
		return (ERROR);
	printf("OK");
	return (0);
}
