/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahim@42KL | drmsr <me@drmsr.dev>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 09:04:34 by mrahim@42KL |     #+#    #+#             */
/*   Updated: 2023/09/30 09:19:34 by mrahim@42KL |    ###   ########.KL       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

int	ft_ultimate_range(int **array, int min, int max)
{
	int	i;

	if (min >= max)
	{
		*array = NULL;
		return (0);
	}
	*array = malloc((max - min) * sizeof(int));
	if (*array == NULL)
		return (-1);
	i = 0;
	while (i < (max - min))
	{
		(*array)[i] = min + i;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>

int	main(void)
{
	int	*array;
	int	min;
	int	max;
	int	i;

	min = 10;
	max = 20;

	printf("Size new array is : %d\n",ft_ultimate_range(&array, min, max));

	i = 0;
	while (i < (max - min))
	{
		printf("%d\n", array[i]);
		i++;
	}
	free(array);
	return (0);
}*/
