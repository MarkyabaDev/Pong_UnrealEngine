// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PONG_API ABall : public AActor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereCollider;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BallMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float InitialSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	int SpeedIncreaseAmountInPercent = 5;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed = 1000.f;

	float CurrentSpeed = 0;

	float CurrentZOffset = 0.6f;

	void StartGameAfterDelay();

	void Move();

	void IncreaseAndReverseSpeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
