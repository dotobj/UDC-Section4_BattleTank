// Copyright GradeACaffeine.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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

void ATank::AimAt( FVector OutHitLocation )
{
    TankAimingComponent->AimAt( OutHitLocation, LaunchSpeed );
}
