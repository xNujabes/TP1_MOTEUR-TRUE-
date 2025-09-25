#include "GameManager.h"
#include "AsteroidRandom.h"
#include "AsteroidChaser.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	CurrentSpawnInterval = InitialSpawnInterval;
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	TimeSinceLastSpawn += DeltaTime;

	// Augmente la difficulté progressivement
	if (ElapsedTime >= 1.0f)
	{
		ElapsedTime = 0.0f;
		CurrentSpawnInterval = FMath::Max(CurrentSpawnInterval - DifficultyIncreaseRate, MinSpawnInterval);
	}

	// Spawn si le temps est écoulé
	if (TimeSinceLastSpawn >= CurrentSpawnInterval)
	{
		TimeSinceLastSpawn = 0.0f;
		SpawnAsteroid();
	}
}


void AGameManager::SpawnAsteroid()
{
    if (!RandomAsteroidClass || !ChaserAsteroidClass) return;

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    int32 ViewportX, ViewportY;
    PC->GetViewportSize(ViewportX, ViewportY);

    FVector WorldOrigin, WorldDir;
    FVector TopLeft, TopRight, BottomLeft, BottomRight;

    // Plan Z=0
    FPlane GroundPlane(FVector::ZeroVector, FVector::UpVector);

    auto ProjectToPlane = [&](float ScreenX, float ScreenY) -> FVector
    {
        PC->DeprojectScreenPositionToWorld(ScreenX, ScreenY, WorldOrigin, WorldDir);
        return FMath::LinePlaneIntersection(
            WorldOrigin,
            WorldOrigin + WorldDir * 10000.f,
            GroundPlane
        );
    };

    // Coins écran
    TopLeft     = ProjectToPlane(0.f, 0.f);
    TopRight    = ProjectToPlane(ViewportX, 0.f);
    BottomLeft  = ProjectToPlane(0.f, ViewportY);
    BottomRight = ProjectToPlane(ViewportX, ViewportY);

    // Marge pour spawn hors écran
    const float Margin = 300.f;

    FVector SpawnLocation = FVector::ZeroVector;
    int32 Edge = FMath::RandRange(0, 3);
    switch (Edge)
    {
        case 0:
            SpawnLocation = FMath::Lerp(TopLeft, BottomLeft, FMath::FRand());
            SpawnLocation.X -= Margin;
            break;
        case 1:
            SpawnLocation = FMath::Lerp(TopRight, BottomRight, FMath::FRand());
            SpawnLocation.X += Margin;
            break;
        case 2:
            SpawnLocation = FMath::Lerp(TopLeft, TopRight, FMath::FRand());
            SpawnLocation.Y += Margin;
            break;
        case 3:
            SpawnLocation = FMath::Lerp(BottomLeft, BottomRight, FMath::FRand());
            SpawnLocation.Y -= Margin;
            break;
    }

    SpawnLocation.Z = 0.f;

	float TotalWeight = RandomAsteroidWeight + ChaserAsteroidWeight;
	float Pick = FMath::FRandRange(0.f, TotalWeight);

	TSubclassOf<AActor> AsteroidToSpawn;
	if (Pick <= RandomAsteroidWeight)
	{
		AsteroidToSpawn = RandomAsteroidClass;
	}
	else
	{
		AsteroidToSpawn = ChaserAsteroidClass;
	}

    GetWorld()->SpawnActor<AActor>(AsteroidToSpawn, SpawnLocation, FRotator::ZeroRotator);
}