#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StreamableManager.h"
#include "InteractableActor.h"
#include "Engine/AssetManager.h"
#include "MeshChanger.generated.h"

UCLASS()
class INTERACTIONPLUGIN_API AMeshChanger : public AInteractableActor
{
    GENERATED_BODY()

public:
    AMeshChanger();

protected:
    virtual void BeginPlay() override;

    void LoadMeshAsync();

    UPROPERTY(EditAnywhere, Category = "Mesh")
    TSoftObjectPtr<UStaticMesh> MeshToLoad;  

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaticMeshComponent;

public:
    UFUNCTION(BlueprintCallable, Category = "Mesh")
    void ApplyMesh(); 

    virtual void Interact_Implementation(AActor* Interactor) override;

private:
    UStaticMesh* LoadedMesh = nullptr;  
    bool bIsMeshLoaded = false; 
    bool bPendingApplyMesh = false;  
};
