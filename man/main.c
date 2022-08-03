/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:40:51 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/03 15:26:21 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philos(t_union *info_union, t_philo *info_philo_arr)
{
	int		n_philo;
	int		philo_create_status;

	n_philo = -1;
	pthread_mutex_lock(&info_union->start_key);
	info_union->time_to_start = get_cur_time();
	while (++n_philo < (int)info_union->num_of_philo)
	{
		info_philo_arr[n_philo].time_of_last_meal = info_union->time_to_start;
		if (n_philo % 2 == 1)
			philo_create_status = \
				pthread_create(info_union->philo_arr[n_philo], NULL, \
										philo_even, &info_philo_arr[n_philo]);
		else
			philo_create_status = \
				pthread_create(info_union->philo_arr[n_philo], NULL, \
										philo_odd, &info_philo_arr[n_philo]);
		if (philo_create_status == -1)
			return (ERROR);
	}
	pthread_mutex_unlock(&info_union->start_key);
	return (TRUE);
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
			pthread_mutex_lock(&info_philo_arr->info_union->voice);
			printf("%zu %d is die\n", get_time_stamp(info_philo_arr), n_philo);
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
	pthread_mutex_lock(&info_philo_arr->info_union->voice);
	printf("%zu all philo is full\n", get_time_stamp(info_philo_arr));
	return (TRUE);
}

void	*get_watcher_func_pointer(int argc)
{
	if (argc == 6)
		return (watcher_optional);
	else
		return (watcher_no_optional);
}

int	main(int argc, char *argv[])
{
	t_union	info_union;
	t_philo	*info_philo_arr;
	void	(*watcher)(t_philo *);

	memset(&info_union, 0, sizeof(t_union));
	if (parsing(&info_union, argc, argv) == ERROR)
		return (ft_error());
	if (malloc_and_init_resources(&info_union, &info_philo_arr) == ERROR)
		ft_error();
	if (make_philos(&info_union, info_philo_arr) == ERROR)
	{
		error_in_making_philo(&info_union, &info_philo_arr);
		return (0);
	}
	watcher = get_watcher_func_pointer(argc);
	watcher(info_philo_arr);
	destroy_all_mutex(&info_union);
	free_all_resources(&info_union, &info_philo_arr);
	return (0);
}
