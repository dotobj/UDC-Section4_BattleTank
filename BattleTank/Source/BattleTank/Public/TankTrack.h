// Copyright GradeACaffeine.

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
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);
	
    // max force per track in nextons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 400000.; // assume 40 tonne tank, and 1g acceleration
	
private:
    UTankTrack();
    
    virtual void BeginPlay() override;
    
    void ApplySidewaysForce();
    
    void DriveTrack();
    
    float CurrentThrottle = 0.0f;
        
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
