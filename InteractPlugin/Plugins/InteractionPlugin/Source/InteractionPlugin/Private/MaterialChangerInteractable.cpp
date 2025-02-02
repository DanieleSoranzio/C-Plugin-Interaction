#include "MaterialChangerInteractable.h"
#include "Components/StaticMeshComponent.h"

AMaterialChangerInteractable::AMaterialChangerInteractable()
{
    PrimaryActorTick.bCanEverTick = true;

    
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent -> SetupAttachment(RootComponent);
}

void AMaterialChangerInteractable::BeginPlay()
{
    Super::BeginPlay();
}

void AMaterialChangerInteractable::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation( Interactor);
    if (NewMaterial)
    {
        MeshComponent->SetMaterial(0, NewMaterial);
    }
}