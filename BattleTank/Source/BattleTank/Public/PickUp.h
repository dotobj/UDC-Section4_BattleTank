// Copyright GradeACaffeine.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class BATTLETANK_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
