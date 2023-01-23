/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:39:38 by tson              #+#    #+#             */
/*   Updated: 2022/11/27 17:39:39 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long long	get_time_gap_ms(struct timeval start, struct timeval cur)
{
	long long	ret;

	ret = (cur.tv_usec - start.tv_usec) / 1000
		+ (cur.tv_sec - start.tv_sec) * 1000;
	return (ret);
}

int	ft_atoi(char *str)
{
	int		idx;
	long	ret;

	idx = 0;
	ret = 0;
	while (str[idx])
	{
		if (!(str[idx] >= '0' && str[idx] <= '9'))
			return (ATOI_FAIL);
		ret *= 10;
		ret += str[idx] - '0';
		if (ret > INT32_MAX)
			return (ATOI_FAIL);
		idx++;
	}
	return ((int)ret);
}

int	is_correct_argv(int argc, char *argv[], t_program_arg *program_arg)
{
	if (argc != 5 && argc != 6)
		return (FALSE);
	(*program_arg).philosopher_num = ft_atoi(argv[1]);
	(*program_arg).die_time = ft_atoi(argv[2]);
	(*program_arg).eat_time = ft_atoi(argv[3]);
	(*program_arg).slp_time = ft_atoi(argv[4]);
	if (argc == 6)
		(*program_arg).min_num_of_eat = ft_atoi(argv[5]);
	if ((*program_arg).philosopher_num == ATOI_FAIL
		|| (*program_arg).die_time == ATOI_FAIL
		|| (*program_arg).eat_time == ATOI_FAIL
		|| (*program_arg).slp_time == ATOI_FAIL
		|| (*program_arg).min_num_of_eat == ATOI_FAIL)
		return (FALSE);
	return (TRUE);
}

void	msleep(int seconds)
{
	struct timeval	start_time;
	struct timeval	cur_time;

	gettimeofday(&start_time, NULL);
	while (TRUE)
	{
		gettimeofday(&cur_time, NULL);
		if (get_time_gap_ms(start_time, cur_time) >= seconds)
			return ;
		usleep(100);
	}
}

void	print_message(t_thread_arg *thread_arg, char *message)
{
	struct timeval	cur_time;
	long long		time_gap;

	pthread_mutex_lock(thread_arg->print_mutex);
	gettimeofday(&cur_time, NULL);
	time_gap = get_time_gap_ms(thread_arg->start_time, cur_time);
	printf("%lld %d %s\n", time_gap, thread_arg->id, message);
	pthread_mutex_unlock(thread_arg->print_mutex);
}
