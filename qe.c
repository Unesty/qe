/* Run program quiet. GNU License. Created by Unesty in 2020. */
#define _GNU_SOURCE
#include <unistd.h>
//#include <stdlib.h> //too big for static binary
//#include <sys/syscall.h>
char arg=1;
char nosetsid=0;
char nofork=0;
char nocloseall=0;
char ofd=1;
#define USLEN 127
char usage[USLEN]=
"Usage: qe [0 1 2 to close only specific fd] -s(no setsid) -f(no fork) -d(same as 2 -s -f) -c [PATH to cd] -h(help) PROG ARGS\n";
int main(int argc, char** argv, char** envp)
{
	/*
	syscall(3,0);
	syscall(3,1);
	syscall(3,2);
	syscall(59,argv[1],&argv[1],&envp[0]);
	*/
	for(;arg<argc;arg++){
		switch(argv[arg][0]) {
			case '0':
				nocloseall=1;
				close(0);
				break;
			case '1':
				nocloseall=1;
				close(1);
				ofd++;
				break;
			case '2':
				nocloseall=1;
				close(2);
				break;
			case '-':
				switch(argv[arg][1]) {
					case 'h':
						syscall(1,ofd,&usage,USLEN);
						return 0;
					case 's':
						nosetsid=1;
						break;
					case 'f':
						nofork=1;
						break;
					case 'd':
						nofork=1;
						nosetsid=1;
						nocloseall=1;
						close(2);
						break;
					case 'c':
						arg++;
						syscall(80,argv[arg]);
						//setenv("PWD",argv[arg],1);
						break;
					case '-':
						switch(argv[arg][2]) {
							case 'h':
								syscall(1,ofd,&usage,USLEN);
								return 0;
						}
				}
				break;
			default:
				if(nosetsid==0){
					syscall(112);
				}
				if(nofork==0){
					if(syscall(56,0,0))
						return 0;
				}
				if(nocloseall==0){
					close(0);
					close(1);
					close(2);
				}
				execvpe(argv[arg],&argv[arg],&envp[0]);
		}
	}
}
