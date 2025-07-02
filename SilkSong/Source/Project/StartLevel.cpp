#include "StartLevel.h"
#include "GameplayStatics.h"

StartLevel::StartLevel()
{
    GameplayStatics::OpenLevel("FirstLevel");
}