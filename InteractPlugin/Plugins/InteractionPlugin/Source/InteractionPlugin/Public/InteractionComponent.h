#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INTERACTIONPLUGIN_API UInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInteractionComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void PerformInteraction();

    UFUNCTION(BlueprintCallable, Category = "Radar")
    void UseRadar(AActor* PlayerActor, float RadarRange);

private:
    void FindInteractableActor();

    UPROPERTY(EditAnywhere, Category = "Interaction")
    float InteractionRange = 500.0f;

    bool FlipFlop = true;

    AActor* CurrentInteractableActor = nullptr;
};