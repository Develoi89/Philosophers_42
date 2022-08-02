/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:08:33 by ealonso-          #+#    #+#             */
/*   Updated: 2022/08/02 12:30:23 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int	philos;
	int	ttd;
	int	tte;
	int	tts;
	int	limiteat;
	int	cutl;
}	t_args;

typedef struct s_philo
{
	int	phnum;
	int	left;
	int	right;
	int	tte;
	int	ttd;
	int	tts;
	int	limiteat;
}	t_philo;

typedef struct s_vars
{
	t_philo	*philo;
	t_args	*args;
}	t_vars;

int	atoi(const char *str);

#endif