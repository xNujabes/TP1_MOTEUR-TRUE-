#include "AsteroidChaser.h"
#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"

AAsteroidChaser::AAsteroidChaser()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAsteroidChaser::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAsteroidChaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerShip* Player = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player && AsteroidMesh)
	{
		FVector ToPlayer = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		
		
		InitialDirection = (ToPlayer - GetActorLocation()).GetSafeNormal();


		AsteroidMesh->AddImpulse(InitialDirection * MoveForce);
	}
}

