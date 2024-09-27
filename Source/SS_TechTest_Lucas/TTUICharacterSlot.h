// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTUIButton.h"
#include "TTUICharacterSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTTUIOnCharacterClikedSignature, class UTTUICharacterSlot*, Slot);

USTRUCT(BlueprintType)
struct FCharacterDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ClassIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ClassType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLocked ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CharacterPortrait;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillLevel;
};
/**
 * 
 */
UCLASS()
class SS_TECHTEST_LUCAS_API UTTUICharacterSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	//UUserWidget overrides
	bool Initialize() override;
	void NativeConstruct() override;

	//Delagate Callbacks
	UFUNCTION()
	void OnButtonClicked();

	//Helpers
	EClassType GetClassTypeFromString(FString Type);

protected:

	
	//Widget Binded Proprities
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CharacterName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SkillLevel;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CharacterImage;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ClassIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* LockedImageSelected;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* LockedImage;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* UnlockedImageSelected;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* UnlockedImage;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* NormalBackGround;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SelectedBackGround;

	//Control variables
	EButtonState ButtonCurrentState;

	bool isLocked = true;

	EClassType ClassTypeENum;
	
public:
	
	FTTUIOnCharacterClikedSignature OnCharacterClickDelegate;

	FORCEINLINE void SetButtonState(EButtonState state) { ButtonCurrentState = state; }

	FORCEINLINE bool GetIsLocked() { return isLocked; }
	FORCEINLINE EClassType GetClassType() { return ClassTypeENum; }
	
	void DeselectButton();

	void PopulateSlot(class TTUICharacter* Character);

	void UpdateCard();

	void HideWidget();
	void ShowWidget();
	
};
