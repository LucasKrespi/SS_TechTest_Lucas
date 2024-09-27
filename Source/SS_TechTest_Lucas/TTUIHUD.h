// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TTUIHUD.generated.h"

/**
 * 
 */
UCLASS()
class SS_TECHTEST_LUCAS_API ATTUIHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable)
	void HideMainMenu();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenu;
	
};
