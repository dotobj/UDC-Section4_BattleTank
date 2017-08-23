//Copyright GradeACaffeine.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

class UTankAimingComponent;
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
    
public:
    UFUNCTION()
    void OnTankDeath();
    
protected:    
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimingCompRef);
	
private:
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    virtual void BeginPlay() override;
    
    virtual void SetPawn(APawn* InPawn) override;

    // Start moving the barrel of the tank so that a shot would hit where the crosshair intersects the world.
    void AimTowardsCrosshair();
    
    bool GetSightRayHitLocation( FVector& OutHitLocation ) const;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    
    bool GetLookVectorHitLocation( FVector LookDirection, FVector& OutHitLocation ) const;
    
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.f;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333f;
};
