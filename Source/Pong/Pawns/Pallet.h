// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pallet.generated.h"

UCLASS()
class PONG_API APallet : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* PalletMesh;

	void Move(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	APallet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
