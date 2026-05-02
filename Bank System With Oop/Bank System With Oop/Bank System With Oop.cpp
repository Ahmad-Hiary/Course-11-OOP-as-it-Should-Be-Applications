#include <iostream>
#include "clsDate.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <string>
#include "clsUtil.h"
#include "clsMainScreen.h"
#include "clsString.h"
#include <vector>
#include <iomanip>
#include "clsLogInScreen.h"

using namespace std;



int main()
{

    while (true)
    {

        if (!clsLogInScreen::ShowLogInScreen())
            break;
       
    }
}