/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:22 by ealonso-          #+#    #+#             */
/*   Updated: 2022/08/01 13:57:26 by ealonso-         ###   ########.fr       */
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
	args->cutl = args->philos;
}

int	main(int argc, char **argv)
{
	t_args	*args;

	if (argc != 5 && argc != 6)
	{
		printf("\033[1;31mInvalid num of arguents\n");
		return (0);
	}
	args = (t_args *)malloc(sizeof(t_args));
	initargs(args, argc, argv);
}
