// Fill out your copyright notice in the Description page of Project Settings.


#include "TTUIHUD.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void ATTUIHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PC->bShowMouseCursor = true;
	ATTUIHUD* HUD = PC->GetHUD<ATTUIHUD>();

	HUD->ShowMainMenu();
}

void ATTUIHUD::ShowMainMenu()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	MainMenu = CreateWidget<UUserWidget>(PlayerController, MainMenuClass);

	MainMenu->AddToViewport();
}

void ATTUIHUD::HideMainMenu()
{
	if(MainMenu)
	{
		MainMenu->RemoveFromParent();
		MainMenu = nullptr;
	}
}
	
