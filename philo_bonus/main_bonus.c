/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:40:51 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/13 12:32:44 by jaemjeon         ###   ########.fr       */
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
			ft_fork_error(info_union, info_philo);
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
	t_union	*info_u;

	info_u = info_union;
	sem_unlink("voice");
	sem_unlink("start_key");
	sem_unlink("forks_set");
	sem_unlink("full_count");
	sem_unlink("dead_flag");
	sem_unlink("end_game");
	sem_unlink("sem_is_someone_dead");
	sem_unlink("sem_can_get_forks");
	info_u->voice = sem_open("voice", O_CREAT, S_IRWXG, 1);
	info_u->start_key = sem_open("start_key", O_CREAT, S_IRWXG, 1);
	info_u->full_count = sem_open("full_count", O_CREAT, S_IRWXG, 0);
	info_u->dead_flag = sem_open("dead_flag", O_CREAT, S_IRWXG, 0);
	info_u->end_game = sem_open("end_game", O_CREAT, S_IRWXU, 0);
	info_u->sem_is_someone_dead = \
						sem_open("sem_is_someone_dead", O_CREAT, S_IRWXU, 1);
	if (info_u->voice == SEM_FAILED || info_u->start_key == SEM_FAILED \
	|| info_u->full_count == SEM_FAILED || info_u->dead_flag == SEM_FAILED \
	|| info_u->end_game == SEM_FAILED \
	|| info_u->sem_is_someone_dead == SEM_FAILED)
		ft_error(info_u, NULL);
	info_philo->info_union = info_u;
}

void	kill_all_philos(t_union *info_union)
{
	int	count_philo;

	count_philo = -1;
	while (++count_philo < (int)info_union->num_of_philo \
			&& info_union->philo_pid_arr[count_philo] != 0)
		kill(info_union->philo_pid_arr[count_philo], SIGKILL);
}

void	wait_for_philos(t_union *info_union, t_philo *info_philo)
{
	pthread_t	watcher_is_all_full;
	pthread_t	watcher_is_someone_dead;

	pthread_create(&watcher_is_all_full, NULL, \
							f_watcher_is_all_full, info_union);
	pthread_create(&watcher_is_someone_dead, NULL, \
							f_watcher_is_someone_dead, info_union);
	pthread_detach(watcher_is_all_full);
	pthread_detach(watcher_is_someone_dead);
	sem_wait(info_union->end_game);
	kill_all_philos(info_union);
	close_union_sem(info_union);
	close_philo_sem(info_philo);
}

int	main(int argc, char *argv[])
{
	t_union	info_union;
	t_philo	info_philo;

	memset(&info_union, 0, sizeof(t_union));
	memset(&info_philo, 0, sizeof(t_philo));
	init(&info_union, &info_philo);
	parsing(&info_union, argc, argv);
	init_after_parsing(&info_union, &info_philo, argc);
	make_philos(&info_union, &info_philo);
	wait_for_philos(&info_union, &info_philo);
	exit(0);
}
