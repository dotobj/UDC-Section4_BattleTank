// Copyright GradeACaffeine.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent( float DeltaTime, enum ELevelTick, FActorComponentTickFunction *ThisTickFunction )
{
    if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure (Barrel)) { return false; }
    auto BarrelForward = Barrel->GetForwardVector();
    return !BarrelForward.Equals(AimDirection, .01f);
}

void UTankAimingComponent::AimAt(FVector OutHitLocation )
{
    if (!ensure(Barrel)) { return; }
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation( FName ("Projectile") );
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
        this,
        OutLaunchVelocity,
        StartLocation,
        OutHitLocation,
        LaunchSpeed,
        false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace
     );
    if (bHaveAimSolution) // if an AimSolution was found above, use OutLaunchVelocity
    {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards( AimDirection );
    }
}

void UTankAimingComponent::MoveBarrelTowards( FVector Aim )
{
    if (!ensure(Barrel) || !ensure(Turret)) { return; }
    // convert the unit vector to a rotator
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = Aim.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Turn(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
    if (FiringState != EFiringState::Reloading)
    {
        // Spawn projectile on at socket location on the barrel
        if(!ensure(Barrel)) { return; }
        if(!ensure(ProjectileBlueprint)) { return; }
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                                                              ProjectileBlueprint,
                                                              Barrel->GetSocketLocation(FName("Projectile")),
                                                              Barrel->GetSocketRotation(FName("Projectile"))
                                                              );
        Projectile->LaunchProjectile( LaunchSpeed );
        LastFireTime = FPlatformTime::Seconds();
    }
}
