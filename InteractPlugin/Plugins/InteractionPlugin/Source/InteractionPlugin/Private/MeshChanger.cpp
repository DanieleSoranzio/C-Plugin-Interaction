#include "MeshChanger.h"
#include "Components/StaticMeshComponent.h"

AMeshChanger::AMeshChanger()
{
    PrimaryActorTick.bCanEverTick = false;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = StaticMeshComponent;
}

void AMeshChanger::BeginPlay()
{
    Super::BeginPlay();
    LoadMeshAsync();  
}

void AMeshChanger::LoadMeshAsync()
{
    if (MeshToLoad.IsNull())
    {
        UE_LOG(LogTemp, Warning, TEXT("MeshToLoad is NULL! Assign a mesh in the editor."));
        return;
    }

    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

    Streamable.RequestAsyncLoad(
        MeshToLoad.ToSoftObjectPath(),
        [this]()
        {
            // Store the loaded mesh
            LoadedMesh = Cast<UStaticMesh>(MeshToLoad.Get());
            bIsMeshLoaded = true;
            UE_LOG(LogTemp, Warning, TEXT("Mesh Loaded Successfully!"));

            
            if (bPendingApplyMesh)
            {
                ApplyMesh();
            }
        },
        FStreamableManager::DefaultAsyncLoadPriority,
        false
    );
}

void AMeshChanger::ApplyMesh()
{
    if (bIsMeshLoaded && LoadedMesh)
    {
        if (StaticMeshComponent)
        {
            StaticMeshComponent->SetStaticMesh(LoadedMesh);
            UE_LOG(LogTemp, Warning, TEXT("Mesh Applied Successfully!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Mesh not loaded yet, deferring application..."));
        bPendingApplyMesh = true;  
    }
}

void AMeshChanger::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);
    ApplyMesh();

}
