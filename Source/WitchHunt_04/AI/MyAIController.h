// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Witch.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class WITCHHUNT_04_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;

	AWitch* GetControlledCharacter() const;

	AWitch* GetPlayerCharacter() const;
};
