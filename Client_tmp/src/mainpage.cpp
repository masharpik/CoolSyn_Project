#include "mainpage.h"

MainPage::MainPage() :
    mainPageLayout(this),
    inputZone(),
    outputZone()
{
  mainPageLayout.addWidget(&inputZone);
  mainPageLayout.addWidget(&outputZone);
}

