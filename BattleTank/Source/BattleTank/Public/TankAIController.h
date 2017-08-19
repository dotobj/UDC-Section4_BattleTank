// Copyright GradeACaffeine.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    virtual void BeginPlay() override;
    
    //UPROPERTY(EditDefaultsOnly, Category = PathFinding)
    float AcceptanceRadius = 3000.f;
};
