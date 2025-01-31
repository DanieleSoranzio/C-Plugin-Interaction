#include "InteractableActor.h"
#include "InteractionSubsystem.h"

AInteractableActor::AInteractableActor()
{
    PrimaryActorTick.bCanEverTick = true;

    InteractionInfo.ObjectName = GetName();
    InteractionInfo.Location = GetActorLocation();
    InteractionInfo.InteractionID = FMath::RandRange(1, 1000);
    InteractionInfo.bIsActive = true;
}

void AInteractableActor::BeginPlay()
{
    Super::BeginPlay();

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
    if (UInteractionSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UInteractionSubsystem>())
    {
        Subsystem->HandleInteraction(this, InteractionInfo);
    }
}