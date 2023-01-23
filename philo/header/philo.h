/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:06:07 by tson              #+#    #+#             */
/*   Updated: 2022/11/27 14:06:08 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define ATOI_FAIL -1
# define CREATE_MUTEX_ERROR 0
# define CREATE_MUTEX_SUCCESS 1
# define SETTING_FAIL 0
# define SETTING_SUCCESS 1
# define FRK_MES "has taken a fork"
# define EAT_MES "is eating"
# define SLP_MES "is sleeping"
# define THK_MES "is thinking"
# define DIE_MES "died"

typedef struct s_program_arg
{
	int	philosopher_num;
	int	die_time;
	int	eat_time;
	int	slp_time;
	int	min_num_of_eat;
}	t_program_arg;

typedef struct s_thread_arg
{
	int				id;
	int				is_die;
	int				is_all_eat;
	t_program_arg	program_arg;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	time_mutex;
	struct timeval	start_time;
	struct timeval	last_eat_time;
	int				eat_count;
}	t_thread_arg;

void			sitdown_philosophers(t_thread_arg *thread_args);
t_thread_arg	*make_thread_args(t_program_arg program_arg);
pthread_mutex_t	*make_forks(t_program_arg program_arg);
int				put_datas(t_thread_arg *thread_args,
					pthread_mutex_t *forks, t_program_arg program_arg);
long long		get_time_gap_ms(struct timeval start, struct timeval cur);
int				ft_atoi(char *str);
int				is_correct_argv(int argc, char *argv[],
					t_program_arg *program_arg);
void			*t_main(void *arg);
void			eating(t_thread_arg *thread_arg);
void			after_eating(t_thread_arg *thread_arg);
void			sleeping(t_thread_arg *thread_arg);
void			thinking(t_thread_arg *thread_arg);
void			*is_over_die_time(void *arg);
void			msleep(int seconds);
void			print_message(t_thread_arg *thread_arg, char *message);
void			observe_philosophers(t_thread_arg *thread_args);
int				is_anyone_die(t_thread_arg *thread_args);
int				is_everyone_eat(t_thread_arg *thread_args);
#endif
