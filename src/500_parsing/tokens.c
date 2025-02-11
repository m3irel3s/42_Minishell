/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 15:30:27 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_and_tokenize(t_shell *shell);
static t_status	ft_handle_unclosed_quote(t_shell *shell,
					size_t *index, char quote_char);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/11 13:22:05 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_status	ft_process_and_tokenize(t_shell *shell);
static t_status	ft_handle_unclosed_quote(t_shell *shell,
					size_t *index, char quote_char);

/**
 * @brief Tokenizes the input stored in the shell structure.
 *
 * This function checks if the shell's input is valid and calls
 * ft_process_and_tokenize to tokenize the input. If either the shell or
 * its input is invalid, the function returns ERROR. Otherwise, it returns
 * the result of ft_process_and_tokenize.
 *
 * @param shell A pointer to the shell structure containing the input
 *              to be tokenized.
 *
 * @return Returns ERROR if the shell or its input is invalid;
 *         otherwise, returns the result of ft_process_and_tokenize.
 */
int	ft_tokenize(t_shell *shell)
{
	if (!shell || !shell->input)
		return (ERROR);
	return (ft_process_and_tokenize(shell));
}

/**
 * @brief Processes and tokenizes the shell's input.
 *
 * This function iterates through the input string stored in the shell structure,
 * identifying tokens by handling spaces, quotes, and operators. It distinguishes
 * quoted tokens and handles unclosed quotes by invoking the appropriate handler.
 * Each identified token is created and added to the shell's token list. The function
 * returns SUCCESS if all tokens are successfully processed and added; otherwise,
 * it returns ERROR.
 *
 * @param shell A pointer to the shell structure containing the input string to be tokenized.
 *
 * @return Returns SUCCESS if the input is successfully tokenized; otherwise, returns ERROR.
 */
static t_status	ft_process_and_tokenize(t_shell *shell)
{
	size_t			i;
	size_t			start;
	char			quote_char;
	int				quoted_status;

	i = 0;
	quote_char = 0;
	quoted_status = 0;
	while (shell->input[i])
	{
		if (ft_is_space(shell->input[i]))
		{
			i++;
			continue ;
		}
		else if (ft_is_quote(shell->input[i]) && !quote_char)
		{
			quote_char = shell->input[i];
			quoted_status = (quote_char == '\'') * 1 + (quote_char == '"') * 2;
			start = i + 1;
			i++;
			while (shell->input[i] && shell->input[i] != quote_char)
				i++;
			if (!shell->input[i])
				return (ERROR);
			if (shell->input[i] == quote_char)
			{
				if (ft_create_and_add_token(shell, start, i - 1, quoted_status) == ERROR)
					return (ERROR);
				i++;
				quote_char = 0;
			}
			else
			{
				ft_putstr_fd("minishell: error: unmatched quote\n",
			STDERR_FILENO);
				return (ERROR);
			}
		}
		else if (ft_is_operator(shell->input[i]))
		{
			start = i;
			while (ft_is_operator(shell->input[i]))
				i++;
			if (ft_create_and_add_token(shell, start, i, quoted_status) == ERROR)
				return (ERROR);
		}
		else
		{
			start = i;
			while (shell->input[i] && !ft_is_space(shell->input[i]) &&
				!ft_is_operator(shell->input[i]) && !ft_is_quote(shell->input[i]))
				i++;
			if (ft_create_and_add_token(shell, start, i, quoted_status) == ERROR)
				return (ERROR);
		}
	}
	return (SUCCESS);
}
