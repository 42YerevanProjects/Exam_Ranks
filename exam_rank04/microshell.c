#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

typedef	struct	s_cmd
{
	char	**args;
	int		in;
	int		out;
}				t_cmd;

typedef	struct	s_micro
{
	t_cmd	*cmds;
	char	**env;
	pid_t	*fam;
	int		segments;
	int		n;
}				t_micro;

t_micro	g_data;

void	ft_puterr(char	*msg)
{
	write(2, msg, strlen(msg));
}

void	ft_exit(char *msg, int k)
{
	ft_puterr(msg);
	if (k)
		kill(0, SIGINT);
	exit(1);
}

void	ft_exec(t_cmd *cmd)
{
	if (dup2(cmd->in, 0) == - 1 || dup2(cmd->out, 1) == -1)
		ft_exit("error: fatal", 1);
	execve(cmd->args[0], cmd->args, g_data.env);
	ft_puterr("error: cannot execute ");
	ft_puterr(cmd->args[0]);
	ft_puterr("\n");
	exit(127);
}

int	main(int argc, char **argv, char **environ)
{
	int	i;

	// Initializing 
	(void)argc;
	i = 0;
	g_data.env = environ;
	g_data.segments = 1;

	while (argv[i])
		if (!strcmp(argv[i++], ";"))
			g_data.segments++;
	argv++;

	// Main Loop
	while (*argv && g_data.segments)
	{
		if (!strcmp(*argv, ";"))
		{
			g_data.segments--;
			argv++;
			continue;
		}

		// Parsing the input
		i = 0;
		g_data.n = 1;
		while (argv[i] && strcmp(argv[i], ";"))
			if (!strcmp(argv[i++], "|"))
				g_data.n++;
		
		g_data.cmds = malloc(sizeof(t_cmd) * g_data.n);
		g_data.fam = malloc(sizeof(pid_t) * g_data.n);
		if (!g_data.cmds || !g_data.fam)
			ft_exit("error: fatal", 0);

		i = 0;
		int		cur = 0;
		int		cont = 1;
		char	**bag = argv;
		while (cont)
		{
			g_data.cmds[cur].args = bag;
			g_data.cmds[cur].in = 0;
			g_data.cmds[cur].out = 1;
			if (!bag[i] || !strcmp(bag[i], "|") || !strcmp(bag[i], ";"))
			{
				if (!bag[i] || !strcmp(bag[i], ";"))
					cont = 0;

				bag[i] = NULL;
				bag += i + 1;
				cur++;
				i = 0;
			}
			else
				i++;
		}

		// Forking, Pipeing and Execution
		if (strcmp(g_data.cmds[0].args[0], "cd"))
		{
			i = 0;
			while (i < g_data.n)
			{
				if (i != g_data.n - 1)
				{
					int	pipefd[2];

					if (pipe(pipefd))
						ft_exit("error: fatal", 0);
					g_data.cmds[i].out = pipefd[1];
					g_data.cmds[i + 1].in = pipefd[0]; 
				}
				g_data.fam[i] = fork();
				if (g_data.fam[i] == -1)
					ft_exit("error: fatal", 1);
				else if (g_data.fam[i] == 0)
					ft_exec(g_data.cmds + i);

				waitpid(g_data.fam[i], NULL, 0);
				if (g_data.cmds[i].in != 0)
					close(g_data.cmds[i].in);
				if (g_data.cmds[i].out != 1)
					close(g_data.cmds[i].out);
				i++;
			}
		}
		else
		{
			if (!g_data.cmds[0].args[1] || g_data.cmds[0].args[2])
				ft_puterr("error: cd: bad arguments");
			else
			
				if (chdir(g_data.cmds[0].args[1]) == -1)
				{
					ft_puterr("error: cd: cannot change directory to ");
					ft_puterr(g_data.cmds[0].args[1]);
					ft_puterr("\n");
				}
		}

		// Ending
		if (g_data.segments > 1)
		{
			i = 0;
			while (g_data.cmds[g_data.n - 1] .args[i])
				i++;
			argv = &g_data.cmds[g_data.n - 1].args[i] + 1;
		}
		free(g_data.fam);
		free(g_data.cmds);
		g_data.segments--;
	}

	return (0);
}
