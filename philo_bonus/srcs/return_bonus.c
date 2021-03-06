/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:34:01 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 17:34:25 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"

int	print_return(char *str, int code)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (code);
}

int	return_free_time(void *time, int exit_num)
{
	free(time);
	return (exit_num);
}

void	*return_free_time_void(void *time)
{
	free(time);
	return (NULL);
}
