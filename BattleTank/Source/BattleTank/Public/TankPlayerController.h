// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    virtual void BeginPlay() override;
    
    ATank* GetControlledTank() const;
    
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
