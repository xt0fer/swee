#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "pico/stdlib.h"

#define CTRL_KEY(k) ((k) & 0x1f)
#define RUN (-1)

struct edConf {
    int _errno;
    int screenrows;
    int screencols;
};

struct edConf E;

void initEditor() {
    E._errno = RUN;
    E.screencols = 80;
    E.screenrows = 24;
}

void writ(char *s, int l) {
    int i;
    for (i = 0; i < l; i++) {
        putchar(s[i]);
    }
}

void editorDrawRows() {
    int y;
    for(y=0; y< E.screenrows; y++) {
        writ("~\r\n", 3);
    }
}

void editorRefreshScreen() {
    writ("\x1b[2J",4);
    writ("\x1b[H",3);
    editorDrawRows();
    writ("\x1b[H",3);
}

char editorReadKey() {
    return getchar();
}

void editorProcessKey() {
    char c = editorReadKey();
    switch (c) {
        case CTRL_KEY('q'):
            printf("\nQuit.\n");
            E._errno = 0;
            break;
    }
}
int main() {
    // stdio_init_all();
    stdio_uart_init();
    initEditor();
    //char *ver = "\nkshell v0.1\n";
    //writ(ver, strlen(ver));
    while(E._errno == RUN) {
        editorRefreshScreen();
        editorProcessKey();
    }
    //printf("\nexiting..\n");

    return E._errno;
}

void die(const char *s) {
    perror(s);
    E._errno = 1;
}

int getCursor(int *rows, int *cols) {
        writ("\x1b[2J",4);

}