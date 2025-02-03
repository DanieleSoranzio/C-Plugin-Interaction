#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "InteractInterface.h"


class INTERACTIONPLUGIN_API RadarRunnable : public FRunnable
{
public:
    RadarRunnable(UWorld* World, AActor* PlayerActor, float RadarRange, UMaterialInterface* InOverlayMaterial);
    virtual ~RadarRunnable();

    // FRunnable interface
    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;
    virtual void Exit() override;

    // Funzione per ottenere i risultati del radar
    TArray<AActor*> GetInteractableActors() const;

private:
    UWorld* World; // Riferimento al mondo di gioco
    AActor* PlayerActor; // Riferimento al giocatore
    float RadarRange; // Range del radar

    TArray<AActor*> InteractableActors; // Lista degli oggetti interagibili trovati
    FThreadSafeBool bStopThread; // Flag per fermare il thread
    mutable FCriticalSection Mutex; // Mutex per la sincronizzazione dei dati

    UPROPERTY()
    UMaterialInterface* OverlayMaterialInstance;

    TMap<AActor*, UMaterialInterface*> OverlayMaterials;
};