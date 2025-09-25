// Asteroid.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class TP1_MOTEUR_API AAsteroid : public AActor
{
	GENERATED_BODY()

public:
	AAsteroid();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AsteroidMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForce = 100000.f;

	UPROPERTY(EditAnywhere)
	FVector InitialDirection;

	
private:
	UPROPERTY(EditAnywhere)
	float TimeToLive = 10.0f;
	

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	int32 ScoreValue;

	UFUNCTION(BlueprintCallable, Category = "Asteroid")
	void TakeDamage(float DamageAmount);
};
