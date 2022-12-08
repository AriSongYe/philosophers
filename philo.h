/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:01:17 by yecsong           #+#    #+#             */
/*   Updated: 2022/12/08 18:29:16 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define	HUNGRY	0
# define	EATING	1
# define	SLEEP	2
# define	THINK	3

# define	PICK_UP_FORK	0
# define	IS_EATING		1
# define	IS_SLEEPING		2
# define	IS_THINKING		3
# define	DIE				4


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int				state;
	int				left;
	int				right;
	int				eat_cnt;
	struct timeval	now;
	struct timeval	last_eat;
}	t_philo;

typedef struct	s_arg
{
	int				philo_idx;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*fork;
	int				is_dead;
	struct timeval	*start;
	pthread_mutex_t *mutex;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	philo_mutex;
	t_philo			*philo;
}	t_arg;

#endif
