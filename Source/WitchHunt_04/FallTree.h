// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "FallTree.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFall);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WITCHHUNT_04_API UFallTree : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFallTree();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Blueprintassignable)
		FOnFall FOnFall;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	AActor* ActorThatFalls = nullptr;
};
