// Copyright GradeACaffeine.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
    
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    void LaunchProjectile( float Speed );

private:
    UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Setup")
    UStaticMeshComponent* CollisionMesh = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Setup")
    UParticleSystemComponent* LaunchBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Setup")
    UParticleSystemComponent* ImpactBlast = nullptr;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
