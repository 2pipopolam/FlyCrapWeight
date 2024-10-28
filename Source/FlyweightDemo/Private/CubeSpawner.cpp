#include "CubeSpawner.h"
#include "CubeActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"


//class constructor
ACubeSpawner::ACubeSpawner()
{
    PrimaryActorTick.bCanEverTick = true;

    CurrentSpawnMethod = ESpawnMethod::Normal;
    NumberOfCubes = 1000;
    bHasSpawned = false;

    // Hierarchical Instanced Static Mesh component for Flyweight Spawn
    InstancedMesh = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
    RootComponent = InstancedMesh;

    // default cube
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        InstancedMesh->SetStaticMesh(CubeMesh.Object);
    }

    // InstancedMesh optimization
    InstancedMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Disable collision
    InstancedMesh->SetCullDistance(2000.f); // cutoff distance
    InstancedMesh->SetMobility(EComponentMobility::Static); // Optimize for static instances
    InstancedMesh->CastShadow = false; // Turning off drop shadows
    
    EnableInput(nullptr);
}


void ACubeSpawner::BeginPlay()
{
    Super::BeginPlay();
    
    InstancedMesh->SetVisibility(false); 

    SpawnCubesNormal();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->InputComponent = NewObject<UInputComponent>(PlayerController);
        PlayerController->InputComponent->RegisterComponent();
        PlayerController->EnableInput(PlayerController);
        SetupInput(PlayerController->InputComponent);
    }

    if (SpawnMethodWidgetClass)
    {
        SpawnMethodWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), SpawnMethodWidgetClass);
        if (SpawnMethodWidgetInstance)
        {
            SpawnMethodWidgetInstance->AddToViewport();

            UTextBlock* TextBlock = Cast<UTextBlock>(SpawnMethodWidgetInstance->GetWidgetFromName("SpawnMethodText"));
            if (TextBlock)
            {
                FString MethodText = (CurrentSpawnMethod == ESpawnMethod::Normal) ? TEXT("Normal Spawn") : TEXT("Flyweight Spawn");
                TextBlock->SetText(FText::FromString(FString::Printf(TEXT("Current Method: %s"), *MethodText)));
            }
        }
    }
}


void ACubeSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACubeSpawner::SpawnCubesNormal()
{
    if (bHasSpawned)
        return;

    bHasSpawned = true;

    SpawnStartTime = FPlatformTime::Seconds();

    UWorld* World = GetWorld();
    if (World)
    {
        for (int32 i = 0; i < NumberOfCubes; ++i)
        {
            FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(FVector(0.0f, 0.0f, 0.0f), FVector(1000.0f, 1000.0f, 0.0f));
            FRotator Rotation = FRotator::ZeroRotator;

            World->SpawnActor<ACubeActor>(ACubeActor::StaticClass(), Location, Rotation);
        }
    }

    SpawnEndTime = FPlatformTime::Seconds();
    LogSpawnTime();
}

void ACubeSpawner::SpawnCubesFlyweight()
{
    if (bHasSpawned)
        return;

    bHasSpawned = true;

    SpawnStartTime = FPlatformTime::Seconds();

    UWorld* World = GetWorld();
    if (World)
    {
        
        ClearNormalCubes();
        
        InstancedMesh->SetVisibility(false);

        //  reserving memory for transformation
        TArray<FTransform> InstanceTransforms;
        InstanceTransforms.Reserve(NumberOfCubes);

        // generate all instance transformations
        for (int32 i = 0; i < NumberOfCubes; ++i)
        {
            FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(
                FVector(-500.0f, -500.0f, 0.0f), 
                FVector(500.0f, 500.0f, 0.0f)
            );
            FRotator Rotation = FRotator::ZeroRotator;
            FVector Scale = FVector(1.0f);

            InstanceTransforms.Emplace(FTransform(Rotation, Location, Scale));
        }

        // all instances in batch
        InstancedMesh->AddInstances(InstanceTransforms, /*bShouldReturn */ true);
        
        InstancedMesh->SetVisibility(true);
    }

    SpawnEndTime = FPlatformTime::Seconds();
    LogSpawnTime();
}

void ACubeSpawner::ToggleSpawnMethod()
{
    if (CurrentSpawnMethod == ESpawnMethod::Normal)
    {
        CurrentSpawnMethod = ESpawnMethod::Flyweight;
    }
    else
    {
        CurrentSpawnMethod = ESpawnMethod::Normal;
    }

    UWorld* World = GetWorld();
    if (World)
    {
        if (CurrentSpawnMethod == ESpawnMethod::Normal)
        {
            InstancedMesh->ClearInstances();
            InstancedMesh->SetVisibility(false);
            
            SpawnCubesNormal();
        }
        else
        {
            ClearNormalCubes();
            SpawnCubesFlyweight();
        }

        if (SpawnMethodWidgetInstance)
        {
            UTextBlock* TextBlock = Cast<UTextBlock>(SpawnMethodWidgetInstance->GetWidgetFromName("SpawnMethodText"));
            if (TextBlock)
            {
                FString MethodText = (CurrentSpawnMethod == ESpawnMethod::Normal) ? TEXT("Normal Spawn") : TEXT("Flyweight Spawn");
                TextBlock->SetText(FText::FromString(FString::Printf(TEXT("Current Method: %s"), *MethodText)));
            }
        }
    }
}

void ACubeSpawner::SetupInput(UInputComponent* PlayerInputComponent)
{
    if (PlayerInputComponent)
    {
        PlayerInputComponent->BindAction("ToggleSpawnMethod", IE_Pressed, this, &ACubeSpawner::ToggleSpawnMethod);
    }
}

void ACubeSpawner::ClearNormalCubes()
{
    UWorld* World = GetWorld();
    if (World)
    {
        for (TActorIterator<ACubeActor> It(World); It; ++It)
        {
            It->Destroy();
        }
    }
}



void ACubeSpawner::LogSpawnTime() const
{
    float SpawnDuration = SpawnEndTime - SpawnStartTime;
    UE_LOG(LogTemp, Warning, TEXT("Spawned %d cubes in %f seconds using method: %s"),
        NumberOfCubes,
        SpawnDuration,
        (CurrentSpawnMethod == ESpawnMethod::Normal) ? TEXT("Normal") : TEXT("Flyweight"));

    if (SpawnMethodWidgetInstance)
    {
        UTextBlock* TextBlock = Cast<UTextBlock>(SpawnMethodWidgetInstance->GetWidgetFromName("SpawnMethodText"));
        if (TextBlock)
        {
            FString MethodText = (CurrentSpawnMethod == ESpawnMethod::Normal) ? TEXT("Normal Spawn") : TEXT("Flyweight Spawn");
            FString TimeText = FString::Printf(TEXT("Spawned %d cubes in %.2f seconds"), NumberOfCubes, SpawnDuration);
            TextBlock->SetText(FText::FromString(FString::Printf(TEXT("Current Method: %s\n%s"), *MethodText, *TimeText)));
        }
    }
}
