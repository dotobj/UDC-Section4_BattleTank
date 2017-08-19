// Copyright GradeACaffeine.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked
};

// Forward Declaration
class AProjectile;
class UTankBarrel;
class UTankTurret;

// Holds parameters for Barrel properties and ElevateMethod
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();
    
	void AimAt( FVector OutHitLocation);
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;
 
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 5000.f;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.;
        
    double LastFireTime = 0;
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    void MoveBarrelTowards( FVector AimDirection );
};
