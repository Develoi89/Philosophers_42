/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:22 by ealonso-          #+#    #+#             */
/*   Updated: 2022/08/01 13:04:07 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static void	initargs(t_args *args, int argc, char **argv)
{
	args->philos = atoi(argv[1]);
	args->tte = atoi(argv[3]);
	args->ttd = atoi(argv[2]);
	args->tts = atoi(argv[4]);
	if (argc == 6)
		args->limiteat = atoi(argv[5]);
	printf("time to die = %d", args->ttd);
}

int	main(int argc, char **argv)
{
	t_args	args;

	initargs(&args, argc, argv);
}
