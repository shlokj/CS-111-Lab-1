#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#define EXIT_FAILURE 1

int main(int argc, char *argv[])
{
	errno = 0;	
	if (argc <= 1) {
		errno = EINVAL;
		exit(errno);
	}

	int fds[2];

	if (pipe(fds)) {
		exit(EXIT_FAILURE);
	}

	int rc = fork();
	if (rc < 0) {
		exit(EXIT_FAILURE);
	}

	else if (rc == 0) {
		if (argc > 2) {
			dup2(fds[1], STDOUT_FILENO);
		}
		if (execlp(argv[1], argv[1], (char *) NULL) == -1) {
			exit(EXIT_FAILURE);
		}
	}

	else {
		int status = 0;
		waitpid(rc, &status, 0);
		close(fds[1]);
		errno = WEXITSTATUS(status);
		if (errno != 0) 
			exit(errno);
	}

	for (int i = 2; i < argc - 1; i++) {
		int fd_read = fds[0];
		
		if (pipe(fds)) {
			exit(EXIT_FAILURE);
		}	

		int rc1 = fork();
		if (rc1 < 0) {
			exit(EXIT_FAILURE);
		}

		else if (rc1 == 0) {
			dup2(fds[1], STDOUT_FILENO);
			dup2(fd_read, STDIN_FILENO);
			if (execlp(argv[i], argv[i], (char *) NULL) == -1) {
				exit(EXIT_FAILURE);
			}
		}
		else {
			int status = 0;
			waitpid(rc1, &status, 0);
			close(fds[1]);
			close(fd_read);
			errno = WEXITSTATUS(status);
			if (errno != 0) 
				exit(errno);
		}
	}

	if (argc >= 3) {
		int rc_last = fork();
		if (rc_last < 0) {
			exit(EXIT_FAILURE);
		}

		else if (rc_last == 0) {
			dup2(fds[0], STDIN_FILENO);
			if (execlp(argv[argc-1], argv[argc-1], (char *) NULL) == -1) {
				exit(EXIT_FAILURE);
			}		
		}

		else {
			int status = 0;
			waitpid(rc_last, &status, 0);
			close(fds[1]);
			errno = WEXITSTATUS(status);
			if (errno != 0) 
				exit(errno);
		}
	}
	return errno;
}
