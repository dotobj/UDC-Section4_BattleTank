// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);
	
    // max force per track in nextons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 400000.; // assume 40 tonne tank, and 1g acceleration
	
    UPROPERTY(EditDefaultsOnly)
    FVector ForceLocationOffset = FVector(-150, 0, 0);
};
