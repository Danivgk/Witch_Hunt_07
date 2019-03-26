// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WitchHunt_04GameModeBase.generated.h"

class AWitch;

UENUM()
enum class EGamePlayState
{
	EPlaying,
	EGameOver,
	EUnknown
};

/**
 * 
 */
UCLASS()
class WITCHHUNT_04_API AWitchHunt_04GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AWitchHunt_04GameModeBase();

		AWitch* MyCharacter;

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;


	/** Returns the current playing state */
	UFUNCTION(BlueprintPure, Category = "Health")
		EGamePlayState GetCurrentState() const;

	/** Sets a new playing state */
	void SetCurrentState(EGamePlayState NewState);

	UPROPERTY(EditAnywhere, Category = "Health")
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Health")
		class UUserWidget* CurrentWidget;

private:
	
	/**Keeps track of the current playing state */
	EGamePlayState CurrentState;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(EGamePlayState NewState);

	
};
