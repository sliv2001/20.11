#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>

#define MAX_EVENTS 1024
#define ESIZE  ( sizeof (struct inotify_event) )

int main( int argc, char **argv )
{
	int length, i = 0, wd;
	int fd;
	char buffer[4096];
	struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
	fd = inotify_init();
	if ( fd < 0 ) {
		return 0;
	}
	wd = inotify_add_watch(fd, argv[1], IN_CREATE | IN_MOVE_SELF | IN_DELETE);
	if (wd<0)
	{
		return -1;
	}
	while(1)
	{
		i = 0;
		length = read(fd, buffer, 4096);
		if (length < 0) {
			perror("Sth wrong");
		}
		while ( i < length ) {
			if ( event->len ) {
				if ( event->mask & IN_CREATE) {
					if (event->mask & IN_ISDIR)
						printf( "Created dir %s\n", event->name);
					else
						printf("Created file %s\n", event->name);
				}
			if (event->mask & IN_MOVE_SELF) {
				if (event->mask & IN_ISDIR)
					printf("Moved dir %s\n", event->name);
				else
					printf("Moved file %s\n", event->name);
			}
			if (event->mask & IN_DELETE) {
				if (event->mask & IN_ISDIR)
					printf("Deleted dir %s.\n", event->name);
				else
					printf("Deleted file %s\n", event->name);
			}
			i += ESIZE + event->len;
		}
		}
	}
	return 0;
}
