/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:08:07 by tson              #+#    #+#             */
/*   Updated: 2022/10/21 15:15:04 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*t_main(void *arg)
{
	pthread_t		t;
	long			from_start;
	struct timeval	cur_time;
	t_arg			*p_arg;

	p_arg = (t_arg *)arg;
	pthread_create(&t, NULL, is_over_die_time, arg);
	pthread_detach(t);
	while (1)
	{
		make_taking_fork_thread((t_arg *)arg);
		gettimeofday(&cur_time, NULL);
		from_start = get_time_gap((p_arg->p_pub->info).start_time, cur_time);
		pthread_mutex_lock(&(p_arg->p_pub->mutex).printf);
		printf("%ld %d is thinking\n", from_start, p_arg->philosopher_num);
		pthread_mutex_unlock(&(p_arg->p_pub->mutex).printf);
	}
	return (NULL);
}

void	make_taking_fork_thread(t_arg *p_arg)
{
	pthread_t		t1;
	pthread_t		t2;
	struct timeval	cur_time;
	long			from_start;

	pthread_create(&t1, NULL, take_left_fork, (void *)p_arg);
	pthread_create(&t2, NULL, take_right_fork, (void *)p_arg);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	gettimeofday(&cur_time, NULL);
	from_start = get_time_gap((p_arg->p_pub->info).start_time, cur_time);
	pthread_mutex_lock(&(p_arg->p_pub->mutex).printf);
	printf("%ld %d is eating\n", from_start, p_arg->philosopher_num);
	pthread_mutex_unlock(&(p_arg->p_pub->mutex).printf);
	usleep((p_arg->p_pub->info).time_to_eat);
	pthread_mutex_unlock(&(p_arg->p_pub->mutex).forks[p_arg->philosopher_num]);
	pthread_mutex_unlock(&(p_arg->p_pub->mutex).forks[(p_arg->philosopher_num + 1) % (p_arg->p_pub->info).num_of_philo]);
	gettimeofday(&cur_time, NULL);
	from_start = get_time_gap((p_arg->p_pub->info).start_time, cur_time);
	pthread_mutex_lock(&(p_arg->p_pub->mutex).printf);
	printf("%ld %d is sleeping\n", from_start, p_arg->philosopher_num);
	pthread_mutex_unlock(&(p_arg->p_pub->mutex).printf);
	usleep((p_arg->p_pub->info).time_to_sleep);
}

void	*take_left_fork(void *arg)
{
	struct timeval	cur_time;
	long			from_start;
	t_arg			*p_arg;

	p_arg = (t_arg *)arg;
	pthread_mutex_lock(&(p_arg->p_pub->mutex).forks[p_arg->philosopher_num]);
	gettimeofday(&cur_time, NULL);
	from_start = get_time_gap((p_arg->p_pub->info).start_time, cur_time);
	pthread_mutex_lock(&(p_arg->p_pub->mutex).printf);
	printf("%ld %d has taken a fork\n", from_start, p_arg->philosopher_num);
	pthread_mutex_unlock(&(p_arg->p_pub->mutex).printf);
	return (NULL);
}

void	*take_right_fork(void *arg)
{
	struct timeval	cur_time;
	long			from_start;
	t_arg			*p_arg;

	p_arg = (t_arg *)arg;
	pthread_mutex_lock(&(p_arg->p_pub->mutex).forks[(p_arg->philosopher_num + 1) % (p_arg->p_pub->info).num_of_philo]);
	gettimeofday(&cur_time, NULL);
	from_start = get_time_gap((p_arg->p_pub->info).start_time, cur_time);
	pthread_mutex_lock(&(p_arg->p_pub->mutex).printf);
	printf("%ld %d has taken a fork\n", from_start, p_arg->philosopher_num);
	pthread_mutex_unlock(&(p_arg->p_pub->mutex).printf);
	return (NULL);
}

void	*is_over_die_time(void *arg)
{
	struct timeval	cur_time;
	long			from_start;
	long			time_gap;
	t_arg			*p_arg;

	p_arg = (t_arg *)arg;
	while (1)
	{
		gettimeofday(&cur_time, NULL);
		pthread_mutex_lock(&(p_arg->mutex_time));
		time_gap = get_time_gap(p_arg->last_eat_time, cur_time);
		pthread_mutex_unlock(&(p_arg->mutex_time));
		from_start = get_time_gap((p_arg->p_pub->info).start_time, cur_time);
		if (time_gap >= (p_arg->p_pub->info).time_to_die)
		{
			pthread_mutex_lock(&(p_arg->p_pub->mutex).printf);
			printf("%ld %d died\n", from_start, p_arg->philosopher_num);
			pthread_mutex_lock(&(p_arg->p_pub->mutex).state);
			(p_arg->p_pub->info).state = p_arg->philosopher_num;
			pthread_mutex_unlock(&(p_arg->p_pub->mutex).state);
			pthread_mutex_unlock(&(p_arg->p_pub->mutex).printf);
			return (NULL);
		}
	}
	return (NULL);
}
