// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed )
{
    if (!Barrel) { return; }
    
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
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards( AimDirection );
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f Aim solve found"), Time);
    }
    else
    {
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f No aim solve found"), Time);
    }
}

void UTankAimingComponent::MoveBarrelTowards( FVector AimDirection )
{
    // convert the unit vector to a rotator
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(5);
}
