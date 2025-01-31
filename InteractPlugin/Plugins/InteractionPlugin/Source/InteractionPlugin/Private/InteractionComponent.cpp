#include "InteractionComponent.h"
#include "InteractInterface.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //FindInteractableActor();
}

void UInteractionComponent::PerformInteraction()
{
    FindInteractableActor();
    if (CurrentInteractableActor && CurrentInteractableActor->Implements<UInteractInterface>())
    {
        IInteractInterface::Execute_Interact(CurrentInteractableActor, GetOwner());
    }
}

void UInteractionComponent::FindInteractableActor()
{
    FVector Start = GetOwner()->GetActorLocation();
    FVector End = Start + GetOwner()->GetActorForwardVector() * InteractionRange;

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && HitActor->Implements<UInteractInterface>())
        {
            CurrentInteractableActor = HitActor;
            DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f);
        }
        else
        {
            CurrentInteractableActor = nullptr;
            DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.1f);
        }
    }
    else
    {
        CurrentInteractableActor = nullptr;
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.1f);
    }
}