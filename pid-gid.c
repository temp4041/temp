#include <stdio.h>
#include <unistd.h>

int main() {
    // Call getuid() to get the real user ID (UID) of the current process
    uid_t uid = getuid();
    printf("Real User ID (UID): %d\n", uid);

    // Call getgid() to get the real group ID (GID) of the current process
    gid_t gid = getgid();
    printf("Real Group ID (GID): %d\n", gid);

    // Call geteuid() to get the effective user ID (EUID) of the current process
    uid_t euid = geteuid();
    printf("Effective User ID (EUID): %d\n", euid);

    // Call getegid() to get the effective group ID (EGID) of the current process
    gid_t egid = getegid();
    printf("Effective Group ID (EGID): %d\n", egid);

    return 0;
}

