#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int rc;
    uid_t uid = getuid();
    struct passwd *passwd = getpwuid(uid);
    if (passwd == NULL)
        goto error;
    if (strcmp(passwd->pw_name, "sbuild") == 0)
    {
        passwd = getpwnam("sbuild-slave");
        if (passwd == NULL)
            goto error;
        uid = passwd->pw_uid;
    }
    rc = setuid(uid);
    if (rc != 0)
        goto error;
	execv("/usr/bin/dpkg-buildpackage", argv);
error:
    perror(NULL);
    exit(1);
}

/* vim:set ts=4 sw=4 et:*/
