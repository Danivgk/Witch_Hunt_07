// Fill out your copyright notice in the Description page of Project Settings.

#include "Witch.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/TimelineComponent.h"


// Sets default values
AWitch::AWitch()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false;

	// Create a camera
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AWitch::BeginPlay()
{
	Super::BeginPlay();
	
	FullHealth = 1000.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;
	bCanBeDamaged = true;
}

float AWitch::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	bCanBeDamaged = false;
	redFlash = true;
	UpdateHealth(-DamageAmount);
	//DamageTimer();
	return DamageAmount;
}

// Called every frame
void AWitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (MyTimeline != nullptr) MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);

}

// Called to bind functionality to input
void AWitch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWitch::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWitch::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWitch::Jump);
	PlayerInputComponent->BindAction("StopJumping", IE_Released, this, &AWitch::StopJumping);

}

void AWitch::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, value);
	}
}

void AWitch::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AWitch::Jump()
{
	bPressedJump = true;
}

void AWitch::StopJump()
{
	bPressedJump = false;
}

float AWitch::GetHealth()
{
	return HealthPercentage;
}

FText AWitch::GetHealthIntText()
{
	int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString HPS = FString::FromInt(HP);
	FString HealthHUD = HPS + FString(TEXT("%"));
	FText HPText = FText::FromString(HealthHUD);
	return HPText;
}

void AWitch::DamageTimer()
{
	bCanBeDamaged = true;
}

void AWitch::SetDamageState()
{//May be changed later
	//GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AWitch::SetDamageState, 2.0f, false);
}

bool AWitch::PlayFlash()
{
	if (redFlash)
	{
		redFlash = false;
		return true;
	}

	return false;
}

void AWitch::UpdateHealth(float HealthChange)
{
	Health = FMath::Clamp(Health += HealthChange, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;
}
