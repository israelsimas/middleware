/**************************************************************************
 *
 * middleware.c
 *
 *    Middlware wrapper to Mosquitto.
 *
 * Copyright 2020
 *
 **************************************************************************/

#include <string.h>
#include <middleware.h>
#include <utils.h>

#define THIS_FILE "middleware.c"

middleware_conn middleware_open(const char *appID, const char *pchHost, int port, void (*on_message)(struct mosquitto *, void *, const struct mosquitto_message *)) {

  int status;
  middleware_conn mosq;

  if (!appID) {
    log_error("Invalid appID to connect middleware");
  }

  if ((!pchHost) || (port <= 0)) {
    log_error("Invalid host or port to connect middleware");
  }

  mosquitto_lib_init();

  mosq = mosquitto_new(appID, true, NULL);
  if (!mosq) {
    log_error("Middleware can not create instance");
    return NULL;
  }

  if (on_message) {
    mosquitto_message_callback_set(mosq, on_message);
  }

  status = mosquitto_connect(mosq, pchHost, port, false);
  if (status) {
    log_error("Middleware can not connect to host %s and port %d", pchHost, port);
    mosquitto_destroy(mosq);
    return NULL;
  }

  return mosq;
}

int middleware_publish(middleware_conn conn, const char *pchTopic, const char *pchMsg) {

  if (!pchTopic || !pchMsg) {
    log_error("Invalid topic or message to send on middleware");
    return ERROR;
  }  

  return mosquitto_publish(conn, NULL, pchTopic, strlen(pchMsg), pchMsg, PUB_QOS, false);
}

int middleware_subscribe(middleware_conn conn, int *pchMessageID, const char *pchSubscribe) {

  if (!pchSubscribe) {
    log_error("Invalid subscribe pattern");
  }

  return mosquitto_subscribe(conn, pchMessageID, pchSubscribe, SUB_QOS);
}

int middleware_close(middleware_conn conn) {
  return mosquitto_disconnect(conn);
}
