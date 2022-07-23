/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:40:51 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/23 02:41:55 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	make_philos(t_union *info_union, t_philo *info_philo)
{
	int		count_philo;
	pid_t	pid;

	count_philo = -1;
	info_philo->info_union = info_union;
	sem_unlink("forks_set");
	sem_unlink("full_count");
	info_union->forks_set = sem_open("forks_set", O_CREAT, 0644, \
												info_union->num_of_philo);
	info_union->full_count = sem_open("full_count", O_CREAT, 0644, \
												info_union->full_count);
	if (info_union->forks_set == SEM_FAILED || info_union->full_count == SEM_FAILED)
		ft_error();
	sem_wait(info_union->start_key);
	info_union->time_to_start = get_cur_time();
	info_philo->time_of_last_meal = info_union->time_to_start;
	while (++count_philo < info_union->num_of_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			info_philo->my_id = count_philo;
			philo_process(info_philo);
		}
		info_union->philo_id_arr[count_philo] = pid;
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
	info_union->voice = sem_open("voice", O_CREAT, 0644, 1);
	info_union->dead = sem_open("dead", O_CREAT, 0644, 1);
	info_union->start_key = sem_open("start_key", O_CREAT, 0644, 1);
	if (info_union->voice == SEM_FAILED || info_union->dead == SEM_FAILED ||
		info_union->start_key == SEM_FAILED)
		ft_error();
}

void	kill_all_philos(t_union *info_union)
{
	int	count_philo;

	count_philo = -1;
	while (++count_philo < info_union->num_of_philo)
		kill(info_union->philo_id_arr[count_philo], SIGKILL);
}

void	wait_for_philos(t_union *info_union)
{
	int		count_philo;
	int		status;
	int		full_philo_count;

	full_philo_count = 0;
	count_philo = -1;
	while (++count_philo < info_union->num_of_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DEAD)
		{
			kill_all_philos(info_union);
			printf("%zu %d %s\n", \
							get_time_stamp(info_union), count_philo, "is died");
			return ;
		}
		else if (WEXITSTATUS(status) == FULL)
			full_philo_count++;
	}
	kill_all_philos(info_union);
	printf("%zu %s\n", get_time_stamp(info_union), "all philo is full");
	return ;
}

int	main(int argc, char *argv[])
{
	t_union	info_union;
	t_philo	info_philo_arr;
	int		n_philo;

	init(&info_union, &info_philo_arr);
	parsing(&info_union, argc, argv);
	make_philos(&info_union, &info_philo_arr);
	wait_for_philos(&info_union);
	sem_close(info_union.forks_set);
	sem_close(info_union.dead);
	sem_close(info_union.start_key);
	sem_close(info_union.full_count);
	exit(0);
}
