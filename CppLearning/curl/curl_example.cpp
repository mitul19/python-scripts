/*
 * Curl Utiliy written by Mitul Patel.
 * It uses various open Source APIs to make cURL.
 * https://curl.se/libcurl/c/example.html
 * https://everything.curl.dev/libcurl/libcurl
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

const bool VERBOSE = true;
const bool RESPONSE_HEADER = true;
const bool RESPONSE_BODY = true;
const int PCONN_TRY = 12;
const int SLEEP = 1;

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int main(void)
{
    CURL *curl;
    struct curl_slist *host = NULL;
    struct curl_slist *list = NULL;
    FILE *verbosefile = fopen("verbose.out", "wb");
    FILE *headerfile = fopen("head.out", "wb");
    FILE *bodyfile = fopen("body.out", "wb");

    host = curl_slist_append(NULL, "mpatel-localhost.akamaized.net:443:198.18.64.72");
    list = curl_slist_append(list, "pragma: akamai-x-cache-on,akamai-x-cache-remote-on,akamai-x-flush-log,akamai-x-serial-no,akamai-x-no-ssl-client-session-caching,akamai-x-get-ssl-client-session-id, akamai-x-write-v-log-line,\
akamai-x-get-log-sym-key, akamai-x-get-cache-key,akamai-x-get-true-cache-key,akamai-x-get-cache-filename,akamai-x-get-extracted-values,akamai-x-reset-adaptive-connect-timeout,akamai-x-check-cacheable, akamai-x-rate-limiting-data,\
akamai-x-get-request-id, akamai-x-cache-only, akamai-x-get-mdc-data,akamai-x-get-client-ip, akamai-x-get-tpca-info, akamai-x-feo-trace, akamai-x-feo-trace-verbose, akamai-x-feo-trace-full,akamai-x-feo-trace-formatted,\
akamai-x-get-match-regex-profile, akamai-x-tapioca-trace, akamai-x-get-sync-dns-cname-chain,akamai-x-get-saas-query-info, akamai-x-get-purge-info, akamai-x-get-cache-tags, akamai-x-get-devpops-info, akamai-x-get-brotli-status");

    list = curl_slist_append(list, "X-Akamai-Request-ID:mpateltest");

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl = curl_easy_init();

    /* set URL and other curl paramater to get */
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(curl, CURLOPT_RESOLVE, host);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_URL, "https://mpatel-localhost.akamaized.net/connect-timeout");
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    /* Use below ignore cert verification and host verification  */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    /* send all data to this function  */
    /* ask libcurl to show us the verbose output */
    /* we want the Verbose be written to this file handle */
    if (VERBOSE)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_STDERR, verbosefile);
    }

    /* we want the headers be written to this file handle */
    if (RESPONSE_HEADER)
    {
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, headerfile);
    }

    /* we want the body be written to this file handle instead of stdout */
    if (RESPONSE_BODY)
    {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, bodyfile);
    }

    /* get it as desired.! */
    for (int i = 0; i < PCONN_TRY; ++i)
    {
        curl_easy_perform(curl);
        sleep(SLEEP);
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl);
    curl_slist_free_all(list);
    curl_slist_free_all(host);

    /* Close files */
    fclose(bodyfile);
    fclose(headerfile);
    fclose(verbosefile);

    return 0;
}