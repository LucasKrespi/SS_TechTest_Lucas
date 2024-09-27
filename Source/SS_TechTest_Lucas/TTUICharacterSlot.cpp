// Fill out your copyright notice in the Description page of Project Settings.


#include "TTUICharacterSlot.h"
#include "Runtime/UMG/Public/UMG.h"
#include "TTUICharacter.h"
#include "Math/Color.h"


bool UTTUICharacterSlot::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!ensure(MainButton != nullptr)) return false;

	MainButton->OnClicked.AddDynamic(this, &UTTUICharacterSlot::OnButtonClicked);

	return false;
}

void UTTUICharacterSlot::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateCard();
}

EClassType UTTUICharacterSlot::GetClassTypeFromString(FString Type)
{
	if (Type == "Assasin")
		return EClassType::ASSASIN;
	else if (Type == "Brawler")
		return EClassType::BRAWLER;
	else if (Type == "Tank")
		return EClassType::TANK;
	else if (Type == "Support")
		return EClassType::SUPPORT;
	return EClassType();
}

void UTTUICharacterSlot::OnButtonClicked()
{
	SetButtonState(EButtonState::ACTIVE);
	UpdateCard();
	OnCharacterClickDelegate.Broadcast(this);
}

void UTTUICharacterSlot::DeselectButton()
{
	SetButtonState(EButtonState::NORMAL);
	UpdateCard();
}

void UTTUICharacterSlot::PopulateSlot(TTUICharacter* Character)
{
	CharacterName->SetText(Character->Name);
	SkillLevel->SetText(FText::FromString(FString::FromInt(Character->SkillLevel)));
	CharacterImage->SetBrushFromTexture(Character->CharacterPortrait);
	ClassIcon->SetBrushFromTexture(Character->ClassIcon);
	isLocked = Character->IsLocked;
	ClassTypeENum = GetClassTypeFromString(Character->ClassType);
	UpdateCard();
}

void UTTUICharacterSlot::UpdateCard()
{
	LockedImageSelected->SetVisibility(ESlateVisibility::Hidden);
	LockedImage->SetVisibility(ESlateVisibility::Hidden);
	UnlockedImageSelected->SetVisibility(ESlateVisibility::Hidden);
	UnlockedImage->SetVisibility(ESlateVisibility::Hidden);
	NormalBackGround->SetVisibility(ESlateVisibility::Hidden);
	SelectedBackGround->SetVisibility(ESlateVisibility::Hidden);

	if (!isLocked)
	{
		this->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		if (ButtonCurrentState == EButtonState::ACTIVE)
		{
			UnlockedImageSelected->SetVisibility(ESlateVisibility::Visible);
			SelectedBackGround->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UnlockedImage->SetVisibility(ESlateVisibility::Visible);
			NormalBackGround->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		this->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.6f));
		if (ButtonCurrentState == EButtonState::ACTIVE)
		{
			LockedImageSelected->SetVisibility(ESlateVisibility::Visible);
			SelectedBackGround->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			LockedImage->SetVisibility(ESlateVisibility::Visible);
			NormalBackGround->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UTTUICharacterSlot::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UTTUICharacterSlot::ShowWidget()
{
	this->SetVisibility(ESlateVisibility::Visible);
}
