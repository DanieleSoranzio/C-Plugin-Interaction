#include "InteractableActor.h"
#include "InteractionSubsystem.h"

AInteractableActor::AInteractableActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AInteractableActor::BeginPlay()
{
    Super::BeginPlay();
    InteractionInfo.ObjectName = GetName();
    InteractionInfo.Location = GetActorLocation();
    InteractionInfo.InteractionID = FMath::RandRange(1, 1000);
    InteractionInfo.bIsActive = true;
    if (UInteractionSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UInteractionSubsystem>())
    {
        Subsystem->RegisterInteractable(this);
    }
}

void AInteractableActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractableActor::Interact_Implementation(AActor* Interactor)
{
    InteractionInfo.bIsActive = false;
    if (UInteractionSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UInteractionSubsystem>())
    {
        Subsystem->HandleInteraction(this, InteractionInfo);
    }
}