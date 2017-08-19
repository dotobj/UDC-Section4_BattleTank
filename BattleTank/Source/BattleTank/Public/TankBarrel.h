// Copyright GradeACaffeine.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // -1 is max downward movement and +1 is max up movement
    void Elevate( float RelativeSpeed );
	
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 10;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxElevationDegrees = 45;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinElevationDegrees = 0;
};
