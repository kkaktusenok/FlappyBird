// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_Bird.h"

#include "Blueprint/UserWidget.h"

// Sets default values
APW_Bird::APW_Bird()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh -> SetupAttachment(RootComponent);
	Mesh -> BodyInstance.bLockXTranslation = true;
	Mesh -> BodyInstance.bLockYTranslation = true;
	Mesh -> BodyInstance.bLockRotation = true;
	Mesh -> BodyInstance.bLockXRotation = true;
	Mesh -> BodyInstance.bLockYRotation = true;
	Mesh -> BodyInstance.bLockZRotation = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom -> SetupAttachment(Mesh);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera -> SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APW_Bird::BeginPlay()
{
	Super::BeginPlay();
	Mesh -> OnComponentHit.AddDynamic(this,&APW_Bird::OnMeshHit);
	Mesh -> BodyInstance.bNotifyRigidBodyCollision = true;
	Mesh -> SetSimulatePhysics(true);

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	
}

// Called every frame
void APW_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APW_Bird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump",IE_Released,this,&APW_Bird::Jump);
}

void APW_Bird::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jumped"));
	Mesh -> BodyInstance.SetLinearVelocity(FVector::UpVector * JumpForce, true);
}

void APW_Bird::OnMeshHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
    FString HitActorName = OtherActor->GetFName().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Hit by %s"), *HitActorName);

	GetWorld()->GetFirstPlayerController()->Pause();
	UUserWidget* WdgRetry = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);
	WdgRetry -> AddToViewport();

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
