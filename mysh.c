/*
 * mysh.c
 * 
 * Copyright 2015 Jeong <jeong@jeong-VirtualBox>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

	struct CMD
	{
		char *name;
		char *desc;
		int (*cmd)(int argc, char *argv[]);
	};
	
	int cmd_cd (int argc, char *argv[]);
	int cmd_pwd (int argc, char *argv[]);
	int cmd_exit (int argc, char *argv[]);
	int cmd_help (int argc, char *argv[]);
	int cmdProcessing(void);
	
	struct CMD builtin[] = 
	{
		{ "cd", "작업 디렉토리 바꾸기",cmd_cd },
		{ "pwd","현재 디렉토리는? ", cmd_pwd },
		{ "exit","셸 실행을 종료합니다.",cmd_exit},
		{ "help","도움말 보여 주기", cmd_help}
	};
	
	const int builtins = 4;
	
int main(int argc, char **argv)
{
	int isExit = 0;
	
	while (!isExit)
	{
		isExit = cmdProcessing();
	}
	fputs ("My Shell을 종료합니다...\n",stdout);
	
	return 0;
}

#define STR_LEN 1024
#define MAX_TOKENS 128

int cmdProcessing (void)
{
	char cmdLine[STR_LEN];
	char *cmdTokens[MAX_TOKENS];
	char delim[] = " \t\n\r";
	char *token;
	int tokenNum;
	int i;
	
	int exitCode = 0;
	fputs("[mysh v0.1] $ ", stdout);
	fgets(cmdLine, STR_LEN, stdin);
	
	tokenNum = 0;
	token = strtok(cmdLine, delim);
	while (token)
	{
		cmdTokens[tokenNum++] = token;
		token = strtok(NULL, delim);
	}
	cmdTokens[tokenNum] = NULL;
	if (tokenNum == 0)
	{
		return exitCode;
	}
	for ( i = 0; i < builtins; ++i)
	{
		if ( strcmp(cmdTokens[0],builtin[i].name) == 0)
		{
			return builtin[i].cmd(tokenNum, cmdTokens);
		}
	}
	
	return exitCode;
}

int cmd_cd(int argc, char *argv[])
{
	if ( argc == 1 )
	{
		chdir(getenv("HOME"));
	}
	else if ( argc == 2 )
	{
		if (chdir(argv[1]) == -1)
		{
			printf("디렉토리가 없대요.\r\n");
		}
		else if (strcmp(argv[1],".") == 0)
		{
			chdir(getenv("HOME"));
		}
		else 
		{
			chdir(argv[1]);
		}
	}
	return 0;
}
int cmd_pwd(int argc, char *argv[])
{
	char buf[STR_LEN];
	getcwd(buf,1024);
	fputs(buf,stdout);
	fputs("\n",stdout);
	return 0;
}
int cmd_exit(int argc, char *argv[])
{
	return 1;
}
int cmd_help(int argc, char *argv[])
{
	int i;
	if ( argc == 1 )
	{
		for ( i = 0; i < builtins; ++i )
		{
			fputs(builtin[i].name, stdout);
			fputs("\t",stdout);
			fputs(builtin[i].desc, stdout);
			fputs("\n",stdout);
		}
	}
	else
	{
		for ( i = 0; i < builtins; ++i)
		{
			if ( strcmp(argv[1], builtin[i].name) == 0 )
			{
				fputs(builtin[i].name, stdout);
				fputs("\t",stdout);
				fputs(builtin[i].desc, stdout);
				fputs("\n",stdout);
			}
		}
	}
	return 0;
}
