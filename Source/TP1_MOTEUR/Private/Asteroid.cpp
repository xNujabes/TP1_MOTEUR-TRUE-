#include "Asteroid.h"
#include "PlayerShip.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = true;

	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMesh"));
	RootComponent = AsteroidMesh;
	
	AsteroidMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AsteroidMesh->SetCollisionObjectType(ECC_PhysicsBody);
	AsteroidMesh->SetSimulatePhysics(true);
	AsteroidMesh->SetEnableGravity(false);
	AsteroidMesh->BodyInstance.bLockZTranslation = true; // reste 2D

	
	InitialLifeSpan = 10.0f;

	Health = FMath::RandRange(1, 5); // Vie aléatoire entre 1 et 5 par défaut
	ScoreValue = Health * 10;
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsteroid::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0.f)
	{
		Destroy();
	}
}
