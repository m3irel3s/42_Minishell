/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_type_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:55:14 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/03 14:55:46 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
