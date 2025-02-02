#include "DestructibleInteractable.h"

ADestructibleInteractable::ADestructibleInteractable()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADestructibleInteractable::BeginPlay()
{
    Super::BeginPlay();
}

void ADestructibleInteractable::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);
    Destroy();
}