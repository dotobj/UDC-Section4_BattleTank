// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerTank found."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerTank = %s"), *(PlayerTank->GetName()));
    }
}

// Called every frame
void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    if (GetPlayerTank())
    {
        // TODO Move towards player
        
        // Aim towards player
        GetControlledTank()->AimAt( GetPlayerTank()->GetActorLocation() );
        
        // Fire if ready
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) { return nullptr; }
    return Cast<ATank>(PlayerPawn);
}