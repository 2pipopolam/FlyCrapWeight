#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeSpawner.generated.h"

UENUM(BlueprintType)
enum class ESpawnMethod : uint8
{
    Normal UMETA(DisplayName = "Normal Spawn"),
    Flyweight UMETA(DisplayName = "Flyweight Spawn")
};

UCLASS()
class FLYWEIGHTDEMO_API ACubeSpawner : public AActor
{
    GENERATED_BODY()
    
public:    
    ACubeSpawner();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    void SpawnCubesNormal();
    
    void SpawnCubesFlyweight();
    
    void ToggleSpawnMethod();
    
    void ClearNormalCubes();
    
    void SetupInput(class UInputComponent* PlayerInputComponent);

    void LogSpawnTime() const;

public:    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    int32 NumberOfCubes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    ESpawnMethod CurrentSpawnMethod;

private:
    // Hierarchical Instanced Static Mesh comp. for Flyweight spawn
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
    class UHierarchicalInstancedStaticMeshComponent* InstancedMesh;


    bool bHasSpawned;

    
    float SpawnStartTime;
    float SpawnEndTime;

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UUserWidget> SpawnMethodWidgetClass;

    UPROPERTY()
    class UUserWidget* SpawnMethodWidgetInstance;
};
