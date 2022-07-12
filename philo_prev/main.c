/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 04:43:56 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/12 20:34:21 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_time(void)
{
	struct timeval s_time;

	gettimeofday(&s_time, 0);
	return (s_time.tv_sec  * 1000 + s_time.tv_usec / 1000);
}

void	set_error_num(t_union_info *union_info, int errnum)
{
	union_info->errnum = errnum;
}

int	is_valid_input_range(t_union_info *union_info, int argc)
{
	if (union_info->num_of_philo > INT_MAX)
		set_error_num(union_info, ERR_NUM_OF_PHILO);
	else if (union_info->time_to_die > INT_MAX)
		set_error_num(union_info, ERR_TIME_TO_DIE);
	else if (union_info->time_to_eat > INT_MAX)
		set_error_num(union_info, ERR_TIME_TO_EAT);
	else if (union_info->time_to_sleep > INT_MAX)
		set_error_num(union_info, ERR_TIME_TO_SLEEP);
	if ((argc == 6) && (union_info->num_each_philo_must_eat > INT_MAX))
		set_error_num(union_info, ERR_NUM_TO_MUST_EAT);
	if (union_info->errnum != 0)
		return (FALSE);
	else
		return (TRUE);
}

int	parsing_and_check_error(t_union_info *union_info, int argc, char *argv[])
{
	if ((argc == 5) || (argc == 6))
	{
		union_info->num_of_philo = ft_atoul(argv[1]);
		union_info->time_to_die = ft_atoul(argv[2]);
		union_info->time_to_eat = ft_atoul(argv[3]);
		union_info->time_to_sleep = ft_atoul(argv[4]);
		if (argc == 6)
			union_info->num_each_philo_must_eat = ft_atoul(argv[5]);
		if (is_valid_input_range(union_info, argc) == FALSE)
			return (FALSE);
		else
			return (TRUE);
	}
	else
		set_error_num(union_info, ERR_NUM_OF_ARGC);
	return (FALSE);
}

void	ft_print_error(int errnum)
{
	if (errnum == ERR_NUM_OF_ARGC)
		printf("no match count of argc\n");
	else if (errnum == ERR_NUM_OF_PHILO)
		printf("error size of philo\n");
	else if (errnum == ERR_TIME_TO_DIE)
		printf("error size of time_to_die\n");
	else if (errnum == ERR_TIME_TO_EAT)
		printf("error size of time_to_eat\n");
	else if (errnum == ERR_TIME_TO_SLEEP)
		printf("error size of time_to_sleep\n");
	else if (errnum == ERR_NUM_TO_MUST_EAT)
		printf("error size of num_each_philo_must_eat\n");
	printf("argment must be positive int\n");
	printf("and must not have signflag like '+' or '-'\n");
}

void	malloc_in_info(t_union_info *info)
{
	size_t	philo_id;
	size_t	fork_id;

	fork_id = -1;
	info->philo_arr = \
			(pthread_t *)malloc(sizeof(pthread_t) * info->num_of_philo);
	info->fork_arr = \
	(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	while (++fork_id < info->num_of_philo)
		pthread_mutex_init(info->fork_arr + fork_id, 0);
	pthread_mutex_init(&info->voice, 0);
	pthread_mutex_init(&info->start_key, 0);
	info->fork_status = (int *)malloc(sizeof(int) * info->num_of_philo);
	memset(info->fork_status, 0, sizeof(int) * info->num_of_philo);
}

void	philo_is_speaking(t_philo_info *info, size_t time, char *str, int state)
{
	if (info->union_info->is_someone_dead == DEAD)
		return ;
	pthread_mutex_lock(&info->union_info->voice);
	printf("%zu %zu %s\n", time, info->my_id, str);
	pthread_mutex_unlock(&info->union_info->voice);
}

void	*func_odd_philo_thread(void *my_philo_info)
{
	t_philo_info	*my_info;

	my_info = (t_philo_info *)my_philo_info;
	my_info->right_fork_id = \
			(my_info->my_id + 1) % my_info->union_info->num_of_philo;
	my_info->left_fork_id = my_info->my_id;
	pthread_mutex_lock(&my_info->union_info->start_key);
	pthread_mutex_unlock(&my_info->union_info->start_key);
	while (my_info->union_info->is_someone_dead == NOBODY_DEAD)
	{
		get_my_right_fork(my_info);
		get_my_left_fork(my_info);
		philo_eat(my_info);
		philo_sleep(my_info);
		philo_think(my_info);
	}
	return (0);
}

void	*func_even_philo_thread(void *my_philo_info)
{
	t_philo_info	*my_info;

	my_info = (t_philo_info *)my_philo_info;
	my_info->right_fork_id = \
			(my_info->my_id + 1) % my_info->union_info->num_of_philo;
	my_info->left_fork_id = my_info->my_id;
	pthread_mutex_lock(&my_info->union_info->start_key);
	pthread_mutex_unlock(&my_info->union_info->start_key);
	usleep(1000);
	while (my_info->union_info->is_someone_dead == NOBODY_DEAD)
	{
		get_my_left_fork(my_info);
		get_my_right_fork(my_info);
		philo_eat(my_info);
		philo_sleep(my_info);
		philo_think(my_info);
		// usleep(100);
	}
	return (0);
}

t_philo_info	*make_philos(t_union_info *union_info)
{
	t_philo_info	*philo_info_arr;
	int				philo_id;

	philo_info_arr = \
	(t_philo_info *)malloc(sizeof(t_philo_info) * union_info->num_of_philo);
	union_info->time_to_start = ft_time();
	philo_id = -1;
	while (++philo_id < union_info->num_of_philo)
	{
		philo_info_arr[philo_id].union_info = union_info;
		philo_info_arr[philo_id].my_id = philo_id;
		philo_info_arr[philo_id].time_of_last_meal = union_info->time_to_start;
	}
	philo_id = -1;
	pthread_mutex_lock(&union_info->start_key);
	while (++philo_id < union_info->num_of_philo)
	{
		if (philo_id % 2 == 0)
			pthread_create(&union_info->philo_arr[philo_id], NULL, \
							func_even_philo_thread, &philo_info_arr[philo_id]);
		else
			pthread_create(&union_info->philo_arr[philo_id], NULL, \
							func_odd_philo_thread, &philo_info_arr[philo_id]);
	}
	return (philo_info_arr);
}

void	watcher(t_philo_info *philo_info, size_t num_of_philo)
{
	size_t			cur_time_in_ms;
	size_t			time_to_starve;
	size_t			time_to_die;
	int				philo_count;

	time_to_die = philo_info->union_info->time_to_die;
	while (1)
	{
		philo_count = -1;
		cur_time_in_ms = ft_time();
		while (++philo_count < num_of_philo)
		{
			time_to_starve = \
				cur_time_in_ms - (philo_info + philo_count)->time_of_last_meal;
			if (time_to_starve >= time_to_die)
			{
				philo_info->union_info->is_someone_dead = DEAD;
				philo_is_speaking(philo_info + philo_count, \
					cur_time_in_ms - philo_info->union_info->time_to_start, \
					"died", DEAD);
				return ;
			}
		}
	}
	return ;
}

int	main(int argc, char *argv[])
{
	t_union_info	union_info;
	t_philo_info	*t_philo_info_arr;
	int				philo_num;

	philo_num = -1;
	memset(&union_info, 0, sizeof(union_info));
	if (parsing_and_check_error(&union_info, argc, argv) == FALSE)
		ft_print_error(union_info.errnum);
	malloc_in_info(&union_info);
	t_philo_info_arr = make_philos(&union_info);
	watcher(t_philo_info_arr, union_info.num_of_philo);
	while (++philo_num < union_info.num_of_philo)
		pthread_join(union_info.philo_arr[philo_num], 0);
	// free_all_resource(&union_info);
	return (0);
}

// 천 ms == 1sec
// 1000 us(마이크로) =1ms