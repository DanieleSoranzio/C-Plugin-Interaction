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
    }
}

void UInteractionSubsystem::HandleInteraction(AInteractableActor* Interactable, const FInteractionInfo& InteractionInfo)
{
    if (Interactable)
    {
        UE_LOG(LogTemp, Warning, TEXT("Interacted with: %s at Location: %s"),
            *InteractionInfo.ObjectName,
            *InteractionInfo.Location.ToString());
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
                FString::Printf(TEXT("Interacted with: %s at Location: %s"),
                    *InteractionInfo.ObjectName,
                    *InteractionInfo.Location.ToString()));
        }
    }
}

void UInteractionSubsystem::StartRadar(AActor* PlayerActor, float RadarRange)
{
    if (!RadarThread.IsValid())
    {
        RadarThread = MakeUnique<RadarRunnable>(GetWorld(), PlayerActor, RadarRange);
        Thread = FRunnableThread::Create(RadarThread.Get(), TEXT("RadarThread"));
    }
}

void UInteractionSubsystem::StopRadar()
{
    if (RadarThread.IsValid())
    {
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