/*
 * mycat2.c
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
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int fi;
	char buf[102400];
	int rsize;
	int wsize;
	
	if ( argc == 1 )
	{
		while(read(0,buf,1024) != EOF)
		{
			rsize = read(0,buf,102400);
			wsize = write(1,buf,rsize);
		}
	}
	fi = open(argv[1], O_RDONLY);
	rsize = read(fi, buf, 102400);
	wsize = write(1,buf,rsize);
	
	while ( read(fi,buf,102400))
	{
		wsize = write(1,buf,rsize);
	}
	close(fi);
		
	return 0;
}

