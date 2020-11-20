#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	char* fullpath;
	struct dirent *dirp;
	size_t pathlen;
	DIR* d;
	if (argc!=2)
		return -1;
	d = opendir(argv[1]);
	if (d == NULL)
		return -1;
	while((dirp=readdir(d))!=NULL){
		if (strcmp(".", dirp->d_name)!=0&&strcmp("..", dirp->d_name)!=0)
			printf("%s\n", dirp->d_name);
	}
	closedir(d);
	return 0;
}
