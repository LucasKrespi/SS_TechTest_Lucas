// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTUIToggle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTTUIOnCheckedSignature, bool, isToggle);
/**
 * 
 */
UCLASS()
class SS_TECHTEST_LUCAS_API UTTUIToggle : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	bool Initialize() override;

	UFUNCTION()
	void OnCheckChange(bool checked);

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* CheckBox;

public:

	FTTUIOnCheckedSignature OnCheckStateChangeDelegate;
};
