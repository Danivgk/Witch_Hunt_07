// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Witch.generated.h"

class UTimelineComponent;

UCLASS()
class WITCHHUNT_04_API AWitch : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Character movement */
	void MoveRight(float value);
	void MoveForward(float value);
	void Jump();
	void StopJump();

	// Returns TopDownCameraComponent
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	// Returns CameraBoom subobject
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool redFlash;

	float CurveFloatValue;
	float TimelineValue;

	//UTimelineComponent* MyTimeline;
	//struct FTimerHandle MemberTimerHandle;
	//struct FTimerHandle MagicTimerHandle;

	/** Get Health */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	/** Get Health Text */
	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	/** Damage Timer */
	UFUNCTION()
		void DamageTimer();

	/** Set Damage State */
	UFUNCTION()
		void SetDamageState();

	/** Play Flash */
	UFUNCTION(BlueprintPure, Category = "Health")
		bool PlayFlash();

	// void ReceivePointDamage(float Damage, const class UDamageType * DamageType, FVector HitLocation, FVector HitNormal, class UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, class AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo);

	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange);

	private:

		// Top down camera 
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
			class UCameraComponent* TopDownCameraComponent;

		// Camera boom positioning the camera above the character
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
			class USpringArmComponent* CameraBoom;

};