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

int main()
{
	FILE *s;
	char nof[200];
	char call[200];
	char *buf = "#include <stdio.h>%c#include <dirent.h>%c#include\
<string.h>%c#include <unistd.h>%c#include <stdlib.h>%cstatic\
 int count_quine(){int i = 1;struct dirent *node;DIR *dir;dir = opendir(%c./%c);\
while (node = readdir(dir)){if (!strncmp(node->d_name, %cquine%c, 5)){i++;}}closedir(dir);\
return (i);}int main(){FILE *s;char nof[20];char call[200];char *buf = %c%s%c;\
int nbquine = count_quine();sprintf(nof, %c./quine%cd.c%c, nbquine);\
s = fopen(nof, %cw+%c);fprintf(s, buf, 10, 10, 10, 10, 10, 34,34,34,34,34,buf,34,34,37,34,34,34,34,37,37,34,34,37,34);\
fclose(s);sprintf(call, %c/usr/bin/gcc -o quine%cd.out %cs%c, nbquine, nof);\
system(call);sprintf(call, %c./quine%cd.out%c, nbquine);system(call);return 0;}";
	int nbquine = count_quine();
	sprintf(nof, "./quine%d.c", nbquine);
	s = fopen(nof, "w+");
	fprintf(s, buf, 10, 10, 10, 10, 10, 34,34,34,34,34,buf,34,34,37,34,34,34,34,37,37,34,34,37,34);
	fclose(s);
	sprintf(call, "/usr/bin/gcc -o quine%d.out %s", nbquine, nof);
	system(call);
	sprintf(call, "./quine%d.out", nbquine);
	system(call);
	return (0);
}
