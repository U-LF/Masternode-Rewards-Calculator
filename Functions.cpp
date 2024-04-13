#include "Libraries.h"

using json = nlohmann::json;
using namespace std;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

static int GetMasterNodeCount () {

    CURL* curl;
    CURLcode res;
    string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://explorer.neoxa.net/api/getmasternodecount");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            return 0;
        }
        else {
            try {
                auto jsonResponse = json::parse(response);

                return jsonResponse["enabled"];
            }
            catch (json::parse_error& e) {
                return 0;
            }
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}