// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Turn( float RelativeSpeed )
{
    // rotate the yaw of the barrel towards this rotation
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto TurnChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto Turn = RelativeRotation.Yaw + TurnChange;
    SetRelativeRotation(FRotator (0, Turn, 0));
}
