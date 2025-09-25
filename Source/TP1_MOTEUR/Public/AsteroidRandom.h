#pragma once

#include "CoreMinimal.h"
#include "Asteroid.h"
#include "AsteroidRandom.generated.h"

UCLASS()
class TP1_MOTEUR_API AAsteroidRandom : public AAsteroid
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
