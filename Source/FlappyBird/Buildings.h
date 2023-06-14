// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Buildings.generated.h"

UCLASS()
class FLAPPYBIRD_API ABuildings : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<UStaticMeshComponent*> Pillows;

	UPROPERTY(EditAnywhere)
	int numsOfPillows = 10;

	UPROPERTY(EditAnywhere)
	float pillowGap = 100.f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 10.f;

	UPROPERTY(EditAnywhere)
	float screenWith = 1000.f;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* PillarMesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	UFUNCTION(BlueprintCallable)
	void SpawnPillows();
	
	UFUNCTION(BlueprintCallable)
	void RandomizePillars();
	
public:	
	// Sets default values for this actor's properties
	ABuildings();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
