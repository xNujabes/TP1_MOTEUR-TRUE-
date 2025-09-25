#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class TP1_MOTEUR_API AGameManager : public AActor
{
	GENERATED_BODY()

public:
	AGameManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category="Asteroids")
	TSubclassOf<class AAsteroidRandom> RandomAsteroidClass;

	UPROPERTY(EditAnywhere, Category="Asteroids")
	TSubclassOf<class AAsteroidChaser> ChaserAsteroidClass;

	UPROPERTY(EditAnywhere, Category="Asteroids")
	float InitialSpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, Category="Asteroids")
	float MinSpawnInterval = 0.5f;

	UPROPERTY(EditAnywhere, Category="Asteroids")
	float DifficultyIncreaseRate = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Asteroids")
	float RandomAsteroidWeight = 0.7f;

	UPROPERTY(EditAnywhere, Category = "Asteroids")
	float ChaserAsteroidWeight = 0.3f;


	float CurrentSpawnInterval;
	float TimeSinceLastSpawn = 0.0f;
	float ElapsedTime = 0.0f;

	void SpawnAsteroid();
};
