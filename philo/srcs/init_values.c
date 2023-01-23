/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:30:01 by tson              #+#    #+#             */
/*   Updated: 2022/12/20 19:30:01 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	sitdown_philosophers(t_thread_arg *thread_args)
{
	pthread_t		th;
	int				i;

	i = 0;
	while (i < thread_args->program_arg.philosopher_num)
	{
		pthread_create(&th, NULL, t_main, (void *)&thread_args[i]);
		pthread_detach(th);
		i++;
	}
}

t_thread_arg	*make_thread_args(t_program_arg program_arg)
{
	t_thread_arg	*ret;
	pthread_mutex_t	*forks;

	ret = malloc(sizeof(t_thread_arg) * program_arg.philosopher_num);
	forks = make_forks(program_arg);
	if (ret == NULL || forks == NULL)
	{
		free(ret);
		free(forks);
		return (NULL);
	}
	if (put_datas(ret, forks, program_arg) == SETTING_FAIL)
	{
		free(ret);
		free(forks);
		return (NULL);
	}
	return (ret);
}

pthread_mutex_t	*make_forks(t_program_arg program_arg)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * program_arg.philosopher_num);
	if (forks == NULL)
		return (forks);
	i = 0;
	while (i < program_arg.philosopher_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	put_datas(t_thread_arg *thread_args,
					pthread_mutex_t *forks,	t_program_arg program_arg)
{
	pthread_mutex_t	*print_mutex;
	struct timeval	start_time;
	int				i;

	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (print_mutex == NULL)
		return (SETTING_FAIL);
	pthread_mutex_init(print_mutex, NULL);
	gettimeofday(&start_time, NULL);
	i = 0;
	while (i < program_arg.philosopher_num)
	{
		memset(&thread_args[i], 0, sizeof(t_thread_arg));
		thread_args[i].id = i + 1;
		thread_args[i].program_arg = program_arg;
		thread_args[i].forks = forks;
		thread_args[i].print_mutex = print_mutex;
		thread_args[i].start_time = start_time;
		thread_args[i].last_eat_time = start_time;
		i++;
	}
	return (SETTING_SUCCESS);
}
