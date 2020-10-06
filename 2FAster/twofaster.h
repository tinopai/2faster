#include <iostream>
class TwoFAster {
    public:
        std::string name;
        std::string version;
        std::string loginUri;
        TwoFAster() {
            name = "2FAster";
            version = "1.0a";
            loginUri = "https://localhost:3100/api/v1/login";
        };
};