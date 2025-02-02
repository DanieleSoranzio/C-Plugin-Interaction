#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "MaterialChangerInteractable.generated.h"

UCLASS()
class INTERACTIONPLUGIN_API AMaterialChangerInteractable : public AInteractableActor
{
    GENERATED_BODY()

public:
    AMaterialChangerInteractable();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Interact_Implementation(AActor* Interactor) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, Category = "Materials")
    UMaterialInterface* NewMaterial;
};