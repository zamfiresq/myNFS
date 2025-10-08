#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>
#include "nfs.h"

#ifndef SERVER_IP
#define SERVER_IP "192.168.64.3"
#endif

#define MAX_FILES 10  // maxim 10 fisiere in director

/* wrapper pt ls_1 */
char **safe_ls(CLIENT *clnt) {
    char *arg = "";
    char **res = ls_1(&arg, clnt);
    if (!res) return NULL;

    static char *copy[MAX_FILES + 1] = {NULL};
    for (int i = 0; i < MAX_FILES; i++) {
        copy[i] = NULL;  // initializare
        if (res[i] != NULL)
            copy[i] = strdup(res[i]);
        else
            break;
    }
    copy[MAX_FILES] = NULL;
    return copy;
}

/* wrapper pt create_1 */
int safe_create(CLIENT *clnt, const char *filename) {
    char *arg = (char *)filename;
    int *res = create_1(&arg, clnt);
    if (!res) {
        clnt_perror(clnt, "create_1 failed");
        return -1;
    }
    return *res;
}

/* wrapper pt delete_1 */
int safe_delete(CLIENT *clnt, const char *filename) {
    char *arg = (char *)filename;
    int *res = delete_1(&arg, clnt);
    if (!res) {
        clnt_perror(clnt, "delete_1 failed");
        return -1;
    }
    return *res;
}

int main(int argc, char *argv[]) {
    const char *server = (argc > 1) ? argv[1] : SERVER_IP;
    CLIENT *clnt = clnt_create((char *)server, NFS_PROGRAM, NFS_VERSION_1, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(server);
        return 1;
    }

    printf("Connected to server %s\n", server);

    /* ------------------ ls ------------------ */
    char **ls_res = safe_ls(clnt);
    if (ls_res == NULL) {
        clnt_perror(clnt, "ls_1 failed");
    } else {
        printf("=== Lista fisiere ===\n");
        char *line = strtok(*ls_res, "\n");
        int idx = 1;
        while (line != NULL) {
            printf("%2d | %s\n", idx++, line);
            line = strtok(NULL, "\n");
        }
        printf("====================\n");
    }

    /* ------------------ create ------------------ */
    const char *new_file = "newfile.txt";
    int status = safe_create(clnt, new_file);
    if (status == 0) {
        printf("File %s created successfully\n", new_file);
    } else {
        fprintf(stderr, "Failed to create file %s\n", new_file);
    }

    /* ------------------ delete ------------------ */
    int del_status = safe_delete(clnt, new_file);
    if (del_status == 0) {
        printf("File %s deleted successfully\n", new_file);
    } else {
        fprintf(stderr, "Failed to delete file %s\n", new_file);
    }

    /* ------------------ cleanup ------------------ */
    clnt_destroy(clnt);
    return 0;
}
