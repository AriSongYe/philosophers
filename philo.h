/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:01:17 by yecsong           #+#    #+#             */
/*   Updated: 2022/11/30 05:36:34 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define	SLEEP	0
# define	HUNGRY	1
# define	EATING	2


# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_time_info
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_time;
	struct timeval	start;
	struct timeval	now;
	pthread_mutex_t	mutex;
}	t_time_info;

typedef struct	s_arg
{
	int				index;
	int				*state;
	t_time_info		*info;
}	t_arg;

#endif
