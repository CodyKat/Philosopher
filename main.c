/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 04:43:56 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/09 17:16:54 by jaemjeon         ###   ########.fr       */
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
	info->philo_arr = (pthread_t **)malloc(sizeof(pthread_t *) * \
												info->num_of_philo);
	while (philo_id != info->num_of_philo)
	{
		info->philo_arr[philo_id] = (pthread_t *)malloc(sizeof(pthread_t));
		philo_id++;
	}
	info->fork_arr = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * \
												info->num_of_philo);
	fork_id = 0;
	while (fork_id != info->num_of_philo)
	{
		info->fork_arr[fork_id] = \
				(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
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

void	*func_philo_thread(void *my_philo_info)
{
	static t_philo_info	*my_info;

	my_info = (t_philo_info *)my_philo_info;
	while (1)
	{
		printf("hello my id is :%d\n", my_info->my_id);
		sleep(1);
	}
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

void	make_philos_and_create_pthreads(t_union_info *union_info)
{
	t_philo_info	**philo_info_arr;
	int				philo_id;

	philo_info_arr = (t_philo_info **)malloc(sizeof(t_philo_info *) * \
													union_info->num_of_philo);
	philo_id = 0;
	while (philo_id < union_info->num_of_philo)
	{
		philo_info_arr[philo_id] = (t_philo_info *)malloc(sizeof(t_philo_info));
		philo_info_arr[philo_id]->union_info = union_info;
		philo_info_arr[philo_id]->my_id = philo_id;
		philo_id++;
	}
	philo_id = 0;
	while (philo_id < union_info->num_of_philo)
	{
		pthread_create(union_info->philo_arr[philo_id], NULL, \
						func_philo_thread, philo_info_arr[philo_id]);
		philo_id++;
	}
}

int	main(int argc, char *argv[])
{
	t_union_info	union_info;
	t_philo_info	**t_philo_info_arr;
	struct timeval	s_time;

	memset(&union_info, 0, sizeof(union_info));
	if (parsing_and_check_error(&union_info, argc, argv) == FALSE)
		ft_print_error(union_info.errnum);
	malloc_in_info(&union_info);
	gettimeofday(&s_time, NULL);
	union_info.time_to_start = timeval_to_ms(s_time);
	make_philos_and_create_pthreads(&union_info);
}

// 천 ms == 1sec
// 1000 us(마이크로) =1ms