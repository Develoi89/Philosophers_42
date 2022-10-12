/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:08:33 by ealonso-          #+#    #+#             */
/*   Updated: 2022/10/12 11:26:07 by ealonso-         ###   ########.fr       */
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

struct	s_vars;

typedef struct s_args
{
	int				param;
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
	int				meals;
	int				limiteat;
	long long int	tte;
	long long int	ttd;
	long long int	tts;
	long long int	time;
	struct s_vars	*vars;
}	t_philo;

typedef struct s_vars
{	
	int				dd;
	int				id;
	int				init;
	int				done;
	t_args			*args;
	t_philo			*philo;
	pthread_t		*threads;
	long long int	start_time;
	pthread_mutex_t	dead;
	pthread_mutex_t	*cutl;
	pthread_mutex_t	writing;
}	t_vars;

int				errors(char *s);
int				free_all(t_philo *philo);
int				comprove(char **argv, int argc);
int				printing(char *sms, t_philo *philo);

void			time_sleep(int i);
void			*routine(void *var);

long long int	get_time(void);
long long int	ft_atoi(const char *str);

#endif
