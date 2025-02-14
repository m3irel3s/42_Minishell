/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:10 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/14 12:30:02 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

	// valid names - Must start with a letter or '_', and contain only letters or numbers ######
	// print export ####
	// add new variable
	// if it exists, overwrite, if it is "+=" append
	// if doenst exist, give empty value if nothing has been assigned

	// 0 no quote
	// 1 single quote
	// 2 double quote

void	ft_export(t_shell *shell)
{
	t_token *curr;
	char	**export;

	export = NULL;
	curr = shell->tokens;
	if (!curr->next)
	{
		export = ft_duplicate_env(shell->env_cpy);
		export = ft_sort_export(export);
		ft_print_export(export);
		ft_free_arr(export);
		return;
	}
	while (curr->next)
	{
		char	*var;
		char	*value;
		curr = curr->next;
		if(ft_check_var_chars(curr->value) == SUCCESS)
			ft_printf(1, "Chars ok\n");
		var = ft_get_var_name(curr->value);
		printf("var=> %s\n", var);
		value = curr->value + (ft_strlen(var) + 1);
		printf("value=> %s\n", value);
		ft_update_or_add_var(var, value, shell);
		printf("env_size => %d\n", ft_get_env_size(shell));
		printf("value of the last index => %s\n", shell->env_cpy[ft_get_env_size(shell) - 1]);
	}
}

void	ft_add_var_to_env(t_shell *shell, char *var, char *value)
{
	char	**new_env;
	char	**old_env;
	int		new_size;
	int		i;
	
	old_env = shell->env_cpy;
	i = 0;
	new_size = ft_get_env_size(shell) + 1;
	new_env = ft_safe_malloc(sizeof(char *) * new_size);
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	new_env[i] = ft_update_var(var, value);
	printf("i => %d\n",i);
	printf("new_size => %d\n",new_size);
	new_env[++i] = NULL;
	shell->env_cpy = new_env;
}
