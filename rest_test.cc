#include <iostream>
#include <string>
#include <curl/curl.h>
#include "lib/json-parser/json.h"


using namespace std;

string data; //will hold the url's contents

size_t writeCallback(char *buf, size_t size, size_t nmemb, void *up) { //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c < size * nmemb; c++) {
        data.push_back(buf[c]);
    }
    return size * nmemb; //tell curl how many bytes we handled
}

int main() {
    CURL *curl; //our curl object

    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, "http://pingpongping.cfapps.io/activity");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

    curl_easy_perform(curl);

    cout << endl << data << endl;

    char const *input = data.c_str();

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    json_value res = * json_parse(input, strlen(input));
    json_value *arr = res.u.array.values[0];
    cout << arr->u.object.values[0].value->u.boolean;

    return 0;
}


//#include <iostream>
//#include <string>
//#include <curl/curl.h>
//#include <NotificationCenter/NotificationCenter.h>
//#include "lib/json-parser/json.h"
//
//
//using namespace std;
//
//string data; //will hold the url's contents
//
//size_t writeCallback(char *buf, size_t size, size_t nmemb, void *up) { //callback must have this declaration
//    //buf is a pointer to the data that curl has for us
//    //size*nmemb is the size of the buffer
//
//    for (int c = 0; c < size * nmemb; c++) {
//        data.push_back(buf[c]);
//    }
//    return size * nmemb; //tell curl how many bytes we handled
//}
//
//int main() {
//    CURL *curl; //our curl object
//
//    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
//    curl = curl_easy_init();
//
//    curl_easy_setopt(curl, CURLOPT_URL, "http://pingpongping.cfapps.io/activity");
//    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
//    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress
//
//    curl_easy_perform(curl);
//
//    cout << endl << data << endl;
//
//    char const *input = data.c_str();

//    curl_easy_cleanup(curl);
//    curl_global_cleanup();
//
//    json_value res = * json_parse(input, strlen(input));
//    json_value *arr = res.u.array.values[0];
//
//    printf("\n%s\n", arr->u.object.values[0].name);
////    const int length = list->u.array.length;
//
//    // cout << "Birthday: " << array[i]->u.object.values[j].value->u.string.ptr << endl;
//
////    printf("\n%s\n", list->u.object.values[0].name);
//
//
////    printf("\n%s\n", res->u.object.values[0].name);
////    printf("\n%d\n", res->u.object.values[0].value->u.integer);
////
////    printf("\n%s\n", res->u.object.values[1].name);
////    printf("\n%s\n", res->u.object.values[1].value->u.string.ptr);
//
//    return 0;
//}