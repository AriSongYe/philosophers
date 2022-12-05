/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getoftheday.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:50:27 by yecsong           #+#    #+#             */
/*   Updated: 2022/12/05 12:08:41 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>


int main()
{
	struct timeval	start;
	struct timeval	end;
	long long		diff_time;
	
	gettimeofday(&start, NULL);
	sleep(1);
	gettimeofday(&end, NULL);
	diff_time = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000);
	printf("difftime = %lld\n", diff_time);
}
