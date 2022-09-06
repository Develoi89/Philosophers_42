/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:08:33 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/06 16:51:19 by ealonso-         ###   ########.fr       */
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
	int				philos;
	int				limiteat;
	long long int	tte;
	long long int	ttd;
	long long int	tts;
}	t_args;

typedef struct s_philo
{
	int				left;
	int				phnum;
	int				right;
	int				limiteat;
	long long int	tte;
	long long int	ttd;
	long long int	tts;
	long long int	time;
}	t_philo;

typedef struct s_vars
{
	int				id;
	t_args			*args;
	t_philo			*philo;
	pthread_t		*threads;
	pthread_mutex_t	dead;
	pthread_mutex_t	*cutl;
	pthread_mutex_t	writing;
}	t_vars;

int				errors(char *s);
long long int	ft_atoi(const char *str);
int				comprove(char **argv, int argc);

void			time_sleep(int i);
void			*routine(void *var);
void			free_all(t_vars *vars);

long long int	get_time(void);

#endif