/*
* 
	� 2FAster
	Implement your own offline 2FA on your applications faster!

*/

#include <iostream>
#include <curl/curl.h>
#include "twofaster.h"
#pragma comment(lib, "lib/libcurl.lib")

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


int super_private_after_login_function(std::string username) {
	std::cout << "\n[SUPER-PRIVATE-AFTER-LOGIN-FUNCTION] Hello " << username << "\n";
	return 1;
}

// This is an example login with 2FA for a Windows Machine
int main() {
	/* Welcome title and descrption */
	std::cout << "\033[1;96m" << "2FAster" << "\033[1;90m" << "\nImplement your own offline 2FA on your applications faster!" << "\033[1;0m\n\n";

	/* Actual application */
	// Intialize variables
	std::string username, password, code2fa;

	std::cout << "Username: ";
	std::cin >> username;
	std::cout << "Password: ";
	std::cin >> password;
	std::cout << "2FA code: ";
	std::cin >> code2fa;

    //TwoFAster application();

	CURL* curl;
	CURLcode res;

	std::string postData = "{ \"username\": \"" + username + "\", \"password\": \"" + password + "\", \"twofactor\": \"" + code2fa + "\" }";


	std::string readBuffer;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");

		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3100/api/v1/login");
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "2FAster");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		// Add headers
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

		// Get response from web
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);


		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	/* This is just an example response with an example check
	*  You shouldn't trust {"success":true}. Specially if your super_private_after_login_function contains
	*  super_private_information_only_admins_are_able_to_access
	* 
	*  https://www.oreilly.com/library/view/http-developers-handbook/0672324547/0672324547_ch22lev1sec1.html
	*/
	if(readBuffer == "{\"success\":true}") return super_private_after_login_function(username);
}
