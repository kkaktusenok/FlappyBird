// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings.h"

void ABuildings::SpawnPillows()
{
	UE_LOG(LogTemp,Warning,TEXT("Spawning Pillows"));

	for (size_t i = 0; i < Pillows.Num();i++)
	{
		if(Pillows[i])
		{ 
			Pillows[i] -> DestroyComponent();
		}
	}
	Pillows.Empty();
	
	for (size_t i = 0; i < numsOfPillows;i++)
	{
		UStaticMeshComponent* smc = (UStaticMeshComponent*)AddComponentByClass(UStaticMeshComponent::StaticClass(),false, FTransform(),true);
		if(smc)
		{
			smc->RegisterComponent();
			smc->SetMobility(EComponentMobility::Movable);
			smc -> AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			smc ->SetWorldLocation(GetActorLocation() + FVector(0,pillowGap* i,0));
			smc ->SetStaticMesh(PillarMesh);
			Pillows.Add(smc);
		}
	}
	RandomizePillars();
}

void ABuildings::RandomizePillars()
{
	for (size_t i = 0; i < numsOfPillows;i++)
	{
		Pillows[i]->SetWorldScale3D(FVector(1,1,FMath::RandRange(1,6)));
	}
}

// Sets default values
ABuildings::ABuildings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void ABuildings::BeginPlay()
{
	Super::BeginPlay();
	
	
}
void ABuildings::OnConstruction(const FTransform& Transform)
{
	SpawnPillows();
}
// Called every frame
void ABuildings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Move Pillars
	SetActorLocation(GetActorLocation()+FVector(0,MoveSpeed * DeltaTime,0));

	if(GetActorLocation().Y < -1*(pillowGap+4400))
	{
		SetActorLocation(GetActorLocation()+FVector(0, pillowGap * numsOfPillows + screenWith,0));
		RandomizePillars();
	}
}

