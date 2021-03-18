/*
 *  'Alternative to Alternative To (name subject to change)' Copyright (C) 2021 Anthony Beckett
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <json-c/json.h>
#include <curl/curl.h> 
#include <lexbor/html/parser.h>
#include <stdio.h>
#include <stdlib.h>


#define TMP_PATH "/tmp/curl_results.html"


int
check_file(char file[])
{
	FILE* chk;
	if ((chk = fopen(file, "r"))) {
		fclose(chk);
		return 1;
	}
	return 0;
}


char
get_results(char url[], char path[])
{
	CURL* curl = curl_easy_init();
	FILE* file;

	file = fopen(TMP_PATH, "w");

	if (curl) {
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		return 1;
	}
	fclose(file);
	return 0;
}


int
main(int argc, char* argv[])
{
	int arg_len = strlen(argv[1]);
	static const char URL[35] = "https://alternativeto.net/software/";
	char full_url[35 + arg_len];
	static const char PATH[19] = "/tmp/alternativeto/";
	char full_path[19 + arg_len];
	char page;

	snprintf(full_url, sizeof(full_url) + 2, "%s%s/", URL, argv[1]);
	snprintf(full_path, sizeof(full_path) + 1, "%s%s", PATH, argv[1]);

	if (!check_file(full_path)) {
		page = get_results(full_url, full_path);
	}
	
	return 0;
}
