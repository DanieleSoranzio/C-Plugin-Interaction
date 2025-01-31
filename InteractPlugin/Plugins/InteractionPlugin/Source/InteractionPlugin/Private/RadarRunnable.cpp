#include "RadarRunnable.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
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
            TArray<AActor*> FoundActors;
            UGameplayStatics::GetAllActorsWithInterface(World, UInteractInterface::StaticClass(), FoundActors);

            TArray<AActor*> ActorsInRange;

            for (AActor* Actor : FoundActors)
            {
                if (Actor && Actor->GetDistanceTo(PlayerActor) <= RadarRange)
                {
                    ActorsInRange.Add(Actor);
                }
            }

            // Blocca l'accesso alla lista degli oggetti interagibili
            FScopeLock Lock(&Mutex);
            InteractableActors = ActorsInRange;
        }

        // Aspetta un po' prima di eseguire di nuovo la ricerca
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