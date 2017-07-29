// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

/**
 * 
 */
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
    
    UPROPERTY(EditAnywhere)
    float Reach = 2500.f;
    
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333f;
    
    FVector GetTraceLineStart() const;
    
    FVector GetTraceLineEnd() const;
    
};
