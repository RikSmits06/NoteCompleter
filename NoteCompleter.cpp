#include <fstream>
#include <iostream>
#include <string>

#include "AutoComplete/autoComplete.h"
#include "AutoComplete/trieComplete.h"
#include "Gui/App.h"


int main(int argc, char* argv[])
{
    App app;
    app.run();
    app.destroy();
}
