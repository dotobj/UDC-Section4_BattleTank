// Copyright GradeACaffeine.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();
    
    if (!ensure(PlayerTank && ControlledTank)) { return; }
    // Move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);
        
    // Aim towards player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt( PlayerTank->GetActorLocation() );
        
    // Fire if ready
    AimingComponent->Fire();
}
