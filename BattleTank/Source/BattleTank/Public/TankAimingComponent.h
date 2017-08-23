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
    Locked,
    OutOfAmmo
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
    
    EFiringState GetFiringState() const;
    
	void AimAt( FVector OutHitLocation);
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    int32 GetAmmo() const;
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;
 
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    virtual void BeginPlay() override;

    virtual void TickComponent( float DeltaTime, enum ELevelTick, FActorComponentTickFunction *ThisTickFunction ) override;
    
    bool IsBarrelMoving();
    
    void MoveBarrelTowards( FVector AimDirection );
    
    FVector AimDirection;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 5000.f;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 Ammo = 3;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float AimAccuracy = .01f;
    
    double LastFireTime = 0;
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
};
