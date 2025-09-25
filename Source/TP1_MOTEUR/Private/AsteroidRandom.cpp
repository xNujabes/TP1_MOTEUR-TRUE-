#include "AsteroidRandom.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

void AAsteroidRandom::BeginPlay()
{
	Super::BeginPlay();

	// Récupérer le PlayerController
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;

	int32 ViewportX, ViewportY;
	PC->GetViewportSize(ViewportX, ViewportY);

	// Générer un point aléatoire dans l'écran visible
	float RandX = FMath::FRandRange(0.f, (float)ViewportX);
	float RandY = FMath::FRandRange(0.f, (float)ViewportY);

	FVector WorldOrigin, WorldDir;
	PC->DeprojectScreenPositionToWorld(RandX, RandY, WorldOrigin, WorldDir);

	// Intersection avec le plan Z = 0
	FPlane GroundPlane(FVector::ZeroVector, FVector::UpVector);
	FVector TargetLocation = FMath::LinePlaneIntersection(
		WorldOrigin,
		WorldOrigin + WorldDir * 10000.f,
		GroundPlane
	);

	// Direction vers ce point
	InitialDirection = (TargetLocation - GetActorLocation()).GetSafeNormal();

	// Impulsion de départ
	AsteroidMesh->AddImpulse(InitialDirection * MoveForce);
}
