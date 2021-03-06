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

	ResetPosition = GetActorLocation();
	BallMesh->OnComponentBeginOverlap.AddDynamic(this, &ABall::ABall::OnOverlapOutTrigger);

	BeginRound();
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
}


void ABall::Move()
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector NewLocation(0, CurrentSpeed * DeltaTime, CurrentZOffset * DeltaTime);


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
	CurrentZOffset = FMath::FRandRange(MinZOffset, MaxZOffset);
	if (CurrentSpeed >= MaxSpeed || CurrentSpeed <= -MaxSpeed)
	{
		CurrentSpeed *= -1;
		return;
	}
	CurrentSpeed *= (SpeedIncreaseAmountInPercent * 0.01f + 1) * -1;
}

void ABall::BeginRound()
{
	CurrentZOffset = 0;
	CurrentSpeed = 0;
	SetActorLocation(ResetPosition);

	FTimerHandle StartDelayHandle;
	GetWorldTimerManager().SetTimer(StartDelayHandle, this, &ABall::StartGameAfterDelay, 3, false);
}

void ABall::OnOverlapOutTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Name of Other Actor: %s"), *OtherActor->GetName());
	}

	BeginRound();
}


