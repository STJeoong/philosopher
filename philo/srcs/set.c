/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:52:20 by tson              #+#    #+#             */
/*   Updated: 2022/10/21 15:18:26 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	set_pub(t_pub *p_pub, int argc, char *argv[])
{
	if (set_info(&p_pub->info, argc, argv) == 0)
		return (0);
	if (set_mutex(&p_pub->mutex, (p_pub->info).num_of_philo) == 0)
		return (0);
	return (1);
}

int	set_info(t_info *p_info, int argc, char *argv[])
{
	p_info->num_of_philo = ft_atoi(argv[1]);
	if (p_info->num_of_philo == -1)
		return (0);
	p_info->time_to_die = ft_atoi(argv[2]);
	if (p_info->time_to_die == -1)
		return (0);
	p_info->time_to_eat = ft_atoi(argv[3]);
	if (p_info->time_to_eat == -1)
		return (0);
	p_info->time_to_sleep = ft_atoi(argv[4]);
	if (p_info->time_to_sleep == -1)
		return (0);
	p_info->num_of_must_eat = -1;
	if (argc == 6)
	{
		p_info->num_of_must_eat = ft_atoi(argv[5]);
		if (p_info->num_of_must_eat == -1)
			return (0);
	}
	if (gettimeofday(&(p_info->start_time), NULL) == -1)
		return (0);
	p_info->eat = 0;
	p_info->state = -1;
	return (1);
}

int	set_mutex(t_mutexs *p_mutexs, int num_of_philo)
{
	int	i;

	p_mutexs->forks = malloc(sizeof(pthread_mutex_t) * num_of_philo);
	if (p_mutexs->forks == NULL)
		return (0);
	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_init(&(p_mutexs->forks)[i], NULL);
		i++;
	}
	pthread_mutex_init(&(p_mutexs->state), NULL);
	pthread_mutex_init(&(p_mutexs->eat), NULL);
	pthread_mutex_init(&(p_mutexs->printf), NULL);
	return (1);
}

int	make_philosophers(t_pub *p_pub, t_arg *p_arg)
{
	pthread_t	t_id;
	int			i;

	i = 0;
	p_arg = make_args(p_pub);
	if (p_arg == NULL)
		return (0);
	while (i < (p_pub->info).num_of_philo)
	{
		pthread_create(&t_id, NULL, t_main, (void *)&p_arg[i]);
		pthread_detach(t_id);
		i++;
	}
	return (1);
}
