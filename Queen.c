#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int	count_quine()
{
	int i = 2;
	struct dirent *node;
	DIR *dir;

	dir = opendir("./infected/");
	while (node = readdir(dir)){
		if (!strncmp(node->d_name, "quine", 5)){
			i++;
		}
	}
	closedir(dir);
	return (i / 2);
}

int main(int ac, char *av[], char *vp[])
{
	FILE *s;
	char nof[200];
	int pipefd[2];
	char call[200];
	char *buf = "#include <stdio.h>%c#include <dirent.h>%c#include <sys/wait.h>%c#include\
<string.h>%c#include <unistd.h>%c#include <stdlib.h>%cstatic\
 int count_quine(){int i = 2;struct dirent *node;DIR *dir;dir = opendir(%c./infected/%c);\
while (node = readdir(dir)){if (!strncmp(node->d_name, %cquine%c, 5)){i++;}}closedir(dir);\
return (i/2);}int main(int ac, char *av[], char *vp[]){FILE *s;char nof[20];char call[200];char *buf = %c%s%c;\
int nbquine = count_quine();int status;char noex[200];sprintf(nof, %c./infected/quine%cd.c%c, nbquine);\
sprintf(noex, %c./infected/quine%cd.out%c, nbquine);s = fopen(nof, %cw+%c);\
fprintf(s, buf, 10, 10, 10,10, 10, 10, 34,34,34,34,34,buf,34,34,37,34,34,37,34,34,34,34,34,34,34,34,34,34,37,34);\
fclose(s);if (!fork()){char *arg_1[] = {%c/usr/bin/gcc%c, %c-o%c, noex, nof, NULL};\
execve(%c/usr/bin/gcc%c, arg_1, vp);}sprintf(call, %c./%cs%c, noex);\
char *arg_2[] = {call, NULL};wait(&status);if (!fork()){execve(call, arg_2, vp);};return 0;}";
	int nbquine = count_quine();
	int status;
	char noex[200];
	sprintf(nof, "./infected/quine%d.c", nbquine);
	sprintf(noex, "./infected/quine%d.out", nbquine);
	s = fopen(nof, "w+");
	fprintf(s, buf, 10, 10, 10,10, 10, 10, 34,34,34,34,34,buf,34,34,37,34,34,37,34,34,34,34,34,34,34,34,34,34,37,34);
	fclose(s);
	if (!fork()){
		char *arg_1[] = {"/usr/bin/gcc", "-o", noex, nof, NULL};
		execve("/usr/bin/gcc", arg_1, vp);
	}
	sprintf(call, "./%s", noex);
	char *arg_2[] = {call, NULL};
	wait(&status);
	if (!fork()){
		execve(call, arg_2, vp);
	}
	return (0);
}
