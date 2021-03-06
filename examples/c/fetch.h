#ifndef __fetch_h__
#define __fetch_h__

#include <stdlib.h>
#include <stdbool.h>

#include <glib.h>
#include <curl/curl.h>

#include "debug.h"
#include "misc.h"

/**
 * global handle
 */
static CURL *curl = NULL;

static size_t write_callback(char *data, size_t size, size_t nmemb, void *buf)
{
    GString *str = buf;
    g_string_append_len(str, data, size * nmemb);
    return size * nmemb;
}

/* exported symbols */

int fetch_init()
{
    check(curl_global_init(CURL_GLOBAL_DEFAULT) == CURLE_OK, "could not init curl");
    curl = curl_easy_init();
    check(curl, "unable to create an curl handle");
    return HN_OK; 
error:
    return HN_ERR;
}


int fetch_cleanup()
{
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return HN_OK;
}

int fetch(GString *url, GString OUT *body) 
{

    CURLcode status;
    curl_easy_setopt(curl, CURLOPT_URL, GSTR(url));

    check(body, "unable to create buffer");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, body);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    status = curl_easy_perform(curl);

    check(status == CURLE_OK, "failed to performs request: %s", curl_easy_strerror(status));

    return HN_OK;

error:
    return HN_ERR;
}

#endif
