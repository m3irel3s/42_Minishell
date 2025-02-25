# Disable debuginfod prompts
set debuginfod enabled off

# Enable pending breakpoints
set breakpoint pending on

# Improve print readability
set print pretty on
set print array on

# Enable syntax highlighting
set style enabled on

### Logging
set logging on
set logging overwrite on
set logging redirect on
set logging file gdb.txt

# Load the program
file minishell

# define ft_handle_pipes
# 	disp num_pipes
# 	disp pid
# 	disp i
# 	disp curr->val.value
# 	disp curr->type
# end

define ft_env
	disp env[i]
	disp res
	disp i
end


# Set breakpoints
break main
break ft_env
fs cmd
# break ft_export
# break ft_set_var_value
# break ft_add_var_to_env

# Show active breakpoints and watchpoints
info break
info watch

# Automatically start the program (optional)
run
