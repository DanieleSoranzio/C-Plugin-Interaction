#include "InteractionComponent.h"
#include "InteractInterface.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InteractableActor.h"
#include "InteractionSubsystem.h"
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
        if (AInteractableActor* InteractableActor = Cast<AInteractableActor>(CurrentInteractableActor))
        {
            FInteractionInfo InteractionInfo = InteractableActor->InteractionInfo;
            if (InteractionInfo.bIsActive)
            {
                IInteractInterface::Execute_Interact(CurrentInteractableActor, GetOwner());
            }
        }
    }
}
void UInteractionComponent::UseRadar(AActor* PlayerActor, float RadarRange)
{
    if (FlipFlop)
    {
        FlipFlop = !FlipFlop;
        if (UInteractionSubsystem* Subsystem = GetOwner()->GetGameInstance()->GetSubsystem<UInteractionSubsystem>())
        {
            Subsystem->StartRadar(PlayerActor, RadarRange);
        }
    }
    else
    {
        FlipFlop = !FlipFlop;
        if (UInteractionSubsystem* Subsystem = GetOwner()->GetGameInstance()->GetSubsystem<UInteractionSubsystem>())
        {
            Subsystem->StopRadar();
        }
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
            if (AInteractableActor* InteractableActor = Cast<AInteractableActor>(CurrentInteractableActor))
            {
                FInteractionInfo InteractionInfo = InteractableActor->InteractionInfo;
                if (InteractionInfo.bIsActive)
                {
                    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f);
                }
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
    else
    {
        CurrentInteractableActor = nullptr;
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.1f);
    }
}