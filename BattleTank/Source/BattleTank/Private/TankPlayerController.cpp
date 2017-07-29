// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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
        //UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *OutHitLocation.ToString());
        // tell controlled tank to aim at this point
    }
}

// get world location of linetrace though crosshair, true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation ) const
{
    // ray-cast out to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT HitResult,
                                            GetTraceLineStart(),
                                            GetTraceLineEnd(),
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldDynamic),
                                            TraceParams
                                            );
    // find crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D((ViewportSizeX*CrossHairXLocation), (ViewportSizeY*CrossHairYLocation));
    
    // de-project the screen position of the crosshair to a world direction
    // line trace along that look direction and see what we hit
    OutHitLocation = FVector(1.0);
    return true;
}

FVector ATankPlayerController::GetTraceLineStart() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation);
    return PlayerViewPointLocation;
}

FVector ATankPlayerController::GetTraceLineEnd() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation);
    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}