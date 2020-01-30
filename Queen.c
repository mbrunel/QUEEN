#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int	count_quine()
{
	int i = 1;
	struct dirent *node;
	DIR *dir;

	dir = opendir("./");
	while (node = readdir(dir))
		if (!strncmp(node->d_name, "quine", 5))
			i++;
	closedir(dir);
	return (i);
}

int main(int ac, char *av[], char *vp[])
{
	FILE *s;
	char nof[200];
	char call[200];
	char *buf = "#include <stdio.h>%c#include <dirent.h>%c#include\
<string.h>%c#include <unistd.h>%c#include <stdlib.h>%cstatic\
 int count_quine(){int i = 1;struct dirent *node;DIR *dir;dir = opendir(%c./%c);\
while (node = readdir(dir)){if (!strncmp(node->d_name, %cquine%c, 5)){i++;}}closedir(dir);\
return (i);}int main(int ac, char *av[], char *vp[]){FILE *s;char nof[20];char call[200];char *buf = %c%s%c;\
int nbquine = count_quine();char noex[200];sprintf(nof, %c./quine%cd.c%c, nbquine);sprintf(noex, %c./quine%cd.out%c, nbquine);\
s = fopen(nof, %cw+%c);fprintf(s, buf, 10, 10, 10, 10, 10, 34,34,34,34,34,buf,34,34,37,34,34,37,34,34,34,34,37,37,34,34,37,34);\
fclose(s);sprintf(call, %c/usr/bin/gcc -o %cs %cs%c, noex, nof);\
system(call);sprintf(call, %c./%cs%c, noex);char *arg[] = {call, NULL};execve(call, arg, vp);return 0;}";
	int nbquine = count_quine();
	char noex[200];
	sprintf(nof, "./quine%d.c", nbquine);
	sprintf(noex, "./quine%d.out", nbquine);
	s = fopen(nof, "w+");
	fprintf(s, buf, 10, 10, 10, 10, 10, 34,34,34,34,34,buf,34,34,37,34,34,37,34,34,34,34,37,37,34,34,37,34);
	fclose(s);
	sprintf(call, "/usr/bin/gcc -o %s %s", noex, nof);
	system(call);
	sprintf(call, "./%s", noex);
	char *arg[] = {call, NULL};
	execve(call, arg, vp);
	return (0);
}
