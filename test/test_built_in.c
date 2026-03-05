/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:18:54 by obutolin          #+#    #+#             */
/*   Updated: 2026/03/05 09:23:41 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *run_cmd_and_capture(char **argv, int (*func)(char **))
{
	int		fd[2];
	int		saved_stdout;
	char	tmp[1024];
	ssize_t	bytes;
	size_t	total = 0;
	char	*result = NULL;
	char	*new_result;

	if (pipe(fd) == -1)
		return (NULL);

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (NULL);
	}

	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(saved_stdout);
		return (NULL);
	}
	close(fd[1]);

	func(argv);
	fflush(stdout);

	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	while ((bytes = read(fd[0], tmp, sizeof(tmp))) > 0)
	{
		new_result = realloc(result, total + bytes + 1);
		if (!new_result)
		{
			free(result);
			close(fd[0]);
			return (NULL);
		}
		result = new_result;
		memcpy(result + total, tmp, bytes);
		total += bytes;
	}
	close(fd[0]);

	if (!result)
		return (strdup(""));

	result[total] = '\0';
	return (result);
}

char *run_env_cmd_and_capture(char **argv, t_env **env,
		int (*func)(char **argv, t_env **env))
{
	int		fd[2];
	int		saved_stdout;
	char	tmp[1024];
	ssize_t	bytes;
	size_t	total = 0;
	char	*result = NULL;
	char	*new_result;

	if (pipe(fd) == -1)
		return (NULL);

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (NULL);
	}

	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(saved_stdout);
		return (NULL);
	}
	close(fd[1]);

	func(argv, env);
	fflush(stdout);

	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	while ((bytes = read(fd[0], tmp, sizeof(tmp))) > 0)
	{
		new_result = realloc(result, total + bytes + 1);
		if (!new_result)
		{
			free(result);
			close(fd[0]);
			return (NULL);
		}
		result = new_result;
		memcpy(result + total, tmp, bytes);
		total += bytes;
	}
	close(fd[0]);

	if (!result)
		return (strdup(""));

	result[total] = '\0';
	return (result);
}


void	built_in_echo_test()
{
	char **argv;
	char *str;

	printf("\nECHO BUILTIN\n");
	// argv == NULL.  Return -1;
	argv = NULL;
	if (built_in_echo(argv) == -1)
		printf("1. OK\n");
	else
		printf("1. ERROR argv == NULL\n");

	// First argv[0] = NULL.  Return -1;
	argv = calloc(7, sizeof(char *));
	if (built_in_echo(argv) == -1)
		printf("2. OK\n");
	else
		printf("2. ERROR argv[0] == NULL\n");

	// First argv[0] != "echo". Command "bubu". Return -1;
	argv[0] = calloc(5, sizeof(char));
	ft_strlcpy(argv[0], "bubu", 5);
	if (built_in_echo(argv) == -1)
		printf("3. OK\n");
	else
		printf("3. ERROR argv[0] != 'echo'\n");

	// First argv is "echo". Command "echo". Return 0;
	ft_strlcpy(argv[0], "echo", 5);
	if (built_in_echo(argv) == 0)
		printf("4. OK\n");
	else
		printf("4. ERROR argv[0] == 'echo'\n");

	// First argv is echo. Command "echo". Print "\n"
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "\n") == 0)
		printf("5. OK\n");
	else
		printf("5. ERROR command 'echo'\n");
	free(str);

	// Command "echo -n". Print ""
	argv[1] = calloc(3, sizeof(char));
	ft_strlcpy(argv[1], "-n", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (strlen(str) == 0)
		printf("6. OK\n");
	else
		printf("6. ERROR command 'echo -n'\n");
	free(str);

	// Command "echo ok". Print "ok\n"
	ft_strlcpy(argv[1], "ok", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "ok\n") == 0)
		printf("7. OK\n");
	else
		printf("7. ERROR command 'echo ok'\n");
	free(str);

	// Command "echo -e". Print "\n"
	ft_strlcpy(argv[1], "-e", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "\n") == 0)
		printf("8. OK\n");
	else
		printf("8. ERROR command 'echo -e'\n");
	free(str);

	// Command "echo -e hi". Print "hi\n"
	argv[2] = calloc(3, sizeof(char));
	ft_strlcpy(argv[2], "hi", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "hi\n") == 0)
		printf("9. OK\n");
	else
		printf("9. ERROR command 'echo -e hi'\n");
	free(str);

	// Command "echo -e -n". Print ""
	ft_strlcpy(argv[2], "-n", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (strlen(str) == 0)
		printf("10. OK\n");
	else
		printf("10. ERROR command 'echo -e -n'\n");
	free(str);

	// Command "echo -e -n to". Print "to"
	argv[3] = calloc(3, sizeof(char));
	ft_strlcpy(argv[3], "to", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "to") == 0)
		printf("11. OK\n");
	else
		printf("11. ERROR command 'echo -e -n to'\n");
	free(str);

	// Command "echo -e -n -E". Print ""
	ft_strlcpy(argv[3], "-E", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (strlen(str) == 0)
		printf("12. OK\n");
	else
		printf("12. ERROR command 'echo -e -n -E'\n");
	free(str);

	// Command "echo -e -n -n word". Print "word"
	argv[4] = calloc(5, sizeof(char));
	ft_strlcpy(argv[3], "-n", 3);
	ft_strlcpy(argv[4], "word", 5);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "word") == 0)
		printf("13. OK\n");
	else
		printf("13. ERROR command 'echo -e -n -n word'\n");
	free(str);

	// Command "echo -e -n -n -nnn". Print ""
	ft_strlcpy(argv[4], "-nnn", 5);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "") == 0)
		printf("14. OK\n");
	else
		printf("14. ERROR command 'echo -e -n -n -nnn'\n");
	free(str);

	// Command "echo -e -n hi good". Print "hi good"
	ft_strlcpy(argv[4], "good", 5);
	ft_strlcpy(argv[3], "hi", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "hi good") == 0)
		printf("15. OK\n");
	else
		printf("15. ERROR command 'echo -e -n hi good'\n");
	free(str);

	// Command "echo -e ow hi word". Print "ow hi word\n"
	ft_strlcpy(argv[4], "word", 5);
	ft_strlcpy(argv[2], "ow", 3);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "ow hi word\n") == 0)
		printf("16. OK\n");
	else
		printf("16. ERROR command 'echo -e ow hi word'\n");
	free(str);

	// Command "echo wo ow hi word". Print "wo ow hi word\n"
	ft_strlcpy(argv[1], "wo", 3);
	ft_strlcpy(argv[4], "w\nrd", 5);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "wo ow hi w\nrd\n") == 0)
		printf("17. OK\n");
	else
		printf("17. ERROR command 'echo wo ow hi w\nrd'\n");
	free(str);

	// Command "echo -e -E -e -nnn 1234". Print "1234"
	argv[5] = calloc(5, sizeof(char));
	ft_strlcpy(argv[1], "-e", 3);
	ft_strlcpy(argv[2], "-E", 3);
	ft_strlcpy(argv[3], "-e", 3);
	ft_strlcpy(argv[4], "-nnn", 5);
	ft_strlcpy(argv[5], "1234", 5);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "1234") == 0)
		printf("18. OK\n");
	else
		printf("18. ERROR command 'echo -e -E -e -nnn 1234");
	free(str);

	// Command "echo -e -E -e -nnf 1234". Print "-nnf 1234\n"
	ft_strlcpy(argv[4], "-nnf", 5);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "-nnf 1234\n") == 0)
		printf("19. OK\n");
	else
		printf("19. ERROR command 'echo -e -E -e -nnf 1234");
	free(str);

	// Command "echo -e -E -e -n-E 1234". Print "-n-E 1234\n"
	ft_strlcpy(argv[4], "-n-E", 5);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_echo);
	if (ft_strcmp(str, "-n-E 1234\n") == 0)
		printf("20. OK\n");
	else
		printf("20. ERROR command 'echo -e -E -e -n-E 1234");
	free(str);

	free(argv[5]);
	free(argv[4]);
	free(argv[3]);
	free(argv[2]);
	free(argv[1]);
	free(argv[0]);
	free(argv);
}

void	built_in_pwd_test()
{
	char	**argv;
	char	*cwd;
	char	*str;
	char	*str_expected;

	printf("\nPWD BUILTIN\n");
	// argv == NULL.  Return -1;
	argv = NULL;
	if (built_in_pwd(argv) == -1)
		printf("1. OK\n");
	else printf("1. ERROR argv == NULL\n");

	// First argv[0] = NULL.  Return -1;
	argv = calloc(3, sizeof(char *));
	if (built_in_pwd(argv) == -1)
		printf("2. OK\n");
	else printf("2. ERROR argv[0] == NULL\n");

	// First argv[0] != "pwd". Command "mmm". Return -1;
	argv[0] = calloc(4, sizeof(char));
	ft_strlcpy(argv[0], "mmm", 4);
	if (built_in_pwd(argv) == -1)
		printf("3. OK\n");
	else printf("3. ERROR argv[0] != 'pwd'\n");

	// First argv is "pwd". Command "pwd". Return 0;
	ft_strlcpy(argv[0], "pwd", 4);
	if (built_in_pwd(argv) == 0)
		printf("4. OK\n");
	else printf("4. ERROR argv[0] == 'pwd'\n");

	// Command "pwd"
	cwd = getcwd(NULL, 0);
	str = NULL;
	str = run_cmd_and_capture(argv, built_in_pwd);
	str_expected = ft_straddchar(cwd, '\n');
	if (ft_strcmp(str, str_expected) == 0)
		printf("5. OK\n");
	else printf("5. ERROR command 'pwd'\n");
	free(str);
	free(str_expected);

	free(cwd);
}

void	built_in_exit_test(void)
{
	char	**argv;
	int		need_exit;

	printf("\nEXIT BUILTIN\n");
	argv = NULL;
	if (built_in_exit(argv, 0, &need_exit) == -1)
		printf("1. OK\n");
	else printf("1. ERROR argv == NULL\n");
}

void	built_in_export_test(void)
{
	char	**argv;
	char	**argv_only_export;
	t_env	*env;
	char	*str;

	printf("\nEXPORT BUILTIN\n");
	argv = NULL;
	argv_only_export = NULL;
	env = NULL;
	if (built_in_export(argv, &env) == -1)
		printf("1. OK\n");
	else printf("1. ERROR argv == NULL\n");

	// First argv[0] = NULL.  Return -1;
	argv = calloc(4, sizeof(char *));
	if (built_in_export(argv, &env) == -1)
		printf("2. OK\n");
	else
		printf("2. ERROR argv[0] == NULL\n");

	// First argv[0] != "export". Command "bububub". Return -1;
	argv[0] = calloc(7, sizeof(char));
	ft_strlcpy(argv[0], "bububub", 7);
	if (built_in_export(argv, &env) == -1)
		printf("3. OK\n");
	else
		printf("3. ERROR argv[0] != 'echo'\n");

	// First argv[0] != "export". Command "export". env = NULL Return 0;
	ft_strlcpy(argv[0], "export", 7);
	if (built_in_export(argv, &env) == 0)
		printf("4. OK\n");
	else
		printf("4. ERROR command 'export', env=NULL\n");

	// Command "export USER"
	argv[1] = calloc(50, sizeof(char));
	ft_strlcpy(argv[1], "USER", 5);
	str = NULL;
	str = run_env_cmd_and_capture(argv, &env, built_in_export);
	if (ft_strlen(str) == 0
			&& count_env(env) == 1)
		printf("5. OK\n");
	else
		printf("5. ERROR command 'export USER'\n");
	free(str);


	// Command "export" (env has "USER=null")
	argv_only_export = calloc(3, sizeof(char *));
	argv_only_export[0] = calloc(7, sizeof(char));
	ft_strlcpy(argv_only_export[0], "export", 7);
	str = NULL;
	str = run_env_cmd_and_capture(argv_only_export, &env, built_in_export);
	if (ft_strcmp(str, "declare -x USER\n") == 0)
		printf("6. OK\n");
	else
		printf("6. ERROR command 'export' with env USER=null\n");
	free(str);

	// Command "export WMVAR=MyVal"
	ft_strlcpy(argv[1], "WMVAR=MyVal", 12);
	str = NULL;
	str = run_env_cmd_and_capture(argv, &env, built_in_export);
	if (ft_strlen(str) == 0
			&& count_env(env) == 2)
		printf("7. OK\n");
	else
		printf("7. ERROR command 'export WMVAR=MyVal'\n");
	free(str);

	// Command "export" (env has "USER=null and WMVAR=MyVal ")
	str = NULL;
	str = run_env_cmd_and_capture(argv_only_export, &env, built_in_export);
	if (ft_strcmp(str, "declare -x USER\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("8. OK\n");
	else
		printf("8. ERROR command 'export' with env USER and WMVAR\n");
	free(str);

	// Command "export MyVAR=999"
	ft_strlcpy(argv[1], "MyVAR=999", 10);
	str = NULL;
	str = run_env_cmd_and_capture(argv, &env, built_in_export);
	if (ft_strlen(str) == 0 && count_env(env) == 3)
		printf("9. OK\n");
	else
		printf("9. ERROR command 'export MyVAR=999'\n");
	free(str);

	// Command "export" (env has "USER=null, WMVAR=MyVal, MyVAR=999 ")
	str = NULL;
	str = run_env_cmd_and_capture(argv_only_export, &env, built_in_export);
	if (ft_strcmp(str, "declare -x MyVAR=\"999\"\ndeclare -x USER\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("10. OK\n");
	else
		printf("10. ERROR command 'export' with env USER, WMVAR, MyVAR\n");
	free(str);

	// Command "export MyVAR=new"  Change the value to new value
	ft_strlcpy(argv[1], "MyVAR=new", 10);
	str = NULL;
	str = run_env_cmd_and_capture(argv, &env, built_in_export);
	if (ft_strlen(str) == 0
			&& count_env(env) == 3)
		printf("11. OK\n");
	else
		printf("11. ERROR command 'export MyVAR=new'\n");
	free(str);

	// Command "export" (env has "USER=null, WMVAR=MyVal, MyVAR=new ")
	str = NULL;
	str = run_env_cmd_and_capture(argv_only_export, &env, built_in_export);
	if (ft_strcmp(str,
				"declare -x MyVAR=\"new\"\ndeclare -x USER\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("12. OK\n");
	else
		printf("12. ERROR command 'export' with env USER, WMVAR, MyVAR\n");
	free(str);
	
	// Command "export MyVAR"  No changes
	free(argv[2]);
	argv[2] = NULL;
	str = NULL;
	str = run_env_cmd_and_capture(argv, &env, built_in_export);
	if (ft_strlen(str) == 0
			&& count_env(env) == 3)
		printf("13. OK\n");
	else
		printf("13. ERROR command 'export MyVAR'\n");
	free(str);

	// Command "export" (env has "USER=null, WMVAR=MyVal, MyVAR=new ")
	str = NULL;
	str = run_env_cmd_and_capture(
				argv_only_export, &env, built_in_export);
	if (ft_strcmp(str,
				"declare -x MyVAR=\"new\"\ndeclare -x USER\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("14. OK\n");
	else
		printf("14. ERROR command 'export' with env USER, WMVAR, MyVAR\n");
	free(str);
	
	// Command "export USER=Bob"
	ft_strlcpy(argv[1], "USER=Bob", 9);
	str = NULL;
	str = run_env_cmd_and_capture(
				argv, &env, built_in_export);
	if (ft_strlen(str) == 0
			&& count_env(env) == 3)
		printf("15. OK\n");
	else
		printf("15. ERROR command 'export USER=Bob'\n");
	free(str);

	// Command "export" (env has "USER=null, WMVAR=MyVal, MyVAR=new ")
	str = NULL;
	str = run_env_cmd_and_capture(
				argv_only_export, &env, built_in_export);
	if (ft_strcmp(str,
				"declare -x MyVAR=\"new\"\ndeclare -x USER=\"Bob\"\ndeclare -x WMVAR=\"MyVal\"\n") == 0)
		printf("16. OK\n");
	else
		printf("16. ERROR command 'export' with env USER, WMVAR, MyVAR\n");
	free(str);

	// Command "export _Var"
	ft_strlcpy(argv[1], "_Var", 5);
	str = NULL;
	str = run_env_cmd_and_capture(
				argv, &env, built_in_export);
	if (ft_strlen(str) == 0
			&& count_env(env) == 4)
		printf("17. OK\n");
	else
		printf("17. ERROR command 'export _Var=Bob'\n");
	free(str);

	// Command "export" (env has "_Var, USER=Bob, WMVAR=MyVal, MyVAR=new ")
	str = NULL;
	str = run_env_cmd_and_capture(
				argv_only_export, &env, built_in_export);
	if (ft_strcmp(str,
				"declare -x MyVAR=\"new\"\ndeclare -x USER=\"Bob\"\ndeclare -x WMVAR=\"MyVal\"\ndeclare -x _Var\n") == 0)
		printf("18. OK\n");
	else
		printf("18. ERROR command 'export' with env USER, WMVAR, MyVAR, _Var\n");
	free(str);

	// Command "export 1var" wrang key
	ft_strlcpy(argv[1], "1var", 5);
	str = NULL;
	str = run_env_cmd_and_capture(
				argv, &env, built_in_export);
	if (ft_strcmp(str,
				"minishell: export: `1var`: not a valid identifier\n") == 0
			&& count_env(env) == 4)
		printf("19. OK\n");
	else
		printf("19. ERROR command 'export 1Var=Bob'\n");
	free(str);

	// Command "export MyVAR=7 AVar2=Meg" wrang key
	ft_strlcpy(argv[1], "MyVAR=7", 9);
	argv[2] = calloc(50, sizeof(char));
	ft_strlcpy(argv[2], "AVar2=Meg", 10);
	str = NULL;
	str = run_env_cmd_and_capture(
				argv, &env, built_in_export);
	if (ft_strlen(str) == 0
			&& count_env(env) == 5)
		printf("20. OK\n");
	else
		printf("20. ERROR command 'export MyVAR=7 AVar2=Meg'\n");
	free(str);
	
	// command "export"
	str = NULL;
	str = run_env_cmd_and_capture(
				argv_only_export, &env, built_in_export);
	if (ft_strcmp(str,
				"declare -x AVar2=\"Meg\"\ndeclare -x MyVAR=\"7\"\ndeclare -x USER=\"Bob\"\ndeclare -x WMVAR=\"MyVal\"\ndeclare -x _Var\n") == 0)
		printf("21. OK\n");
	else
		printf("21. ERROR command 'export' with env USER, WMVAR, MyVAR, _Var\n");
	free(str);

	free(argv_only_export[0]);
	free(argv_only_export);
	free(argv[2]);
	free(argv[1]);
	free(argv[0]);
	free(argv);
	free_env_list(&env);
}

void	built_in_unset_test(void)
{
	t_env	*env;
	char	**argv;

	printf("\nUNSET BUILTIN\n");
	env = NULL;
	update_env(&env, "VAR", "1");
	update_env(&env, "AVAR", NULL);
	update_env(&env, "XVAR", "X");
	update_env(&env, "DVAR", "D");

	// argv == NULL.  Return -1;
	argv = NULL;
	if (built_in_unset(argv, &env) == -1)
		printf("1. OK\n");
	else
		printf("1. ERROR argv == NULL\n");

	// First argv[0] = NULL.  Return -1;
	argv = calloc(3, sizeof(char *));
	if (built_in_unset(argv, &env) == -1)
		printf("2. OK\n");
	else
		printf("2. ERROR argv[0] == NULL\n");

	// First argv[0] != "unset". Command "bubub". Return -1;
	argv[0] = calloc(6, sizeof(char));
	ft_strlcpy(argv[0], "bubub", 6);
	if (built_in_unset(argv, &env) == -1)
		printf("3. OK\n");
	else
		printf("3. ERROR argv[0] != 'unset'\n");

	// Command "unset". Return 0;
	ft_strlcpy(argv[0], "unset", 6);
	if (built_in_unset(argv, &env) == 0 && count_env(env) == 4)
		printf("4. OK\n");
	else
		printf("4. ERROR argv[0] == 'unset'\n");

	// Command "unset AAAA" Not exist
	argv[1] = calloc(5, sizeof(char));
	ft_strlcpy(argv[1], "AAAA", 5);
	if (built_in_unset(argv, &env) == 0 && count_env(env) == 4)
		printf("5. OK\n");
	else
		printf("5. ERROR command `unset AAAA`\n");

	// Command "unset 1VAR" Wrong key name
	ft_strlcpy(argv[1], "1VAR", 5);
	if (built_in_unset(argv, &env) == 0 && count_env(env) == 4)
		printf("6. OK\n");
	else
		printf("6. ERROR command `unset 1VAR`\n");

	// Command "unset XVAR" Middl position
	ft_strlcpy(argv[1], "XVAR", 5);
	if (built_in_unset(argv, &env) == 0 && count_env(env) == 3)
		printf("7. OK\n");
	else
		printf("7. ERROR command `unset XVAR`\n");

	// Command "unset VAR" First position
	ft_strlcpy(argv[1], "VAR", 4);
	if (built_in_unset(argv, &env) == 0 && count_env(env) == 2)
		printf("8. OK\n");
	else
		printf("8. ERROR command `unset VAR`\n");

	// Command "unset VAR" Last position
	ft_strlcpy(argv[1], "AVAR", 5);
	if (built_in_unset(argv, &env) == 0 && count_env(env) == 1)
		printf("9. OK\n");
	else
		printf("9. ERROR command `unset AVAR`\n");

	// Command "unset VAR" Last element. Env will be empty
	ft_strlcpy(argv[1], "DVAR", 5);
	if (built_in_unset(argv, &env) == 0 && count_env(env) == 0)
		printf("10. OK\n");
	else
		printf("10. ERROR command `unset DVAR`\n");
	// print_env_list(env);
	free_env_list(&env);
	free(argv[1]);
	free(argv[0]);
	free(argv);
}

void	built_in_cd_test(void)
{
	t_env	*env;
	char	**argv;
	char	*str;

	printf("\nCD BUILTIN\n");
	env = NULL;

	// argv == NULL.  Return -1;
	argv = calloc(3, sizeof(char *));
	if (built_in_cd(argv, &env) == -1)
		printf("1. OK\n");
	else
		printf("1. ERROR argv == NULL\n");

	// First argv[0] != "cd". Command "bu". Return -1;
	argv[0] = calloc(3, sizeof(char));
	ft_strlcpy(argv[0], "bu", 3);
	if (built_in_cd(argv, &env) == -1)
		printf("2. OK\n");
	else
		printf("2. ERROR argv[0] != 'cd'\n");

	// Command "cd". There isn't HOME env. Return 1;
	ft_strlcpy(argv[0], "cd", 3);
	if (built_in_cd(argv, &env) == 1)
		printf("3. OK\n");
	else
		printf("3. ERROR command 'cd' but there isn't HOME env\n");

	// Command "cd". There is wrong HOME=C:/MyPath env. Return 0;
	update_env(&env, "HOME", "C:/MyPath");
	str = NULL;
	str = run_env_cmd_and_capture(argv, &env, built_in_cd);
	if (ft_strcmp(str, "minishell: cd: C:/MyPath: No such file or directory\n") == 0
		&& count_env(env) == 1)
		printf("4. OK\n");
	else
		printf("4. ERROR command `cd` There is wrong HOME env\n");
	free(str);
}

void	test_built_in(void)
{
	printf("\n===BUILTIN===\n");
	built_in_echo_test();
	built_in_pwd_test();
	// built_in_exit_test();
	built_in_export_test();
	built_in_unset_test();
	built_in_cd_test();
}
