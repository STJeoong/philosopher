/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 00:52:26 by tson              #+#    #+#             */
/*   Updated: 2022/12/21 00:52:26 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	observe_philosophers(t_thread_arg *thread_args)
{
	while (TRUE)
	{
		if (is_anyone_die(thread_args) == TRUE)
			return ;
		if (is_everyone_eat(thread_args) == TRUE)
			return ;
	}
}

int	is_anyone_die(t_thread_arg *thread_args)
{
	struct timeval	cur_time;
	int				i;
	long long		time_gap;

	i = 0;
	while (i < thread_args[0].program_arg.philosopher_num)
	{
		gettimeofday(&cur_time, NULL);
		pthread_mutex_lock(&thread_args[i].time_mutex);
		time_gap = get_time_gap_ms(thread_args[i].last_eat_time, cur_time);
		pthread_mutex_unlock(&thread_args[i].time_mutex);
		if (time_gap >= thread_args[i].program_arg.die_time)
		{
			print_message(&thread_args[i], DIE_MES);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	is_everyone_eat(t_thread_arg *thread_args)
{
	int	i;

	i = 0;
	while (i < thread_args[0].program_arg.philosopher_num)
	{
		if (thread_args[i].is_all_eat == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	*is_over_die_time(void *arg)
{
	struct timeval	cur_time;
	t_thread_arg	*thread_arg;
	long long		time_gap;

	thread_arg = (t_thread_arg *)arg;
	while (TRUE)
	{
		gettimeofday(&cur_time, NULL);
		pthread_mutex_lock(&(thread_arg->time_mutex));
		time_gap = get_time_gap_ms(thread_arg->last_eat_time, cur_time);
		pthread_mutex_unlock(&(thread_arg->time_mutex));
		if (time_gap >= thread_arg->program_arg.die_time)
		{
			thread_arg->is_die = TRUE;
			time_gap = get_time_gap_ms(thread_arg->start_time, cur_time);
			printf("%lld %d %s\n", time_gap, thread_arg->id, DIE_MES);
			return (NULL);
		}
	}
	return (NULL);
}
