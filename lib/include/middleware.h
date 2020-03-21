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
middleware_conn middleware_open(const char *appID, const char *pchHost, int port, void *callback);

int middleware_publish(middleware_conn conn, const char *pchTopic, const char *pchMsg);

/**
 * Close middleware connection.
 *
 * @param conn pointer to connectiob to be disconnected.
 *
 * @return conn pointer to mosquitto connection.
 */
int middleware_close(middleware_conn conn);

#ifdef __cplusplus
}
#endif

#endif
