#pragma once

#include "CoreMinimal.h"
#include "Asteroid.h"
#include "AsteroidChaser.generated.h"

UCLASS()
class TP1_MOTEUR_API AAsteroidChaser : public AAsteroid
{
	GENERATED_BODY()

public:
	AAsteroidChaser();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
