#include "InteractionSubsystem.h"
#include "Engine/Engine.h"
#include "InteractableActor.h"

void UInteractionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UInteractionSubsystem::Deinitialize()
{
    StopRadar(); 
    Super::Deinitialize();
}

void UInteractionSubsystem::RegisterInteractable(AInteractableActor* Interactable)
{
    if (Interactable)
    {
        Interactables.Add(Interactable);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Updated List of interactable to get: %d"), Interactables.Num()));
        }
    }
}

void UInteractionSubsystem::HandleInteraction(AInteractableActor* Interactable, const FInteractionInfo& InteractionInfo)
{
    if (Interactable && Interactables.Contains(Interactable))
    {
        Interactables.Remove(Interactable);
        UE_LOG(LogTemp, Warning, TEXT("Interacted with: %s at Location: %s"), *InteractionInfo.ObjectName, *InteractionInfo.Location.ToString());
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Interacted with: %s at Location: %s"), *InteractionInfo.ObjectName,  *InteractionInfo.Location.ToString()));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Number of Objects to still interact with: %d"), Interactables.Num()));
        }
        if (Interactables.Num() == 0.f)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("You collected every object! Objects Remaining: %d"), Interactables.Num()));
        }
    }
}


void UInteractionSubsystem::StartRadar(AActor* PlayerActor, float RadarRange)
{
    if (!RadarThread.IsValid())
    {
        RadarThread = MakeUnique<RadarRunnable>(GetWorld(), PlayerActor, RadarRange);
        Thread = FRunnableThread::Create(RadarThread.Get(), TEXT("RadarThread"));
        
        TArray<AActor*> InteractablesRadar = GetInteractableActorsInRange();
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Radar Started")));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("Number of Objects spotted with radar: %d"), InteractablesRadar.Num()));
        }
    }
}

void UInteractionSubsystem::StopRadar()
{
    if (RadarThread.IsValid())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Radar Stopped")));
        RadarThread->Stop();
        if (Thread)
        {
            Thread->WaitForCompletion();
            delete Thread;
            Thread = nullptr;
        }
        RadarThread.Reset();
    }
}

TArray<AActor*> UInteractionSubsystem::GetInteractableActorsInRange() const
{
    if (RadarThread.IsValid())
    {
        return RadarThread->GetInteractableActors();
    }
    return TArray<AActor*>();
}