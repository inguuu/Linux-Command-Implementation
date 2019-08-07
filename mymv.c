/*
 * mymv.c
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
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char **argv)
{
	struct stat *fileinfo = malloc(sizeof(stat));
	if ( argc != 3 )
	{
		printf("mv a b 형식으로 사용하셔야 합니다.");
		exit(1);
	}
	int fd1 = 0;
	int fd2 = 0;
	int fd3 = 0;
	int rsize;
	char buf[102400];
	DIR *dir;
	
	fd1 = open(argv[1], O_RDWR);
    stat(argv[1],fileinfo);
	
	if (S_ISREG(fileinfo->st_mode))
	{
		fd2 = open(argv[2],O_RDWR | O_CREAT | O_EXCL, 0644);
		stat(argv[2], fileinfo);
		if ( access(argv[2], F_OK) == -1 )
		{
			rename(argv[1], argv[2]);
		}
		else if ( S_ISREG(fileinfo->st_mode) )
		{
			rename(argv[1], argv[2]);
		}
		else if ( S_ISDIR(fileinfo->st_mode))
		{
			chdir(argv[2]);
			fd3 = open(argv[1],O_RDWR | O_CREAT | O_EXCL, 0644);
			rsize = read(fd1,buf,102400); 
			write(fd3,buf,rsize);
		}
	}
	else if ( S_ISDIR(fileinfo->st_mode) )
	{
		fd2 = open(argv[2],O_RDWR | O_CREAT | O_EXCL, 0644);
		stat(argv[2], fileinfo);
		if ( access(argv[2], F_OK) == -1 )
		{
			rename(argv[1],argv[2]);
		}
		else if ( S_ISDIR(fileinfo->st_mode))
		{
			struct dirent *read;
			dir = opendir(argv[2]);
			int num = 0;
			
			while( read = readdir(dir) )
			{
				num++;
			}
			if ( num == 2)
			{
				rename(argv[1], argv[2]);
			}
			else
			{
				printf("파일을 비우셔야 디렉토리를 옮길 수 있습니다.");
				exit(1);
			} 
		}
	}
	return 0;
}

