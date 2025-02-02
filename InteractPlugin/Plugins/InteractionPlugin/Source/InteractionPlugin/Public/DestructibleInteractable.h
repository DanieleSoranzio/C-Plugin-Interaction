#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "DestructibleInteractable.generated.h"

UCLASS()
class INTERACTIONPLUGIN_API ADestructibleInteractable : public AInteractableActor
{
    GENERATED_BODY()

public:
    ADestructibleInteractable();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Interact_Implementation(AActor* Interactor) override;
};