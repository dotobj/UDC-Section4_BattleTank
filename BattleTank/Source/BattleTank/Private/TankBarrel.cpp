// Copyright GradeACaffeine.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate( float RelativeSpeed )
{
    // rotate the pitch of the barrel towards this rotation
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator (Elevation, 0, 0));
}
