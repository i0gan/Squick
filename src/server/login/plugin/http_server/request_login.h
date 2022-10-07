

#include "squick/base/request.h"

class RequestLogin : public IRequest
{
public:
	std::string user;
	std::string password;

};

AJSON(RequestLogin, user, password)