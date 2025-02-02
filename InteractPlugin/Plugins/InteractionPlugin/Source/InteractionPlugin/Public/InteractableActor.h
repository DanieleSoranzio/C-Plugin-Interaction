#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "InteractableActor.generated.h"

USTRUCT(BlueprintType)
struct FInteractionInfo
{
    GENERATED_BODY()

public:
  
    FInteractionInfo(): ObjectName(TEXT("")), Location(FVector::ZeroVector),InteractionID(0),bIsActive(false) { }

    UPROPERTY(BlueprintReadWrite, Category = "Interaction")
    FString ObjectName;

    UPROPERTY(BlueprintReadWrite, Category = "Interaction")
    FVector Location;

    UPROPERTY(BlueprintReadWrite, Category = "Interaction")
    int32 InteractionID;

    UPROPERTY(BlueprintReadWrite, Category = "Interaction")
    bool bIsActive;
};

UCLASS()
class INTERACTIONPLUGIN_API AInteractableActor : public AActor, public IInteractInterface
{
    GENERATED_BODY()

public:
    AInteractableActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

   /* UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Interact(AActor* Interactor) override;*/

    virtual void Interact_Implementation(AActor* Interactor) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FInteractionInfo InteractionInfo;
};