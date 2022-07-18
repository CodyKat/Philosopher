/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:40:51 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/18 23:52:02 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_philos(t_union *info_union, t_philo *info_philo_arr)
{
	int		n_philo;

	n_philo = -1;
	pthread_mutex_lock(&info_union->start_key);
	info_union->time_to_start = get_cur_time();
	while (++n_philo < info_union->num_of_philo)
	{
		info_philo_arr[n_philo].time_of_last_meal = info_union->time_to_start;
		if (n_philo % 2 == 0)
			pthread_create(info_union->philo_arr[n_philo], NULL, philo_even, \
												&info_philo_arr[n_philo]);
		else
			pthread_create(info_union->philo_arr[n_philo], NULL, philo_odd, \
												&info_philo_arr[n_philo]);
	}
	pthread_mutex_unlock(&info_union->start_key);
}

int	check_is_someone_dead(t_philo *info_philo_arr)
{
	int		n_philo;
	int		num_of_philo;
	size_t	time_to_die;
	size_t	time_to_starve;

	num_of_philo = info_philo_arr->info_union->num_of_philo;
	time_to_die = info_philo_arr->info_union->time_to_die;
	n_philo = -1;
	while (++n_philo < num_of_philo)
	{
		time_to_starve = get_cur_time() - \
									info_philo_arr[n_philo].time_of_last_meal;
		if (time_to_starve >= time_to_die)
		{
			philo_is_speaking(&info_philo_arr[n_philo], n_philo, \
														"is die", LASTSPEAK);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	check_all_philo_is_full(t_philo *info_philo_arr)
{
	int	n_philo;
	int	num_of_philo;
	int	num_philo_must_eat;

	num_of_philo = info_philo_arr->info_union->num_of_philo;
	num_philo_must_eat = info_philo_arr->info_union->num_each_philo_must_eat;
	n_philo = -1;
	while (++n_philo < num_of_philo)
	{
		if (info_philo_arr[n_philo].eat_count < num_philo_must_eat)
			return (FALSE);
	}
	philo_is_speaking(info_philo_arr, 0, "\b\ball philo is full", LASTSPEAK);
	return (TRUE);
}

void	watcher(t_philo *info_philo_arr, int argc)
{
	int	n_philo;
	int	num_of_philo;
	int	each_philo_must_eat;
	size_t	time_to_die;

	num_of_philo = info_philo_arr->info_union->num_of_philo;
	each_philo_must_eat = info_philo_arr->info_union->num_each_philo_must_eat;
	time_to_die = info_philo_arr->info_union->time_to_die;
	while (TRUE)
	{
		if (check_is_someone_dead(info_philo_arr) == TRUE)
			break ;
		if (argc == 6)
		{
			if (check_all_philo_is_full(info_philo_arr) == TRUE)
				break ;
		}
	}
	n_philo = -1;
	while (++n_philo < info_philo_arr->info_union->num_of_philo)
		pthread_detach(*info_philo_arr->info_union->philo_arr[n_philo]);
}

int	main(int argc, char *argv[])
{
	t_union	info_union;
	t_philo	*info_philo_arr;
	int		n_philo;

	memset(&info_union, 0, sizeof(t_union));
	if (parsing(&info_union, argc, argv) == ERROR)
		return (ft_error());
	if (malloc_and_init_resources(&info_union, &info_philo_arr) == ERROR)
		ft_error();
	make_philos(&info_union, info_philo_arr);
	watcher(info_philo_arr, argc);
	return (0);
}
