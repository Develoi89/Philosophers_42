/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:22 by ealonso-          #+#    #+#             */
/*   Updated: 2022/08/02 12:30:18 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static int	initphilos(t_vars *vars, int argc)
{
	int	i;

	i = 0;
	vars->philo = malloc(sizeof(t_philo) * vars->args->philos);
	if (!vars->philo)
		return (0);
	while (vars->args->philos - i != 0)
	{
		vars->philo[i].phnum = i + 1;
		vars->philo[i].right = i;
		vars->philo[i].left = i + 1;
		if (argc == 6)
			vars->philo[i].limiteat = vars->args->limiteat;
		i++;
	}
	return (1);
}

static void	initargs(t_vars *vars, int argc, char **argv)
{
	vars->args = malloc(sizeof(t_args));
	vars->args->philos = atoi(argv[1]);
	vars->args->tte = atoi(argv[3]);
	vars->args->ttd = atoi(argv[2]);
	vars->args->tts = atoi(argv[4]);
	if (argc == 6)
		vars->args->limiteat = atoi(argv[5]);
	vars->args->cutl = vars->args->philos;
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("\033[1;31mInvalid num of arguents!\n");
		return (0);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (0);
	initargs(vars, argc, argv);
	initphilos(vars, argc);
	free (vars->args);
	free (vars);
	return (0);
}
