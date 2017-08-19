// Copyright GradeACaffeine.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:  
    void AimAt( FVector OutHitLocation );
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
    UTankAimingComponent* TankAimingComponent = nullptr;
    
private:
	// Sets default values for this pawn's properties
	ATank();
        
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 5000.f;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.;
    
    UTankBarrel* Barrel = nullptr; // TODO remove
    
    double LastFireTime = 0;
};
