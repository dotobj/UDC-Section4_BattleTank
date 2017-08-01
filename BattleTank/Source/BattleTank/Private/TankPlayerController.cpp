// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No possesed Pawn found."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerPawn = %s"), *(ControlledTank->GetName()));
    }
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }
    
    FVector OutHitLocation; // out param
    if (GetSightRayHitLocation(OutHitLocation))
    {
        GetControlledTank()->AimAt(OutHitLocation);
    }
}

// get world location of linetrace though crosshair, true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation ) const
{
    // find crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D((ViewportSizeX*CrossHairXLocation), (ViewportSizeY*CrossHairYLocation));
    
    // de-project the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // line trace along that look direction and see what we hit
        GetLookVectorHitLocation( LookDirection, OutHitLocation );
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // to be discarded, but must be given
    return DeprojectScreenPositionToWorld(
                                    ScreenLocation.X,
                                    ScreenLocation.Y,
                                    CameraWorldLocation,
                                    LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation( FVector LookDirection, FVector& OutHitLocation ) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + ( LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(
                                             HitResult,
                                             StartLocation,
                                             EndLocation,
                                             ECollisionChannel::ECC_Visibility
                                             ))
    {
        OutHitLocation = HitResult.Location;
        return true;
    }
        OutHitLocation = FVector(0.0);
        return false;
}
