/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:41:55 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/14 01:44:46 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define INT_MAX 2147483647

typedef struct s_union
{
	int				is_someone_dead;// = 0
	size_t			num_of_philo;// =num
	size_t			time_to_die;// = num
	size_t			time_to_eat;//=num
	size_t			time_to_sleep;//=num
	size_t			time_to_start;
	size_t			num_each_philo_must_eat; //num
	int				*fork_status; // calloced
	pthread_t		**philo_arr; // malloced
	pthread_mutex_t	**fork_arr; // malloced
	pthread_mutex_t	voice;
	pthread_mutex_t	start_key;
	pthread_mutex_t	key_of_deadflag_box;
}	t_union;

typedef struct s_philo
{
	size_t			my_id;
	size_t			time_of_last_meal;
	int				right_fork_id;
	int				left_fork_id;
	t_union	*info_union;

}	t_philo;


// main.c

//parsing.c
int	parsing(t_union *info_union, int argc, char **argv);

//util.c
size_t	ft_atoul_check_range(char *str);
int		ft_error(void);
size_t	get_cur_time(void);
size_t	ft_time_diff(size_t time1, size_t time2);

//util2.c
int	 paras_is_in_valid_range(t_union *info_union, int argc);
void	*ft_calloc(size_t size);

#endif
