// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"

#include "TP_TopDown/TP_TopDownPlayerController.h"
#include "TP_TopDown/TP_TopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACGameMode::ACGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATP_TopDownPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}