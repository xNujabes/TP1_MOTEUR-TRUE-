// PlayerShip.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Projectile.h"
#include "PlayerShip.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class TP1_MOTEUR_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:
	APlayerShip();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 500.f;

public:
	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cam")
	FVector2D MinBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cam")
	FVector2D MaxBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess="true"))
	class UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	int32 Health = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	int32 Score = 0;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shooting")
	TSubclassOf<AProjectile> ProjectileClass;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Shoot();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float DamageAmount);
};
