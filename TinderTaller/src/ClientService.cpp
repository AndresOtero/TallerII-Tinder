/*
 * ClientService.cpp
 */

#include "ClientService.h"

ClientService::ClientService() {
	LOG(INFO)<< "Inicio Cliente Service";
}

ClientService::~ClientService() {
	LOG(INFO)<< "Borro Cliente Service";
}

MemoryStruct ClientService::getClientService(const char * url) {
	CURL *curl;
	CURLcode response;

	struct MemoryStruct chunk;
	chunk.memory = (char *) malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl = curl_easy_init();

	/* specify URL to get */
	curl_easy_setopt(curl, CURLOPT_URL, url);

	/* send all data to this function  */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	/* some servers don't like requests that are made without a user-agent
     field, so we provide one */
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	/* get it! */
	response = curl_easy_perform(curl);

	/* check for errors */
	if(response != CURLE_OK) {
		LOG(WARNING)<< "curl_easy_perform() failed: " << curl_easy_strerror(response);
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl);

	/* we're done with libcurl, so clean it up */
	curl_global_cleanup();

	chunk.status = response;
	return chunk;
}

MemoryStruct ClientService::postClientService(const char * url, const char * data){
	CURL *curl;
	CURLcode res;

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	struct MemoryStruct chunk;

	chunk.memory = (char *) malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	//Estructura donde se guardan los datos a enviar.
	struct SendStruct pooh;
	pooh.memory = data;
	pooh.size = strlen(data);

	/* get a curl handle */
	curl = curl_easy_init();

	if(curl) {
		struct curl_slist * headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		/* First set the URL that is about to receive our POST. This URL can
       	   just as well be a https:// URL if that is what should receive the
       	   data. */
		curl_easy_setopt(curl, CURLOPT_URL, url);
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		/* Now specify we want to POST data */
      	curl_easy_setopt(curl, CURLOPT_POST, 1L);
      	/* we want to use our own read function */
      	curl_easy_setopt(curl, CURLOPT_READFUNCTION, readMemoryCallback);
      	/* pointer to pass to our read function */
      	curl_easy_setopt(curl, CURLOPT_READDATA, (void *)&pooh);
      	/* Set the expected POST size. If you want to POST large amounts of data,
      		   consider CURLOPT_POSTFIELDSIZE_LARGE */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (curl_off_t) pooh.size);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

      	/* Perform the request, res will get the return code */
      	res = curl_easy_perform(curl);
      	/* Check for errors */
      	if(res != CURLE_OK) {
      		LOG(WARNING)<< "curl_easy_perform() failed: " << curl_easy_strerror(res);
      	}

      	/* always cleanup */
      	curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	chunk.status = res;
	return chunk;
}

MemoryStruct ClientService::putClientService(const char * url, const char * data){
	CURL *curl;
	CURLcode res;

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	struct MemoryStruct chunk;

	chunk.memory = (char *) malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	/* get a curl handle */
	curl = curl_easy_init();
	if(curl) {
		struct curl_slist * headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	    /* First set the URL that is about to receive our POST. This URL can
	      just as well be a https:// URL if that is what should receive the
	      data. */
	    curl_easy_setopt(curl, CURLOPT_URL, url);
	    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
	    /* Now specify the POST data */
	    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
	      /* Now specify we want to POST data */
	    curl_easy_setopt(curl, CURLOPT_POST, 1L);
	    curl_easy_setopt(curl, CURLOPT_READFUNCTION, readMemoryCallback);
	    /* pointer to pass to our read function */
	    curl_easy_setopt(curl, CURLOPT_READDATA, (void *)&chunk);

	    /* Perform the request, res will get the return code */
	    res = curl_easy_perform(curl);
	    /* Check for errors */
	    if(res != CURLE_OK){
	    	LOG(WARNING)<< "curl_easy_perform() failed: " << curl_easy_strerror(res);
	    }

	    /* always cleanup */
	    curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	chunk.status = res;
	return chunk;
}

MemoryStruct ClientService::deleteClientService(const char * url){
	CURL *curl;
	CURLcode res;

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);
	struct MemoryStruct chunk;

	chunk.memory = (char *) malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	/* get a curl handle */
	curl = curl_easy_init();
	if(curl) {
		struct curl_slist * headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		/* First set the URL that is about to receive our POST. This URL can
		 just as well be a https:// URL if that is what should receive the
		 data. */
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
		/* we want to use our own read function */
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, readMemoryCallback);
		/* pointer to pass to our read function */
		curl_easy_setopt(curl, CURLOPT_READDATA, (void *)&chunk);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK){
			LOG(WARNING)<< "curl_easy_perform() failed: " << curl_easy_strerror(res);
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	chunk.status = res;
	return chunk;
}

