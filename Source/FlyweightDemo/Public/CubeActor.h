#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeActor.generated.h"

UCLASS()
class FLYWEIGHTDEMO_API ACubeActor : public AActor
{
	GENERATED_BODY()

public:    
	ACubeActor();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	//Static Mesh for cube
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cube")
	UStaticMeshComponent* MeshComponent;
};
