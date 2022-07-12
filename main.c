/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 04:43:56 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/12 16:54:00 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	philo_id = 0;
	info->philo_arr = \
			(pthread_t **)malloc(sizeof(pthread_t *) * info->num_of_philo);
	while (philo_id != info->num_of_philo)
	{
		info->philo_arr[philo_id] = (pthread_t *)malloc(sizeof(pthread_t));
		philo_id++;
	}
	info->fork_arr = \
	(pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * info->num_of_philo);
	fork_id = 0;
	while (fork_id != info->num_of_philo)
	{
		info->fork_arr[fork_id] = \
				(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(info->fork_arr[fork_id], 0);
		fork_id++;
	}
	info->fork_status = (int *)malloc(sizeof(int) * info->num_of_philo);
	memset(info->fork_status, 0, sizeof(int) * info->num_of_philo);
}

void	free_union_info(t_union_info *info)
{
	size_t	philo_id;

	philo_id = 0;
	while (philo_id != info->num_of_philo)
	{
		free(info->philo_arr[philo_id]);
		philo_id++;
	}
	free(info->philo_arr);
	philo_id = 0;
	while (philo_id != info->num_of_philo)
	{
		free(info->fork_arr[philo_id]);
		philo_id++;
	}
	free(info->fork_arr);
	free(info->fork_status);
}

void	philo_is_speaking(t_philo_info *info, size_t time, char *str, int state)
{
	if (box_has_dead_flag(info->union_info, GET) && (state != DEAD))
	{
		pthread_mutex_unlock(&info->union_info->key_of_deadflag_box);
		return ;
	}
	pthread_mutex_unlock(&info->union_info->key_of_deadflag_box);
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
	while (!box_has_dead_flag(my_info->union_info, GET))
	{
		pthread_mutex_unlock(&my_info->union_info->key_of_deadflag_box);
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
	while (!box_has_dead_flag(my_info->union_info, GET))
	{
		pthread_mutex_unlock(&my_info->union_info->key_of_deadflag_box);
		get_my_left_fork(my_info);
		get_my_right_fork(my_info);
		philo_eat(my_info);
		philo_sleep(my_info);
		philo_think(my_info);
		// usleep(100);
	}
	return (0);
}

void	control_fork_status(t_union_info *union_info, int fork_num, int mode)
{
	pthread_mutex_lock(union_info->fork_arr[fork_num]);
	if (mode == LOCK)
		union_info->fork_status[fork_num] = LOCK;
	else if (mode == UNLOCK)
		union_info->fork_arr[fork_num] = UNLOCK;
	pthread_mutex_unlock(union_info->fork_arr[fork_num]);
}

size_t	timeval_to_ms(struct timeval time_t)
{
	return (time_t.tv_sec * 1000 + time_t.tv_usec / 1000);
}

t_philo_info	**make_philos(t_union_info *union_info, struct timeval time)
{
	t_philo_info	**philo_info_arr;
	int				philo_id;

	philo_info_arr = \
	(t_philo_info **)malloc(sizeof(t_philo_info *) * union_info->num_of_philo);
	philo_id = -1;
	while (++philo_id < union_info->num_of_philo)
	{
		philo_info_arr[philo_id] = (t_philo_info *)malloc(sizeof(t_philo_info));
		philo_info_arr[philo_id]->union_info = union_info;
		philo_info_arr[philo_id]->my_id = philo_id;
		philo_info_arr[philo_id]->time_of_last_meal = timeval_to_ms(time);
	}
	philo_id = -1;
	pthread_mutex_lock(&union_info->start_key);
	while (++philo_id < union_info->num_of_philo)
	{
		if (philo_id % 2 == 0)
			pthread_create(union_info->philo_arr[philo_id], NULL, \
							func_even_philo_thread, philo_info_arr[philo_id]);
		else
			pthread_create(union_info->philo_arr[philo_id], NULL, \
							func_odd_philo_thread, philo_info_arr[philo_id]);
	}
	return (philo_info_arr);
}

int	box_has_dead_flag(t_union_info *info, int getset_option)
{
	pthread_mutex_lock(&info->key_of_deadflag_box);
	if (getset_option == SET)
	{
		info->is_someone_dead = 1;
		pthread_mutex_unlock(&info->key_of_deadflag_box);
		return (DEAD);
	}
	else
	{
		// pthread_mutex_unlock(&info->key_of_deadflag_box);
		return (info->is_someone_dead);
	}
}

void	watcher(t_philo_info **philo_info, size_t num_of_philo)
{
	struct timeval	cur_time;
	size_t			cur_time_in_ms;
	size_t			time_to_starve;
	size_t			time_to_die;
	int				philo_count;

	time_to_die = philo_info[0]->union_info->time_to_die;
	while (1)
	{
		gettimeofday(&cur_time, NULL);
		cur_time_in_ms = timeval_to_ms(cur_time);
		philo_count = -1;
		while (++philo_count < num_of_philo)
		{
			time_to_starve = \
				cur_time_in_ms - philo_info[philo_count]->time_of_last_meal;
			if (time_to_starve >= time_to_die)
			{
				// pthread_mutex_lock(&(*philo_info)->union_info->key_of_deadflag_box);
				box_has_dead_flag((*philo_info)->union_info, SET);
				// pthread_mutex_unlock(&(*philo_info)->union_info->key_of_deadflag_box);
				philo_is_speaking(philo_info[philo_count], \
					cur_time_in_ms - philo_info[0]->union_info->time_to_start, \
					"died", DEAD);
				return ;
			}
		}
	}
	return ;
}

// void	free_all_resource(t_union_info *info)
// {
// 	int	arr_index;

// 	arr_index = -1;
// 	while (++arr_index < info->num_of_philo)
// 	{
// 		pthread_join(info->philo_arr[arr_index], 0);
// 		free(info->philo_arr[arr_index]);
// 	}
// 	free(info->philo_arr);
// 	arr_index = -1;
// 	free(info->fork_status);
// }

int	main(int argc, char *argv[])
{
	t_union_info	union_info;
	t_philo_info	**t_philo_info_arr;
	struct timeval	s_time;
	int				philo_num;

	philo_num = -1;
	memset(&union_info, 0, sizeof(union_info));
	if (parsing_and_check_error(&union_info, argc, argv) == FALSE)
		ft_print_error(union_info.errnum);
	malloc_in_info(&union_info);
	gettimeofday(&s_time, NULL);
	union_info.time_to_start = timeval_to_ms(s_time);
	t_philo_info_arr = make_philos(&union_info, s_time);
	watcher(t_philo_info_arr, union_info.num_of_philo);
	while (++philo_num < union_info.num_of_philo)
		pthread_join(*union_info.philo_arr[philo_num], 0);
	// free_all_resource(&union_info);

	return (0);
}

// 천 ms == 1sec
// 1000 us(마이크로) =1ms