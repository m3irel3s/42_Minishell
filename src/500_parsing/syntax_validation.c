/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:43:44 by meferraz          #+#    #+#             */
/*   Updated: 2025/02/10 21:49:12 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_status validate_syntax(t_token *tokens) {
	t_token *current = tokens;
	t_token_type prev = -1;

	while (current) {
		t_token_type type = current->type;
		if (type == PIPE && (prev == -1 || prev == PIPE || prev == REDIRECT_IN || prev == REDIRECT_OUT || prev == HEREDOC || prev == REDIRECT_APPEND)) {
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
			return ERROR;
		}
		if ((type == REDIRECT_IN || type == REDIRECT_OUT || type == HEREDOC || type == REDIRECT_APPEND) && (!current->next || current->next->type != WORD)) {
			ft_putstr_fd("minishell: syntax error near redirect\n", STDERR_FILENO);
			return ERROR;
		}
		prev = type;
		current = current->next;
	}
	if (prev == PIPE || prev == REDIRECT_IN || prev == REDIRECT_OUT || prev == HEREDOC || prev == REDIRECT_APPEND) {
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", STDERR_FILENO);
		return ERROR;
	}
	return SUCCESS;
}
