/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:42:14 by tson              #+#    #+#             */
/*   Updated: 2022/10/21 15:51:34 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	main(int argc, char *argv[])
{
	t_pub	public;
	t_arg	arg;

	memset(&public, 0, sizeof(t_pub));
	if (argc != 5 && argc != 6)
		return (0);
	if (set_pub(&public, argc, argv) == 0)
		return (0);
	if (make_philosophers(&public, &arg) == 0)
		return (0);
	check_philosophers_state(&public);
	while (1);
	return (0);
}
