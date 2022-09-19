/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:22 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/19 11:35:56 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static int	initphilos(t_vars *vars, int argc)
{
	int	i;

	i = 0;
	vars->philo = malloc(sizeof(t_philo) * vars->args->philos);
	if (!vars->philo)
		return (errors("\033[1;31mphilos malloc failed!\n"));
	while (i < vars->args->philos)
	{
		vars->philo[i].phnum = i + 1;
		vars->philo[i].right = i;
		if (i != vars->args->philos - 1)
			vars->philo[i].left = i + 1;
		else
			vars->philo[i].left = 0;
		if (argc == 6)
			vars->philo[i].limiteat = vars->args->limiteat;
		i++;
	}
	return (1);
}

static int	initargs(t_vars *vars, int argc, char **argv)
{
	int	i;

	i = 0;
	vars->args = malloc(sizeof(t_args));
	if (!vars->args)
		return (errors("\033[1;31margs malloc failed!\n"));
	vars->args->philos = ft_atoi(argv[1]);
	vars->args->ttd = ft_atoi(argv[2]);
	vars->args->tte = ft_atoi(argv[3]);
	vars->args->tts = ft_atoi(argv[4]);
	if (argc == 6)
		vars->args->limiteat = atoi(argv[5]);
	vars->cutl = malloc(sizeof(pthread_mutex_t) * vars->args->philos);
	if (!vars->cutl)
		return (errors("\033[1;31mcutl malloc failed!\n"));
	while (i < vars->args->philos)
		pthread_mutex_init(&(vars->cutl[i++]), NULL);
	pthread_mutex_init(&(vars->writing), NULL);
	pthread_mutex_init(&(vars->dead), NULL);
	return (0);
}

static int	start(t_vars *vars)
{
	int	i;

	i = 0;
	vars->threads = (pthread_t *)malloc(sizeof(pthread_t) * vars->args->philos);
	if (!vars->threads)
		return (errors("\033[1;31mthreads malloc failed!\n"));
	while (i < vars->args->philos)
	{
		vars->id = i;
		pthread_create(&(vars->threads[i]), NULL, &routine, vars);
		usleep(20);
		i++;
	}
	i = 0;
	while (i++ < vars->args->philos)
		pthread_join(vars->threads[i], NULL);
	i = 0;
	pthread_mutex_unlock(&vars->writing);
	free (vars->threads);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (comprove(argv, argc) != 1)
		return (0);
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (errors("\033[1;31mvars malloc failed!\n"));
	initargs(vars, argc, argv);
	initphilos(vars, argc);
	start(vars);
	free_all(vars);
	return (0);
}
