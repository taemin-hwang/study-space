#include <curl/curl.h>
//#include <json/json.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;


size_t callBackFunk(char* ptr, size_t size, size_t nmemb, string* stream)
{
	int realsize = size * nmemb;
	stream->append(ptr, realsize);
	return realsize;
}

static size_t writefunction(void *ptr, size_t size, size_t nmemb, void *stream)
{
	  fwrite(ptr, size, nmemb, (FILE *)stream);
	    return (nmemb*size);
}

int main() {

	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	std::string chunk;

	std::string strTargetURL;
	std::string strResourceJSON;
	//struct curl_slist *headerlist = nullptr;
	//headerlist = curl_slist_append(headerlist, "Content-Type: application/json");
	strTargetURL = "http://127.0.0.1:50001";
	//strResourceJSON = "{\"snippet\": {\"title\": \"this is title\", \"scheduledStartTime\": \"2017-05-15\"},\"status\": {\"privacyStatus\": \"private\"}}";
	strResourceJSON = "hello";
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, strTargetURL.c_str());
		//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
		//curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strResourceJSON.c_str());

		// 결과 기록
		//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &callBackFunk);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		res = curl_easy_perform(curl);
		//curl_slist_free_all(headerlist);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}

		curl_easy_cleanup(curl);
		std::cout << "------------Result" << std::endl;
		//std::cout << chunk.memory << std::endl;
		return true;
	}

}
