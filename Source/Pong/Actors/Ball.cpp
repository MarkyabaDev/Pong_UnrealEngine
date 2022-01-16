// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	RootComponent = SphereCollider;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	BallMesh->SetupAttachment(RootComponent);

	

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle StartDelayHandle;

	GetWorldTimerManager().SetTimer(StartDelayHandle, this, &ABall::StartGameAfterDelay, 3, false);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ABall::StartGameAfterDelay()
{
	CurrentSpeed = InitialSpeed;
	UE_LOG(LogTemp, Warning, TEXT("Start Game"))
}


void ABall::Move()
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector NewLocation(0, CurrentSpeed * DeltaTime, CurrentZOffset);


	FHitResult SweepHitResult;
	AddActorLocalOffset(NewLocation, true, &SweepHitResult);
	if (SweepHitResult.bBlockingHit && SweepHitResult.GetActor())
	{
		AController* Controller = SweepHitResult.GetActor()->GetInstigatorController();
		if (Controller == nullptr)
		{
			CurrentZOffset *= -1;
		}
		else
		{
			IncreaseAndReverseSpeed();
		}
	}
}

void ABall::IncreaseAndReverseSpeed()
{
	if (CurrentSpeed >= MaxSpeed || CurrentSpeed <= -MaxSpeed)
	{
		CurrentSpeed *= -1;
		return;
	}
	CurrentSpeed *= (SpeedIncreaseAmountInPercent * 0.01f + 1) * -1;
}



