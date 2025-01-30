// Copyright Epic Games, Inc. All Rights Reserved.

#include "InteractPluginGameMode.h"
#include "InteractPluginCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInteractPluginGameMode::AInteractPluginGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
