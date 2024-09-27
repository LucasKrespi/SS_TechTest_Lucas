// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTUIMainHUD.generated.h"

/**
 * 
 */
UCLASS()
class SS_TECHTEST_LUCAS_API UTTUIMainHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	//UUserWidget overrides
	void NativeConstruct() override;
	void SynchronizeProperties() override;
	
	//Delgate Callback
	UFUNCTION()
	void OnClassButtonClicked(UTTUIButton* ClikedButton);
	UFUNCTION()
	void OnCharacterSlotClicked(UTTUICharacterSlot* ClikedButton);
	UFUNCTION()
	void OnShowLockedToggleChange(bool IsChecked);

	//Init functions
	void PopulateButtonArray();
	void CreateCharacters();
	//Filter
	void FilterIsLocked(bool ShowLocked);

protected:

	//Binded Widgets
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTTUIButton* SelectClassButtonOne;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTTUIButton* SelectClassButtonTwo;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTTUIButton* SelectClassButtonTree;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTTUIButton* SelectClassButtonFour;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTTUIButton* SelectClassButtonFive;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTTUIToggle* ShowLockedToggle;

	//UI Current use widgets
	UTTUIButton* CurrentSelectedButton;
	class UTTUICharacterSlot* CurrentSelectedSlot;

	bool IsShowLocked = true;

	TArray<UTTUIButton*> ClassSelectionButtons;

	//Character Selection
	//Variables are initialized because SynchronizeProperties() happens on editor
	UPROPERTY(EditAnywhere, Category = "Character Selection Panel")
	int32 Columns = 5;

	UPROPERTY(EditAnywhere, Category = "Character Selection Panel")
	int32 Rows = 3;

	UPROPERTY(EditAnywhere, Category = "Character Selection Panel")
	TSubclassOf<class UTTUICharacterSlot> ItemWidgetClass = nullptr; //TODO: Change UUserWidget to Custom Button class

	UPROPERTY(BlueprintReadOnly, Category = "Character Selection Panel", meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> Grid;

	TArray<class UTTUICharacterSlot*> CharactersSlots;
	TArray<class UUniformGridSlot*> Slots;
};
