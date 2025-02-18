/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:27:21 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/18 12:46:15 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_status	ft_print_unmatched_quote_error(void)
{
	ft_putstr_fd(ERR_SYNTAX_UNCLOSED_QUOTE, 2);
	return (ERROR);
}

t_status	ft_print_syntax_error(char *token)
{
	ft_printf(2, ERR_SYNTAX_UNEXPECTED_TOKEN, token);
	return (ERROR);
}

t_status	ft_print_redirect_no_file_error(void)
{
	ft_putstr_fd(ERR_SYNTAX_EOF_REDIR, 2);
	return (ERROR);
}

t_status	ft_print_command_not_found_error(char *cmd)
{
	ft_printf(2, ERR_CMD_NOT_FOUND, cmd);
	return (ERROR);
}

t_status	ft_print_heredoc_delim_error(void)
{
	ft_putstr_fd(ERR_SYNTAX_EOF_HEREDOC, 2);
	return (ERROR);
}
