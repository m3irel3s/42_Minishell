/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:17:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/20 12:23:19 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void ft_free_token(t_token *token)
{
	if (token)
	{
		ft_free(token->value);
		ft_free(token);
	}
}

void ft_free_arr(char **arr)
{
	int i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}
