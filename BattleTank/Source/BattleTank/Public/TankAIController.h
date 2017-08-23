// Copyright GradeACaffeine.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
    
public:
    UFUNCTION()
    void OnTankDeath();
    
protected:
    UPROPERTY(EditDefaultsOnly, Category = "PathFinding")
    float AcceptanceRadius = 10000.f;
	
private:
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    virtual void SetPawn(APawn* InPawn) override;
    
    virtual void BeginPlay() override;
    
    
};
