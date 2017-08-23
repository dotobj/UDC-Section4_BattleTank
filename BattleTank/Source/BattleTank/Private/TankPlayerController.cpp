// Copyright GradeACaffeine.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    FoundAimingComponent(AimingComponent);
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }
        
        // subscribe to local method to the tanks death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
    }
}

void ATankPlayerController::OnTankDeath()
{
    StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) { return; } // e.g. if not possessing
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    
    FVector OutHitLocation; // out param
    bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
    if (bGotHitLocation)
    {
        AimingComponent->AimAt(OutHitLocation);
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
        return GetLookVectorHitLocation( LookDirection, OutHitLocation );
    }
    return false;
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
