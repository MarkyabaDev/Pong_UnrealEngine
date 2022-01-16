// Fill out your copyright notice in the Description page of Project Settings.


#include "Pallet.h"

#include "Components/BoxComponent.h"

// Sets default values
APallet::APallet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxComponent;

	PalletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pallet Mesh"));
	PalletMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APallet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APallet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APallet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move"), this, &APallet::Move);
}

void APallet::Move(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move: %f"), Value)
}


