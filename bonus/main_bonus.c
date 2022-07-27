/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:40:51 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/27 17:49:55 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_full_wait_process(t_philo *info_philo)
{
	sleep(2147483647);
}

void	make_philos(t_union *info_union, t_philo *info_philo)
{
	int		count_philo;
	pid_t	pid;

	count_philo = -1;
	info_philo->info_union = info_union;
	if (info_union->forks_set == SEM_FAILED \
		|| info_union->full_count == SEM_FAILED)
		ft_error();
	sem_wait(info_union->start_key);
	info_union->time_to_start = get_cur_time();
	while (++count_philo < info_union->num_of_philo)
	{
		pid = fork();
		info_union->philo_pid_arr[count_philo] = pid;
		if (pid == 0)
		{
			info_philo->my_id = count_philo / 2;
			if (count_philo % 2 == 0)
				philo_process(info_philo);
			else
				philo_full_wait_process(info_philo);
		}
	}
	sem_post(info_union->start_key);
}

void	init(t_union *info_union, t_philo *info_philo)
{
	memset(info_union, 0, sizeof(t_union));
	memset(info_philo, 0, sizeof(t_philo));
	sem_unlink("voice");
	sem_unlink("dead");
	sem_unlink("start_key");
	sem_unlink("forks_set");
	info_union->voice = sem_open("voice", O_CREAT, 0644, 1);
	info_union->dead = sem_open("dead", O_CREAT, 0644, 1);
	info_union->start_key = sem_open("start_key", O_CREAT, 0644, 1);
	if (info_union->voice == SEM_FAILED || info_union->dead == SEM_FAILED
		|| info_union->start_key == SEM_FAILED)
		ft_error();
}

void	kill_all_philos(t_union *info_union)
{
	int	count_philo;

	count_philo = -1;
	while (++count_philo < info_union->num_of_philo)
		kill(info_union->philo_pid_arr[count_philo], SIGKILL);
}

void	wait_for_philos(t_union *info_union)
{
	int		status;
	int		full_philo_count;

	full_philo_count = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DEAD)
		{
			kill_all_philos(info_union);
			return ;
		}
		else
		{
			if (++full_philo_count == info_union->num_of_philo)
				break ;
		}
	}
	printf("%zu %s\n", get_time_stamp(info_union), "all philo is full");
	kill_all_philos(info_union);
	return ;
}

int	main(int argc, char *argv[])
{
	t_union	info_union;
	t_philo	info_philo_arr;
	int		n_philo;

	init(&info_union, &info_philo_arr);
	parsing(&info_union, argc, argv);
	info_union.forks_set = sem_open("forks_set", O_CREAT, 0644, \
												info_union.num_of_philo / 2);
	make_philos(&info_union, &info_philo_arr);
	wait_for_philos(&info_union);
	sem_close(info_union.forks_set);
	sem_close(info_union.voice);
	sem_close(info_union.dead);
	sem_close(info_union.start_key);
	exit(0);
}
