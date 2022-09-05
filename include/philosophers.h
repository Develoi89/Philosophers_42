/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:08:33 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/05 16:27:33 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int	ttd;
	int	tte;
	int	tts;
	int	philos;
	int	limiteat;
}	t_args;

typedef struct s_philo
{
	int				tte;
	int				ttd;
	int				tts;
	int				left;
	int				phnum;
	int				right;
	int				limiteat;
}	t_philo;

typedef struct s_vars
{
	int				id;
	t_args			*args;
	t_philo			*philo;
	pthread_mutex_t	dead;
	pthread_mutex_t	*cutl;
	pthread_mutex_t	writing;
	pthread_t		*threads;
}	t_vars;

int				errors(char *s);
int				atoi(const char *str);
int				comprove(char **argv, int argc);

void			time_sleep(int i);
void			free_all(t_vars *vars);

long long int	get_time(void);

#endif