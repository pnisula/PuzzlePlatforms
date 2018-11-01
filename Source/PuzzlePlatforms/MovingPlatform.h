// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
		
public:	
	AMovingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Move Setup")
	float Speed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Move Setup", Meta = (MakeEditWidget = true))
	FVector TargetLocation;
	
	UFUNCTION()
	void AddActiveTrigger();

	UFUNCTION()
	void RemoveActiveTrigger();
private:
	UPROPERTY()
	FVector GlobalTargetLocation;
	
	UPROPERTY()
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
};
