#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;
	ProjectileMesh->SetCollisionProfileName("BlockAllDynamic");

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1500.f;
	MovementComp->MaxSpeed = 1500.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->ProjectileGravityScale = 0.f; // pas de gravité pour un tir spatial

	// TTL automatique
	InitialLifeSpan = 2.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(InitialLifeSpan);                                                
}


