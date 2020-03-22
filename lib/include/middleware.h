/**************************************************************************
 * middleware.h
 *
 *  Create on: 21/06/2019
 *
 *  Header to middleware
 *
 * Copyrights, 2020
 *
 **************************************************************************/

#ifndef _MIDDLEWARE_H_
#define _MIDDLEWARE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************
 * INCLUDES
 **************************************************************************/
#include <mosquitto.h>
#include <standard-types.h>

/**************************************************************************
 * DEFINITIONS
 **************************************************************************/

#define PUB_QOS 1
#define SUB_QOS 1

/**************************************************************************
 * TYPEDEFS
 **************************************************************************/

typedef	struct mosquitto* middleware_conn;


/**************************************************************************
 * API FUNCTIONS
 **************************************************************************/

/**
 * Open middleware connection.
 *
 * @param appID pointer to Application ID.
 * @param pchHost pointer to Host addres to connect.
 * @param port int to port connection.
 * @param callback pointer to callback function that receive events from mosquito.
 *
 * @return conn pointer to mosquitto connection.
 */
middleware_conn middleware_open(const char *appID, const char *pchHost, int port, void (*on_message)(struct mosquitto *, void *, const struct mosquitto_message *));

/**
 * Publish a message on middleware.
 *
 * @param conn pointer to connection.
 * @param pchTopic pointer to topic to be publish the message.
 * @param pchMsg pointer to message.
 *
 * @return int status to publish.
 */
int middleware_publish(middleware_conn conn, const char *pchTopic, const char *pchMsg);

/**
 * Subscribe to a topic.
 *
 * @param conn pointer to connection.
 * @param pchMessageID pointer to message ID.
 * @param pchSubscribe pointer to subscription pattern.
 *
 * @return int status to subscribe.
 */
int middleware_subscribe(middleware_conn conn, int *pchMessageID, const char *pchSubscribe);

/**
 * Subscribe to a topic callback.
 *
 * @param callback pointer to callback.
 * @param topic pointer to topic ID.
 * @param host pointer to host address.
 * @param port port host.
 *
 * @return int status to subscribe.
 */
int middleware_subscribe_callback(int (*callback)(struct mosquitto *, void *, const struct mosquitto_message *), const char *topic, const char *host, int port);

/**
 * Close middleware connection.
 *
 * @param conn pointer to connection to be disconnected.
 *
 * @return conn pointer to mosquitto connection.
 */
int middleware_close(middleware_conn conn);

#ifdef __cplusplus
}
#endif

#endif
