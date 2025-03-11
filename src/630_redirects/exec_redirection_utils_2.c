/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:03:05 by meferraz          #+#    #+#             */
/*   Updated: 2025/03/11 16:10:42 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Prints a predefined error message and updates the given status.
 *
 * This function is used to signal an error by printing a predefined error
 * message to the standard error stream and setting the provided status
 * pointer to indicate an error has occurred.
 *
 * @param status A pointer to an integer where the error status will be set.
 */
void	ft_print_error_and_status(t_status *status)
{
	ft_print_error(ERR_DUP2_FAIL);
	*status = ERROR;
}
