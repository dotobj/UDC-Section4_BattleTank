// Copyright GradeACaffeine.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());
    
    if(ensure(PlayerTank))
    {
        // Move towards player
        MoveToActor(PlayerTank, AcceptanceRadius);
        
        // Aim towards player
        ControlledTank->AimAt( PlayerTank->GetActorLocation() );
        
        // Fire if ready
        ControlledTank->Fire();
    }
}
