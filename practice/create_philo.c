/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:01:44 by yecsong           #+#    #+#             */
/*   Updated: 2022/12/07 15:07:04 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "pthread.h"

pthread_mutex_t	mutex;

void	*handler(void *arg)
{
	int	*sum;
	
	sum = (int *)arg;
	(*sum)++;
	printf("%d\n", *sum);
	pthread_mutex_unlock(&mutex);
	return (sum);
}

int	main()
{
	pthread_t	pthread; //thread의 자료형
	int			tid; // pthread 식별자
	int			i; // 인덱스
	int			sum;

	sum = 0;
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 20000)
	{
		// thread 생성
		tid = pthread_create(&pthread, NULL, handler, (void *)&sum);
		if (tid)
			return (-1);
		i++;
	}
	i = 0;
	while (i < 20000)
	{	// thread가 종료될 때 까지 대기 및 리턴 값 반환. 
		pthread_join(pthread, NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("sum = %d\n", sum);
	return (0);
}
