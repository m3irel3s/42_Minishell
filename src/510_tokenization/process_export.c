/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:51 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/14 10:06:39 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Processes an export assignment.
 *
 * Checks if the given word is a valid variable name and processes it
 * accordingly. If the word contains an equals sign, it is split into a variable
 * name and value. The variable name is checked to ensure it is a valid
 * identifier. If it is, a new token is created and added to the shell's token
 * list.
 *
 * @param shell A pointer to the shell structure.
 * @param word The word to process.
 *
 * @return Returns SUCCESS if the word is successfully processed, ERROR
 *         otherwise.
 */

