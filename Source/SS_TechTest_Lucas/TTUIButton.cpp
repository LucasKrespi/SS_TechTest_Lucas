// Fill out your copyright notice in the Description page of Project Settings.


#include "TTUIButton.h"
#include "Runtime/UMG/Public/UMG.h"

bool UTTUIButton::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!ensure(MainButton != nullptr)) return false;

	MainButton->OnHovered.AddDynamic(this, &UTTUIButton::OnButtonHovered);
	MainButton->OnUnhovered.AddDynamic(this, &UTTUIButton::OnButtonHovered);
	MainButton->OnClicked.AddDynamic(this, &UTTUIButton::OnButtonClicked);
	
	return false;
}

void UTTUIButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InitStyles(); 
}

void UTTUIButton::NativeConstruct()
{
	Super::NativeConstruct();
	InitiButton();
}

void UTTUIButton::InitiButton()
{
	const FString ClassDataPath{ TEXT("/Script/Engine.DataTable'/Game/DataTables/DT_ClassesData.DT_ClassesData'") };

	UDataTable* ClassTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ClassDataPath));

	if (ClassTableObject)
	{
		FClassDataTable* ClassDatarow = nullptr;

		switch (ClassType)
		{
		case EClassType::ALL:
			ClassDatarow = ClassTableObject->FindRow<FClassDataTable>(FName("All"), TEXT(""));
			break;
		case EClassType::SUPPORT:
			ClassDatarow = ClassTableObject->FindRow<FClassDataTable>(FName("Support"), TEXT(""));
			break;
		case EClassType::TANK:
			ClassDatarow = ClassTableObject->FindRow<FClassDataTable>(FName("Tank"), TEXT(""));
			break;
		case EClassType::BRAWLER:
			ClassDatarow = ClassTableObject->FindRow<FClassDataTable>(FName("Brawler"), TEXT(""));
			break;
		case EClassType::ASSASIN:
			ClassDatarow = ClassTableObject->FindRow<FClassDataTable>(FName("Assasin"), TEXT(""));
			break;
		default:
			break;
		}

		if (ClassDatarow)
		{
			ClassIconImage->SetBrushFromTexture(ClassDatarow->ClassIcon);
			ClassName->SetText(ClassDatarow->Name);
			ClassNameSelected->SetText(ClassDatarow->Name);
		}
		
		DeselectButton();
	}
}

void UTTUIButton::OnButtonHovered()
{
	if (ButtonCurrentState == EButtonState::ACTIVE) return;

	if (ButtonCurrentState == EButtonState::HOVERED)
		SetButtonState(EButtonState::NORMAL);
	else
		SetButtonState(EButtonState::HOVERED);
}

void UTTUIButton::OnButtonClicked()
{
	SetButtonState(EButtonState::ACTIVE);
	OnClickDelegate.Broadcast(this);
}

void UTTUIButton::InitStyles()
{
	ActiveStyle.Normal = MainButton->WidgetStyle.Pressed;
	ActiveStyle.Hovered = MainButton->WidgetStyle.Pressed;
	ActiveStyle.Pressed = MainButton->WidgetStyle.Pressed;
	
	HoverdStyle.Normal = MainButton->WidgetStyle.Hovered;
	HoverdStyle.Hovered = MainButton->WidgetStyle.Hovered;
	HoverdStyle.Pressed = MainButton->WidgetStyle.Hovered;
	
	NormalStyle.Normal = MainButton->WidgetStyle.Normal;
	NormalStyle.Hovered = MainButton->WidgetStyle.Normal;
	NormalStyle.Pressed = MainButton->WidgetStyle.Normal;
}

void UTTUIButton::UpdateStyle()
{
	switch (ButtonCurrentState)
	{
	case EButtonState::NORMAL:
		MainButton->WidgetStyle = NormalStyle;
		ClassNameSelected->SetVisibility(ESlateVisibility::Hidden);
		ClassName->SetVisibility(ESlateVisibility::Visible);
		break;
	case EButtonState::HOVERED:
		MainButton->WidgetStyle = HoverdStyle;
		ClassNameSelected->SetVisibility(ESlateVisibility::Visible);
		ClassName->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EButtonState::ACTIVE:
		MainButton->WidgetStyle = ActiveStyle;
		ClassNameSelected->SetVisibility(ESlateVisibility::Visible);
		ClassName->SetVisibility(ESlateVisibility::Hidden);
		break;
	default:
		break;
	}
}

void UTTUIButton::DeselectButton()
{
	SetButtonState(EButtonState::NORMAL);
}

void UTTUIButton::SetButtonState(EButtonState state)
{
	ButtonCurrentState = state;
	UpdateStyle();
}

