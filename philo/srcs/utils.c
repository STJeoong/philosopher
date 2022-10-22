/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:07:53 by tson              #+#    #+#             */
/*   Updated: 2022/10/21 15:08:03 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long	get_time_gap(struct timeval start, struct timeval now)
{
	long	ret;

	ret = (now.tv_sec - start.tv_sec) * 1000000
		+ (now.tv_usec - start.tv_usec);
	return (ret);
}

int	ft_atoi(char *str) // INT_MAX보다 크거나 숫자가 아닌 값이 들어오면 -1반환
{
	int		idx;
	long	val;

	idx = 0;
	val = 0;
	while (str[idx])
	{
		if (!(str[idx] >= '0' && str[idx] <= '9'))
			return (-1);
		val *= 10;
		val += str[idx] - '0';
		if (val >= INT_MAX)
			return (-1);
		idx++;
	}
	return ((int)val);
}

t_arg	*make_args(t_pub *p_pub)
{
	int		i;
	t_arg	*ret;

	ret = malloc(sizeof(t_arg) * (p_pub->info).num_of_philo);
	if (ret == NULL)
		return (0);
	i = 0;
	while (i < (p_pub->info).num_of_philo)
	{
		ret[i].p_pub = p_pub;
		ret[i].philosopher_num = i;
		ret[i].last_eat_time = (p_pub->info).start_time;
		pthread_mutex_init(&ret[i].mutex_time, NULL);
		i++;
	}
	return (ret);
}
