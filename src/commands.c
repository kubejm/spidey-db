#include "graph.h"
#include "networking.h"

#include <string.h>
#include <sys/socket.h>

#include <stdio.h>

void commandCommand(Client client) {
  addArrayLength(client, 1);
  addArrayLength(client, 6);
  addBulkString(client, "command");
  addInteger(client, -1);
  addArrayLength(client, 2);
  addSimpleStringReply(client, "loading");
  addSimpleStringReply(client, "stale");
  addInteger(client, 0);
  addInteger(client, 0);
  addInteger(client, 0);

  send(client->fd, client->resp_buf, client->resp_offset, 0);
}

void commandPing(Client client) {
  addSimpleStringReply(client, "PONG");
  send(client->fd, client->resp_buf, client->resp_offset, 0);
}

void commandSetEdge(Client client) {
  addEdge(client->graph, client->req_args[1], client->req_args[2]);

  addSimpleStringReply(client, "OK");
  send(client->fd, client->resp_buf, client->resp_offset, 0);
}

void commandSetVertex(Client client) {
  addVertex(client->graph, client->req_args[1], client->req_args[2]);

  addSimpleStringReply(client, "OK");
  send(client->fd, client->resp_buf, client->resp_offset, 0);
}

void commandGetVertex(Client client) {
  Vertex v = getVertex(client->graph, client->req_args[1]);

  // TODO: more intelligently return this
  char msg[80];
  strcpy(msg, "+");
  strcat(msg, v->value);
  strcat(msg, "\r\n");

  int len = strlen(msg);

  send(client->fd, msg, len, 0);
}

void commandGetNeighbors(Client client) {
  getNeighbors(client->graph, client->req_args[1], 1);

  addSimpleStringReply(client, "OK");
  send(client->fd, client->resp_buf, client->resp_offset, 0);
}
