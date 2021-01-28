#include "networking.h"

#include <string.h>
#include <sys/socket.h>

void commandCommand(Request req, int clt_fd) {
  char *msg = "*1\r\n*6\r\n$7\r\ncommand\r\n:-1\r\n*2\r\n+loading\r\n+"
              "stale\r\n:0\r\n:0\r\n:0\r\n";
  int len = strlen(msg);

  send(clt_fd, msg, len, 0);
}
