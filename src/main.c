/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:11:36 by thsion            #+#    #+#             */
/*   Updated: 2024/08/29 14:06:22 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


#include "../minishell.h"

int g_status;

void 	show_prompt(t_data *data)
{
	char *input;
    t_node  *final_node;

	while (1)
	{
		signal_handler();
		input = readline("minishell$ ");
		if (check_empty_input(input))
		{
			add_history(input);
            final_node = starting_tree(input, data);
			run_exec_node(final_node, data);
            printf("\n%d\n", final_node->type);
		} 
	}
}

int main(int ac, char **av, char **envp)
{
	t_data data;

	(void)av;
	if (ac > 1)
		printf("🚫 Minishell doesn't take arguments. Still launching Minishell ... 🚫");
	init_env_tab(&data, envp);
	if (!data.env_vars)
		return (1);
	show_prompt(&data);
	//free_minishell(&data);
	return (0);
}











































// EXEMPLE DE PROCESSUS D'EXECUTION :
/* void	general_exec(input, data)
{
	if(builtin)
		-----> exec_bulting.c
	if (pipe)
		------ > exec_pipe.c
} */



// void general_exec(char *command, t_tabenv *tabenv)
// {    
// 	first_argument = isolating_first_argument(command);
// 	t_exec_node exec_node;
	
// 	init_exec_node(&exec_node, command);
// 	if (run_builtin(command, tabenv))
// 		printf("je suis un builtin");
	
// 	if (!run_builtin(command, tabenv))
// 	 	run_exec(command, tabenv);
// }

// void 	show_prompt(t_tabenv *tabenv)
// {
// 	char *command;

// 	while (1)
// 	{
// 		signal_handler();
// 		command = readline("minishell$ ");

// 		// securite
// 		if (command == NULL)
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		if (command)
// 		{
// 			add_history(command);
// 			general_exec(command, tabenv);
// 		}
		
// 		free(command);
// 	}
// }

// int main(int ac, char **av, char **envp)
// {
// 	t_tabenv tabenv;
	
 	
// 	// (void)envp;
// 	(void)ac;
// 	(void)av;

// 	init_env_tab(&tabenv, envp);

//  	// char *argz[] = {"arg1", "arg2", "arg3", NULL};
//  	// char *argz2[] = {"arg1", "arg2", "arg3", NULL};

// 	// -----------------------------------------
// 	// EXEC COMMANDS AND BUILTINS
// 	// init_env_tab(&tabenv, envp);
//     // t_node *node = create_exec_node(2, false, "ls", argz);
// 	// run_exec_node(node, &tabenv);
	
// 	// // -----------------------------------------
// 	// // EXEC PIPE AND MULTI PIPES
// 	// // node DROITE -> gauche et DROITE -> droite                  
// 	// t_node *left_down_level = create_exec_node(EXEC, false, "rev");
// 	// t_node *right_down_level = create_exec_node(EXEC, false, "tr 'h' 'A'");
// 	// // node GAUCHE 
// 	// t_node *left = create_exec_node(EXEC, false, "echo helllo");
// 	// t_node *right = create_exec_node(EXEC, false, "rev");
// 	// // node a DROITE  
// 	// t_node *sub_pipe_node = create_pipe_node(PIPE, left_down_level, right_down_level);
// 	// // // pipe principal avec left et right qui est un pipe aussi
// 	// t_node *pipe_node = create_pipe_node(PIPE, left, sub_pipe_node);
// 	// t_node *pipe_node = create_pipe_node(PIPE, left_down_level, right_down_level);
	
// 	// run_exec_node(left, &tabenv);
// 	// run_exec_node(right, &tabenv);
	
// 	// run_pipe_node(pipe_node, &tabenv);

// 	// -----------------------------------------
// 	// REDIRECTIONS
	
// 	 // Créer un nœud de commande pour la commande "cat"
//     t_node *exec_node = create_exec_node(EXEC, false, "cat");

//     // Créer un nœud de redirection avec le type HEREDOC et "stop" comme délimiteur
//     t_node *redir_node = create_redir_node(REDIR, "stop", HEREDOC, exec_node);

//     // Créer un nœud de pipe pour connecter le heredoc à la commande "cat"
//     t_node *pipe_node = create_pipe_node(PIPE, redir_node, exec_node);

//     // Exécuter le nœud pipe
//     run_pipe_node(pipe_node, &tabenv);

	
// 	// -----------------------------------------
	
// 	// command = "blabla";
// 	// char *name;
// 	// name = "allo=4";
// 	// str = "~";

// 	// (1) BOOL PARSING
// 	// (2) INPUT CLEANvoid general_exec(char *command, t_tabenv *tabenv)
// 	// -------------------- 
// 	// (3) INIT ENV AND PARAM
// 	// init_env_tab(&tabenv, envp);
// 	// init_exec_node(&exec_node, av, ac);
// 	// (3) SET UP SIGNALS (4) SHOW PROMPT
// 	// show_prompt(&tabenv);
// 	// (5) FREE AND CLEAN
// 	// free_minishell(&tabenv);
// 	return (0);
// }
