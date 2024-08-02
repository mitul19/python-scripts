/**
 *  GeoLocation via google API.
 * 
 * 
 * 
 **/

#include<iostream>
#include<string>
#include<list>
#include "cJSON.h"
#include<curl/curl.h>

#define BASE_URL "https://www.googleapis.com/geolocation/v1/geolocate?key="
#define APIKEY "xxx"
#define REQ_URL BASE_URL APIKEY
#define DEBUG 1

using namespace std;

class GeolocationRequest
{
    public:
    void getLocation(char *jsonPayLoad);
    void printLocationInfo(char *response);

    private:
    struct MemoryStruct {
        char *memory;
        size_t size;  
    };
    static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

void GeolocationRequest::getLocation(char *jsonPayLoad)
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();

    if(curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        struct MemoryStruct chunk;
        chunk.memory = NULL;
        chunk.size = 0; 

        curl_easy_setopt(curl, CURLOPT_URL, REQ_URL);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayLoad);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            cerr << "ERROR: curl_easy_perform() failed: " << endl;
        }
        else
        {
            printLocationInfo(chunk.memory);
        }
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        free(chunk.memory);
    }
    else
    {
        cerr << "ERROR: curl_easy_init() failed: " << endl;
    }
}

void GeolocationRequest::printLocationInfo(char *response) 
{
    const cJSON *location = NULL;
    const cJSON *latitude = NULL;
    const cJSON *longitude = NULL;
    const cJSON *accuracy = NULL;

    cJSON *parsedJSON = cJSON_Parse(response);
    if(parsedJSON == NULL) {
        const char *errorPtr = cJSON_GetErrorPtr();
        if(errorPtr != NULL) {
            cerr << "ERROR: cJSON_GetErrorPtr returned: " << errorPtr << endl;
        }
        goto end;
    }

    location = cJSON_GetObjectItemCaseSensitive(parsedJSON, "location");
    if (location == NULL) goto end;

    latitude = cJSON_GetObjectItemCaseSensitive(location, "lat");
    longitude =  cJSON_GetObjectItemCaseSensitive(location, "lng");
    accuracy =  cJSON_GetObjectItemCaseSensitive(parsedJSON, "accuracy");
	if ((latitude != NULL) && (longitude != NULL) && (accuracy != NULL))
	{
		cout << endl << "You are within " << cJSON_Print(accuracy) << "m of "
		                                  << cJSON_Print(latitude) << "N "
								          << cJSON_Print(longitude) << "E" << endl;
	}

end:
    if(DEBUG) cout << cJSON_Print(parsedJSON) << endl;
    cJSON_Delete(parsedJSON);
}

/* memory callback to capture response from curl POST request */
size_t GeolocationRequest::writeMemoryCallback(void *contents, size_t size, size_t nmemb, void* userp) 
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr) {
		cerr << "ERROR: writeMemoryCallback failed to allocate memory" << endl;
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

int main()
{
    //wifi access points load
    FILE * fp = fopen("sample.json","r");
    if (fp == NULL) {
        cerr << "Error: unable to open sample.json. " << endl;
        return 1;
    }
    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);
    // cout << buffer << endl;
    cJSON *json = cJSON_Parse(buffer);
    char * jsonPayload = cJSON_Print(json);

    GeolocationRequest request;
    request.getLocation(jsonPayload);
    
    if(DEBUG) cout << jsonPayload << endl;


    return 0;
}