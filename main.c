#include <dirent.h>
#include <stdio.h>

int main(int argc, char** argv){
	char* fullpath;
	struct dirent *dirp;
	size_t pathlen;
	DIR* d = opendir(argv[1]);
	if (argc!=2)
		return -1;
	while((dirp=readdir(d))!=NULL){
		printf("%s\n", dirp->d_name);
	}
	closedir(d);
	return 0;
}
