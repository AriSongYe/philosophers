/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:00:13 by yecsong           #+#    #+#             */
/*   Updated: 2022/12/09 17:00:57 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_arg_value(t_arg *arg, char **argv)
{
	int	i;

	arg->philo_idx = 0;
	arg->num_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[2]);
	arg->time_to_sleep = ft_atoi(argv[2]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->fork = (int *)ft_calloc(arg->num_philo, sizeof(int));
	arg->fork_mutex = (pthread_mutex_t *)malloc \
		(sizeof(pthread_mutex_t) * arg->num_philo);
	arg->time_mutex = (pthread_mutex_t *)malloc \
		(sizeof(pthread_mutex_t) * arg->num_philo);
	arg->start_dead_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&arg->start_dead_mutex);
	i = 0;
	while (i < arg->num_philo)
	{
		pthread_mutex_init(&arg->fork_mutex[i], NULL);
		pthread_mutex_init(&arg->time_mutex[i++], NULL);
	}
}

t_arg	*init_arg(char **argv)
{
	t_arg	*arg;
	t_philo	*philo;

	arg = (t_arg *)ft_calloc(sizeof (t_arg));
	put_arg_value(arg, argv);
	philo = (t_philo *)ft_calloc(arg->num_philo, sizeof(t_philo));
	arg->philo = philo;
	return (arg);
}

int main(int argc, char **argv)
{
 	t_arg		*arg;
	pthread_t	*tid;

	if (valid_argv(argc, argv))
		return (-1);
	arg = init_arg(argv);
	tid = (pthread_t *)malloc(sizeof(pthread_t) * arg->num_philo);
	tid = ft_calloc(1);
	return (0);
}
