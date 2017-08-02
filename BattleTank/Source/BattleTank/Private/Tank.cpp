// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    TankAimingComponent= CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet )
{
    TankAimingComponent->SetBarrelReference( BarrelToSet );
    Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet )
{
    TankAimingComponent->SetTurretReference( TurretToSet );
}

void ATank::Fire()
{
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    
    if(Barrel && isReloaded)
    {
        // Spawn projectile on at socket location on the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                                            ProjectileBlueprint,
                                            Barrel->GetSocketLocation(FName("Projectile")),
                                            Barrel->GetSocketRotation(FName("Projectile"))
                                            );
        Projectile->LaunchProjectile( LaunchSpeed );
        LastFireTime = FPlatformTime::Seconds();
    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void ATank::AimAt( FVector OutHitLocation )
{
    TankAimingComponent->AimAt( OutHitLocation, LaunchSpeed );
}
