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

# Set breakpoints
break main
break ft_export
break ft_set_var_value
break ft_add_var_to_env

# Show active breakpoints and watchpoints
info break
info watch

# Automatically start the program (optional)
run
