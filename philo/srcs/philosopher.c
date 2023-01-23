/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:07:55 by tson              #+#    #+#             */
/*   Updated: 2022/12/19 23:07:56 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*t_main(void *arg)
{
	t_thread_arg	*thread_arg;

	thread_arg = (t_thread_arg *)arg;
	pthread_mutex_init(&(thread_arg->time_mutex), NULL);
	if (thread_arg->id % 2 == 0)
		usleep(thread_arg->program_arg.eat_time * 1000);
	while (TRUE)
	{
		eating(thread_arg);
		after_eating(thread_arg);
		sleeping(thread_arg);
		thinking(thread_arg);
	}
	return (NULL);
}

void	eating(t_thread_arg *thread_arg)
{
	int				p_num;
	int				id;

	p_num = thread_arg->program_arg.philosopher_num;
	id = thread_arg->id;
	pthread_mutex_lock(&(thread_arg->forks[id - 1]));
	print_message(thread_arg, FRK_MES);
	pthread_mutex_lock(&(thread_arg->forks[id % p_num]));
	print_message(thread_arg, FRK_MES);
	print_message(thread_arg, EAT_MES);
	pthread_mutex_lock(&(thread_arg->time_mutex));
	gettimeofday(&(thread_arg->last_eat_time), NULL);
	pthread_mutex_unlock(&(thread_arg->time_mutex));
	msleep(thread_arg->program_arg.eat_time);
}

void	after_eating(t_thread_arg *thread_arg)
{
	int	p_num;
	int	id;
	int	min_eat;

	p_num = thread_arg->program_arg.philosopher_num;
	id = thread_arg->id;
	min_eat = thread_arg->program_arg.min_num_of_eat;
	pthread_mutex_unlock(&(thread_arg->forks[id - 1]));
	pthread_mutex_unlock(&(thread_arg->forks[id % p_num]));
	(thread_arg->eat_count)++;
	if (min_eat != 0 && thread_arg->eat_count >= min_eat)
		thread_arg->is_all_eat = TRUE;
}

void	sleeping(t_thread_arg *thread_arg)
{
	print_message(thread_arg, SLP_MES);
	msleep(thread_arg->program_arg.slp_time);
}

void	thinking(t_thread_arg *thread_arg)
{
	print_message(thread_arg, THK_MES);
}
