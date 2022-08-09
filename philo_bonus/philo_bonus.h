/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:41:55 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/10 03:03:35 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <string.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define INT_MAX 2147483647
# define LOCK 1
# define UNLOCK 0
# define GET 42
# define SET 24

typedef struct s_union
{
	int				stop_eating;
	int				has_optional_arg;
	int				is_someone_dead;
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_start;
	size_t			num_each_philo_must_eat;
	sem_t			*forks_set;
	sem_t			*voice;
	sem_t			*start_key;
	sem_t			*full_count;
	sem_t			*dead_flag;
	sem_t			*end_game;
	sem_t			*is_dead_status;
	pid_t			*philo_pid_arr;
}	t_union;

typedef struct s_philo
{
	size_t			my_id;
	size_t			time_of_last_meal;
	int				eat_count;
	sem_t			**sem_each_philo_time_last_meal;
	sem_t			**sem_eat_count;
	t_union			*info_union;
}	t_philo;

// main_bonus.c
void	kill_all_philos(t_union *info_union);

//parsing_bonus.c
void	parsing(t_union *info_union, int argc, char **argv);
void	init_after_parsing(t_union *info_union, t_philo *info_philo, int argc);
void	make_my_philo_sem(t_philo *info_union);

//philo_behave_bonus.c
void	philo_is_speaking(t_philo *info_philo, char *message);
void	pick_up_forks(t_philo *info_philo);
void	philo_eat(t_philo *info_philo);
void	philo_sleep(t_philo *info_philo);
void	philo_think(t_philo *info_philo);

//util_bonus.c
size_t	ft_atoul_check_range(char *str);
void	ft_error(t_union *info_union, t_philo *info_philo);
size_t	get_cur_time(void);
size_t	get_time_stamp(t_union *info_union);

//util2_bonus.c
int		paras_is_in_valid_range(t_union *info_union);
void	*ft_calloc(size_t size);
void	ft_fork_error(t_union *info_union, t_philo *info_philo);
void	close_philo_sem(t_philo *info_philo);
void	close_union_sem(t_union *info_union);

//philo_bonus.c
void	philo_process(t_philo *info_philo);

//philo_eat_func.c
void	philo_eat_with_no_option(t_philo *info_philo);
void	philo_eat_with_option(t_philo *info_philo);

//watcher_bonus.c
void	*f_watcher_is_all_full(void	*union_para);
void	*f_watcher_is_someone_dead(void *union_para);

//libft
char	*ft_itoa(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

#endif
