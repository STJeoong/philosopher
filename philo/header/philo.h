/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:39:20 by tson              #+#    #+#             */
/*   Updated: 2022/10/21 15:18:52 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat; // 이 값이 -1이 아니면 5번째 인자값이 주어진거임
	struct timeval	start_time;
	int				eat; // 비트마스킹으로 각각의 쓰레드넘버의 비트위치를 켜기
	int				state;
}	t_info;
typedef struct s_mutexs
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	state;
	pthread_mutex_t	eat; // 다 먹었는지 (죽은게 아니라)
	pthread_mutex_t	printf;
}	t_mutexs;
typedef struct s_pub
{
	t_info		info;
	t_mutexs	mutex;
}	t_pub;
typedef struct s_arg
{
	t_pub			*p_pub;
	int				philosopher_num;
	struct timeval	last_eat_time;
	pthread_mutex_t	mutex_time;
}	t_arg;

void	check_philosophers_state(t_pub *p_pub);
int		is_all_eat(t_pub *p_pub);
int		is_anyone_die(t_pub *p_pub);
int		set_pub(t_pub *p_pub, int argc, char *argv[]);
int		set_info(t_info *p_info, int argc, char *argv[]);
int		set_mutex(t_mutexs *p_mutexs, int num_of_philo);
int		make_philosophers(t_pub *p_pub, t_arg *p_arg);
long	get_time_gap(struct timeval start, struct timeval now);
int		ft_atoi(char *str);
t_arg	*make_args(t_pub *p_pub);
void	*t_main(void *arg);
void	make_taking_fork_thread(t_arg *p_arg);
void	*take_left_fork(void *arg);
void	*take_right_fork(void *arg);
void	*is_over_die_time(void *arg);
#endif
