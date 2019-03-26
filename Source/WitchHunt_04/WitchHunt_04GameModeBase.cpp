// Fill out your copyright notice in the Description page of Project Settings.

#include "WitchHunt_04GameModeBase.h"

#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Witch.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

AWitchHunt_04GameModeBase::AWitchHunt_04GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/Blueprint/Player/MyWitch_BP.MyWitch_BP'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBar(TEXT("WidgetBlueprint'/Game/Widgets/UserWidgetBP.UserWidgetBP'"));
	HUDWidgetClass = HealthBar.Class;

	// use our custom HUD class
	HUDClass = AMyHUD::StaticClass();

	// add Health Bar UI to viewport
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AWitchHunt_04GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGamePlayState::EPlaying);

	MyCharacter = Cast<AWitch>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AWitchHunt_04GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyCharacter)
	{
		if (FMath::IsNearlyZero(MyCharacter->GetHealth(), 0.001f))
		{
			SetCurrentState(EGamePlayState::EGameOver);
		}
	}
}

EGamePlayState AWitchHunt_04GameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void AWitchHunt_04GameModeBase::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void AWitchHunt_04GameModeBase::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
	{
		// do nothing
	}
	break;
	// Unknown/default state
	case EGamePlayState::EGameOver:
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
	break;
	// Unknown/default state
	default:
	case EGamePlayState::EUnknown:
	{
		// do nothing
	}
	break;
	}
}
