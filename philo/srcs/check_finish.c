/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:56:41 by tson              #+#    #+#             */
/*   Updated: 2022/10/21 15:14:42 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	check_philosophers_state(t_pub *p_pub)
{
	while (1)
	{
		if ((p_pub->info).num_of_must_eat != -1)
			if (is_all_eat(p_pub) == 1)
				return ;
		if (is_anyone_die(p_pub) == 1)
			return ;
	}
}

int	is_all_eat(t_pub *p_pub)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(p_pub->mutex).eat);
	while (i < (p_pub->info).num_of_philo)
	{
		if (!((p_pub->info).eat & (1 << i)))
			return (0);
		i++;
	}
	pthread_mutex_unlock(&(p_pub->mutex).eat);
	return (1);
}

int	is_anyone_die(t_pub *p_pub)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(p_pub->mutex).state);
	if ((p_pub->info).state != -1)
		ret = 1;
	pthread_mutex_unlock(&(p_pub->mutex).state);
	return (ret);
}
