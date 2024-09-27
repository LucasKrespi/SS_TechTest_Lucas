// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTUIButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTTUIOnClikedSignature, class UTTUIButton*, Button);

UENUM(BlueprintType)
enum class EClassType : uint8
{
	ALL UMETA(DisplayName = "All"),
	SUPPORT UMETA(DisplayName = "Support"),
	TANK UMETA(DisplayName = "Tank"),
	BRAWLER UMETA(DisplayName = "Brawler"),
	ASSASIN UMETA(DisplayName = "Assasin")
};

UENUM()
enum class EButtonState : uint8
{
	NORMAL,
	HOVERED,
	ACTIVE
};

USTRUCT(BlueprintType)
struct FClassDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ClassIcon;
};

/**
 * 
 */
UCLASS()
class SS_TECHTEST_LUCAS_API UTTUIButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	//UUserWidget overrides
	bool Initialize() override;
	void NativeOnInitialized() override;
	void NativeConstruct() override;
	//===
	virtual void InitiButton();
	
	//Delegate Callbacks
	UFUNCTION()
	void OnButtonHovered();
	UFUNCTION()
	void OnButtonClicked();

	//Init Functions
	void InitStyles();

	//Update
	void UpdateStyle();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Type", meta = (AllowPrivateAccess = "true"))
	EClassType ClassType;

	EButtonState ButtonCurrentState;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ClassIconImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ClassName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ClassNameSelected;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainButton;

private:

	FButtonStyle HoverdStyle;
	
	FButtonStyle ActiveStyle;
	
	FButtonStyle NormalStyle;

public:

	FTTUIOnClikedSignature OnClickDelegate;

	//Sets button to Normal State and set the normal look to the button
	void DeselectButton();

	//Setters 
	FORCEINLINE void SetButtonState(EButtonState state);

	//Getters
	FORCEINLINE EButtonState GetButtonState() { return ButtonCurrentState; }
	FORCEINLINE EClassType GetClassType() { return ClassType; }

};
