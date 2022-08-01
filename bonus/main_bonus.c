/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:40:51 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/31 18:15:05 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	make_philos(t_union *info_union, t_philo *info_philo)
{
	int		count_philo;
	pid_t	pid;

	count_philo = -1;
	info_philo->info_union = info_union;
	info_union->time_to_start = get_cur_time() + 200;
	info_philo->time_of_last_meal = info_union->time_to_start;
	sem_wait(info_union->start_key);
	while (++count_philo < (int)info_union->num_of_philo)
	{
		pid = fork();
		if (pid == -1)
			ft_fork_error(info_union);
		else if (pid == 0)
		{
			info_philo->my_id = count_philo + 1;
			philo_process(info_philo);
		}
		info_union->philo_pid_arr[count_philo] = pid;
	}
	while (info_union->time_to_start > get_cur_time())
	{
	}
	sem_post(info_union->start_key);
}

void	init(t_union *info_union, t_philo *info_philo)
{
	memset(info_union, 0, sizeof(t_union));
	memset(info_philo, 0, sizeof(t_philo));
	sem_unlink("voice");
	sem_unlink("start_key");
	sem_unlink("forks_set");
	info_union->voice = sem_open("voice", O_CREAT, S_IRWXG, 1);
	info_union->start_key = sem_open("start_key", O_CREAT, S_IRWXG, 1);
	if (info_union->voice == SEM_FAILED || info_union->start_key == SEM_FAILED)
		ft_error(info_union);
	info_philo->info_union = info_union;
}

void	kill_all_philos(t_union *info_union)
{
	int	count_philo;

	count_philo = -1;
	while (++count_philo < (int)info_union->num_of_philo \
			&& info_union->philo_pid_arr[count_philo] != 0)
		kill(info_union->philo_pid_arr[count_philo], SIGKILL);
}

void	wait_for_philos(t_union *info_union)
{
	int	status;
	int	full_philo_count;

	full_philo_count = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		if (ft_wexitstatus(status) == DEAD)
			break ;
		else if (++full_philo_count == (int)info_union->num_of_philo)
		{
			printf("all philo is full\n");
			break ;
		}
	}
	kill_all_philos(info_union);
	sem_close(info_union->forks_set);
	sem_close(info_union->voice);
	sem_close(info_union->start_key);
}

int	main(int argc, char *argv[])
{
	t_union	info_union;
	t_philo	info_philo;

	init(&info_union, &info_philo);
	parsing(&info_union, argc, argv);
	init_after_parsing(&info_union, argc);
	make_philos(&info_union, &info_philo);
	wait_for_philos(&info_union);
	exit(0);
}
