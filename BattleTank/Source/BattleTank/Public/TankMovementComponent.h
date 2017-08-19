// Copyright GradeACaffeine.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * responsible for driving the tracks
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void IntendMoveForward(float Throw);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void IntendTurnRight(float Throw);
    
private:
    // Call from the pathfinding logic by the AI controllers
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;

};
