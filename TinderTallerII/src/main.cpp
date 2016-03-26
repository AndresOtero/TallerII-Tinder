
#include "../lib/mongoose.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../lib/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#include <cstdio>
#include <string>
#include <json/json.h>
#include <assert.h>
#include "rocksdb/db.h"


std::string kDBPath = "/tmp/rocksdb_simple_example";


/** Implementacion de server web**/

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

int logg()
{
	   LOG(INFO) << "My first info log using default logger";

    return 0;
}


int rocksdb_basic() {
 rocksdb::DB *db;
 rocksdb::Options options;
 options.create_if_missing = true;
 rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb/", &db);
 printf(status.ok() ? "true" :"false");

 assert(status.ok());
 return 0;
}
static void ev_handler(struct mg_connection *nc, int ev, void *p) {
  if (ev == MG_EV_HTTP_REQUEST) {
    mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
  }
}
void basic_server(){
	struct mg_mgr mgr;
	  struct mg_connection *nc;
	  mg_mgr_init(&mgr, NULL);
	  nc = mg_bind(&mgr, s_http_port, ev_handler);

	  // Set up HTTP server parameters
	  mg_set_protocol_http_websocket(nc);
	  s_http_server_opts.document_root = ".";  // Serve current directory
	  s_http_server_opts.dav_document_root = ".";  // Allow access via WebDav
	  s_http_server_opts.enable_directory_listing = "yes";

	  printf("Starting web server on port %s\n", s_http_port);
	  for (;;) {
	    mg_mgr_poll(&mgr, 1000);
	  }
	  mg_mgr_free(&mgr);


}

int main(int argc,char*  argv[]) {
	// Initialize Google's logging library.
	rocksdb_basic();
	logg();
	basic_server();
    return 0;
}
