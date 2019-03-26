// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "Engine/World.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
}

AWitch * AMyAIController::GetControlledCharacter() const
{
	return Cast<AWitch>(GetCharacter());
}

AWitch * AMyAIController::GetPlayerCharacter() const
{
	auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerCharacter) { return nullptr; }
	return Cast<AWitch>(PlayerCharacter);
}
