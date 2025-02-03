#include "RadarRunnable.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"


RadarRunnable::RadarRunnable(UWorld* InWorld, AActor* InPlayerActor, float InRadarRange)
    : World(InWorld), PlayerActor(InPlayerActor), RadarRange(InRadarRange), bStopThread(false)
{
}

RadarRunnable::~RadarRunnable()
{
    Stop();
}

bool RadarRunnable::Init()
{
    // Inizializzazione del thread
    bStopThread = false;
    return true;
}

uint32 RadarRunnable::Run()
{
    while (!bStopThread)
    {
        if (World && PlayerActor)
        {
            FVector PlayerLocation = PlayerActor->GetActorLocation();

            // Main Thread For overlaping
            AsyncTask(ENamedThreads::GameThread, [this, PlayerLocation]()
                {
                    if (!World || !PlayerActor) return;

                    TArray<FOverlapResult> OverlapResults;
                    FCollisionQueryParams QueryParams;
                    QueryParams.AddIgnoredActor(PlayerActor);

                    bool bHit = World->OverlapMultiByObjectType(
                        OverlapResults,
                        PlayerLocation,
                        FQuat::Identity,
                        FCollisionObjectQueryParams(FCollisionObjectQueryParams::AllObjects),
                        FCollisionShape::MakeSphere(RadarRange),
                        QueryParams
                    );

                    TArray<AActor*> ActorsInRange;
                    if (bHit)
                    {
                        for (const FOverlapResult& Result : OverlapResults)
                        {
                            AActor* Actor = Result.GetActor();
                            if (Actor && Actor->Implements<UInteractInterface>())
                            {
                                if (!ActorsInRange.Contains(Actor))
                                {
                                    ActorsInRange.Add(Actor);
                                }
                            }
                        }
                    }
                    if (GEngine)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Number of Objects spotted with radar: %d"), ActorsInRange.Num()));
                    }

                    UE_LOG(LogTemp, Warning, TEXT("Radar found %d actors"), ActorsInRange.Num());

                    {
                        FScopeLock Lock(&Mutex);
                        InteractableActors = ActorsInRange;
                    }

                    DrawDebugSphere(World, PlayerLocation, RadarRange, 12, FColor::Blue, false, 0.5f);
                });
        }

        FPlatformProcess::Sleep(0.5f);
        
    }

    return 0;
}
void RadarRunnable::Stop()
{
    // Ferma il thread
    bStopThread = true;
}

void RadarRunnable::Exit()
{
    // Pulizia del thread
}

TArray<AActor*> RadarRunnable::GetInteractableActors() const
{
    // Blocca l'accesso alla lista degli oggetti interagibili
    FScopeLock Lock(&Mutex);
    return InteractableActors;
}