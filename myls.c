/*
 * myls.c
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
	struct dirent *read;
	DIR *dir;
	int opt;
	
	if ( argv[1] != NULL )
	{
		while ((opt = getopt(argc, argv, "aisFlRr")) != -1 )
		{
			switch(opt)
			{
				case 'a' :
			
				dir = opendir(".");
				if ( dir == NULL )
				{
					printf("항목이 없습니다.");
				}
			
				while(read = readdir(dir))
				{
					printf("%s\n",read->d_name);
				}
				dir = opendir(".");
				break;
			
			}
		}
	}
	else if ( argc == 1 )
	{
		dir = opendir(".");
		if ( dir == NULL )
		{
			printf("항목이 없습니다.");
		}
		while(read = readdir(dir))
		{
			if ( read->d_name[0] == '.' ){}
			else
			{
				printf("%s\n",read->d_name);
			}
		}
	}

	return 0;
}

