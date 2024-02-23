#include <iostream>
#include <string>
#include <curl/curl.h>

// static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
// {
//     ((std::string *)userp)->append((char *)contents, size * nmemb);
//     return size * nmemb;
// }

// static size_t header_callback(char *buffer, size_t size,
//                               size_t nitems, void *userdata)
// {
//   /* received header is nitems * size long in 'buffer' NOT ZERO TERMINATED */
//   /* 'userdata' is set with CURLOPT_HEADERDATA */
//   return nitems * size;
// }

// int main(void)
// {
//     CURL *curl;
//     CURLcode res;
//     std::string readBuffer;

//     curl = curl_easy_init();
//     if (curl)
//     {
//         curl_easy_setopt(curl, CURLOPT_URL, "http://mpatel.akamaized.net/quote.jpg");
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//         curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);

//         res = curl_easy_perform(curl);
//         /* Check for errors */
//         if (res != CURLE_OK)
//             fprintf(stderr, "curl_easy_perform() failed: %s\n",
//                     curl_easy_strerror(res));

//         curl_easy_cleanup(curl);

//         std::cout << readBuffer << std::endl;
//     }
//     return 0;
// }

static void dump(const char *text,
                 FILE *stream, unsigned char *ptr, size_t size)
{
    size_t i;
    size_t c;
    unsigned int width = 0x10;

    fprintf(stream, "%s, %10.10ld bytes (0x%8.8lx)\n",
            text, (long)size, (long)size);

    for (i = 0; i < size; i += width)
    {
        fprintf(stream, "%4.4lx: ", (long)i);

        /* show hex to the left */
        for (c = 0; c < width; c++)
        {
            if (i + c < size)
                fprintf(stream, "%02x ", ptr[i + c]);
            else
                fputs("   ", stream);
        }

        /* show data on the right */
        for (c = 0; (c < width) && (i + c < size); c++)
        {
            char x = (ptr[i + c] >= 0x20 && ptr[i + c] < 0x80) ? ptr[i + c] : '.';
            fputc(x, stream);
        }

        fputc('\n', stream); /* newline */
    }
}

static int my_trace(CURL *handle, curl_infotype type,
                    char *data, size_t size,
                    void *clientp)
{
    const char *text;
    (void)handle; /* prevent compiler warning */
    (void)clientp;

    switch (type)
    {
    case CURLINFO_TEXT:
        fputs("== Info: ", stderr);
        fwrite(data, size, 1, stderr);
    default: /* in case a new one is introduced to shock us */
        return 0;

    case CURLINFO_HEADER_OUT:
        text = "=> Send header";
        break;
    case CURLINFO_DATA_OUT:
        text = "=> Send data";
        break;
    case CURLINFO_SSL_DATA_OUT:
        text = "=> Send SSL data";
        break;
    case CURLINFO_HEADER_IN:
        text = "<= Recv header";
        break;
    case CURLINFO_DATA_IN:
        text = "<= Recv data";
        break;
    case CURLINFO_SSL_DATA_IN:
        text = "<= Recv SSL data";
        break;
    }

    dump(text, stderr, (unsigned char *)data, size);
    return 0;
}

int main(void)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);

        /* the DEBUGFUNCTION has no effect until we enable VERBOSE */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_URL, "http://api.open-notify.org/astros.json");
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_easy_setopt(curl, CURLOPT_URL, "http://api.open-notify.org/astros.json");
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return 0;
}