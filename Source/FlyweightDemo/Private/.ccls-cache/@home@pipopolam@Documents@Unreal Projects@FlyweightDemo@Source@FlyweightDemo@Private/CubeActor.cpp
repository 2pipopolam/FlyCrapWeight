#include "CubeActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACubeActor::ACubeActor()
{
  PrimaryActorTick.bCanEverTick = true;

  // creating and attaching of Static Mesh
  MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
  RootComponent = MeshComponent;
  
  static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
  if (CubeMesh.Succeeded())
    {
      MeshComponent->SetStaticMesh(CubeMesh.Object);
      MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    }
}

void ACubeActor::BeginPlay()
{
  Super::BeginPlay();    
}

void ACubeActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}
