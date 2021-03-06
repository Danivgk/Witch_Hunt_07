// Fill out your copyright notice in the Description page of Project Settings.

#include "FallTree.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UFallTree::UFallTree()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFallTree::BeginPlay()
{
	Super::BeginPlay();

	ActorThatFalls = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UFallTree::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate != nullptr) //If PressurePlate is not empty
	{
		if (PressurePlate->IsOverlappingActor(ActorThatFalls)) /* Then Check if PressurePlate is Overlapping ActorThatOpens */
		{
			FOnFall.Broadcast();
		}
	}
}

