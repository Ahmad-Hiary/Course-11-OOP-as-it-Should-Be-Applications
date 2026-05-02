#pragma once

#include <iostream>

using namespace std;
class clsInterfaceCommunication
{
public:


	virtual void SendEmail(string Title ,string Body) = 0;
	virtual void SendFax(string Title, string Body) = 0;
	virtual void SendSmS(string Title, string Body) = 0;

	
};

