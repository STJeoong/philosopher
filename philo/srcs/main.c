/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:05:57 by tson              #+#    #+#             */
/*   Updated: 2022/11/27 14:05:58 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	main(int argc, char *argv[])
{
	t_program_arg	program_arg;
	t_thread_arg	*thread_args;

	memset(&program_arg, 0, sizeof(t_program_arg));
	if (is_correct_argv(argc, argv, &program_arg) == FALSE)
		return (0);
	thread_args = make_thread_args(program_arg);
	if (thread_args == NULL)
		return (0);
	sitdown_philosophers(thread_args);
	observe_philosophers(thread_args);
	return (0);
}
