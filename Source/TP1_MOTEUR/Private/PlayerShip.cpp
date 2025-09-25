#include "PlayerShip.h"
#include "Projectile.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"

APlayerShip::APlayerShip()
{
    PrimaryActorTick.bCanEverTick = true;

    ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
    RootComponent = ShipMesh;

    AutoPossessPlayer = EAutoReceiveInput::Player0; // Le joueur contrôle ce vaisseau

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeGameOnly());
    }

}

void APlayerShip::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        FVector WorldOrigin, WorldDir;
        float MouseX, MouseY;
        if (PC->GetMousePosition(MouseX, MouseY))
        {
            // Déprojection de la souris dans le monde
            PC->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldOrigin, WorldDir);
            
            FPlane GroundPlane(FVector::ZeroVector, FVector::UpVector);
            FVector MouseWorld = FMath::LinePlaneIntersection(
                WorldOrigin,
                WorldOrigin + WorldDir * 10000.f,
                GroundPlane
            );
            
            FVector ToMouse = (MouseWorld - GetActorLocation()).GetSafeNormal2D();

            if (!ToMouse.IsNearlyZero())
            {
                // Rotation uniquement sur le plan XY
                FRotator TargetRotation = ToMouse.Rotation();
                TargetRotation.Pitch = 0.f;
                TargetRotation.Roll = 0.f;

                SetActorRotation(TargetRotation);
            }
        }

        FVector Pos = GetActorLocation();
        Pos.X = FMath::Clamp(Pos.X, MinBounds.X, MaxBounds.X);
        Pos.Y = FMath::Clamp(Pos.Y, MinBounds.Y, MaxBounds.Y);
        SetActorLocation(Pos);

    }
}



void APlayerShip::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->bShowMouseCursor = true;                   // Affiche le curseur
        PC->bEnableClickEvents = true;                 // Active les clics
        PC->bEnableMouseOverEvents = true;             // Active hover
        PC->SetInputMode(FInputModeGameAndUI());       // Permet à la fois les clics UI et actions
    }
}


void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShip::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerShip::MoveRight);

    PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerShip::Shoot);
}

void APlayerShip::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(FVector::ForwardVector, Value);
    }
}

void APlayerShip::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(FVector::RightVector, Value);
    }
}



void APlayerShip::Shoot()
{
    if (!ProjectileClass) 
    {
        UE_LOG(LogTemp, Error, TEXT("ProjectileClass not assigned!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Spawning projectile..."));

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;

    FVector WorldLocation, WorldDirection;
    if (PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
    {
        // Spawn devant le vaisseau
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
        FRotator SpawnRotation = GetActorRotation();

        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
        if (!Projectile)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn projectile!"));
        }
    }
}

void APlayerShip::TakeDamage(float DamageAmount)
{
    Health -= DamageAmount;
}



void APlayerShip::AddScore(int32 Amount)
{
    Score += Amount;
}
