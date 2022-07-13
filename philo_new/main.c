/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:16:58 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/13 17:51:06 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_log(t_philo *info_philo, long time, char *message, int is_last)
{
	static int	shutdown_flag = FALSE;

	pthread_mutex_lock(&info_philo->info_union->voice);
	if (shutdown_flag == FALSE)
		printf("%ld %d %s\n", time, info_philo->my_id, message);
	if ((info_philo->info_union->is_someone_dead == TRUE) || \
			(info_philo->info_union->all_philo_full == TRUE))
		shutdown_flag = TRUE;
	pthread_mutex_unlock(&info_philo->info_union->voice);
}

void	wait_philos(t_union *info_union)
{
	int	philo_count;

	philo_count = 0;
	while (philo_count < info_union->num_of_philo)
	{
		pthread_join(info_union->philo_thread[philo_count], NULL);
		philo_count++;
	}
}

void	check_philo_dead(t_philo *info_philo_arr)
{
	t_union	*info_union;
	long	philo_count;
	long	num_of_philo;
	long	time_to_start;

	info_union = info_philo_arr->info_union;
	num_of_philo = info_philo_arr->info_union->num_of_philo;
	time_to_start = info_union->time_to_start;
	while (1)
	{
		philo_count = 0;
		while (philo_count < num_of_philo)
		{
			if (ft_time_diff(time_to_start, get_cur_time()) \
								>= info_union->time_to_died)
			{
				info_union->is_someone_dead = DEAD;
				return ;
			}
			philo_count++;
		}
	}
}

int main(int argc, char *argv[])
{
	t_union	info_union;
	t_philo	*info_philo_arr;

	memset(&info_union, 0, sizeof(t_union));
	if (parsing(&info_union, argc, argv) == ERROR)
		return (ft_error());
	info_philo_arr = \
			(t_philo *)malloc(sizeof(t_philo) * info_union.num_of_philo);
	if (malloc_in_union_resources(&info_union) || (info_philo_arr == NULL))
	{
		free_memory_in_union(&info_union);
		if (info_philo_arr != NULL)
			free(info_philo_arr);
		return (ft_error());
	}
	link_all_philo_to_union(info_philo_arr, &info_union);
	init_mutex_and_make_philos(info_philo_arr);
	check_philo_dead(info_philo_arr);
	wait_philos(&info_union);
	return (0);
}
