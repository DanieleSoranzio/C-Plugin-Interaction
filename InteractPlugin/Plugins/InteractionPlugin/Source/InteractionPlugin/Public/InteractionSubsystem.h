#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RadarRunnable.h"
#include "InteractableActor.h"
#include "InteractionSubsystem.generated.h"

UCLASS()
class INTERACTIONPLUGIN_API UInteractionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    void StartRadar(AActor* PlayerActor, float RadarRange);
    void StopRadar();
    TArray<AActor*> GetInteractableActorsInRange() const;

    void RegisterInteractable(class AInteractableActor* Interactable);
    void HandleInteraction(class AInteractableActor* Interactable, const FInteractionInfo& InteractionInfo);

private:
    TArray<class AInteractableActor*> Interactables;
    TUniquePtr<RadarRunnable> RadarThread;
    FRunnableThread* Thread = nullptr;
};