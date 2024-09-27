// Fill out your copyright notice in the Description page of Project Settings.


#include "TTUIMainHUD.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "TTUICharacter.h"
#include "TTUICharacterSlot.h"
#include "TTUIToggle.h"

void UTTUIMainHUD::NativeConstruct()
{
	Super::NativeConstruct();
	PopulateButtonArray();
	CreateCharacters();
}

void UTTUIMainHUD::SynchronizeProperties()
{
	//This Existes to visualize the layout in the editor will be overriten on NativeConstruct
	Super::SynchronizeProperties();

	//Null check necessary avoid editor errors 
	if (Grid && ItemWidgetClass)
	{
		Grid->ClearChildren();

		for (int32 y = 0; y < Rows; ++y)
		{
			for (int32 x = 0; x < Columns; ++x)
			{
				UTTUICharacterSlot* Widget = CreateWidget<UTTUICharacterSlot>(GetWorld(), ItemWidgetClass);
				int32 index = (y * Rows) + x;

				if (Widget)
				{
					UUniformGridSlot* GridSlot = Grid->AddChildToUniformGrid(Widget);
					GridSlot->SetRow(y);
					GridSlot->SetColumn(x);
				}
			}
		}
		
	}
}

void UTTUIMainHUD::PopulateButtonArray()
{
	ClassSelectionButtons = { SelectClassButtonOne , SelectClassButtonTwo,
							SelectClassButtonTree, SelectClassButtonFour,
							SelectClassButtonFive };

	for (UTTUIButton* Button : ClassSelectionButtons)
	{
		Button->OnClickDelegate.AddUniqueDynamic(this, &ThisClass::OnClassButtonClicked);
	}

	ShowLockedToggle->OnCheckStateChangeDelegate.AddUniqueDynamic(this, &ThisClass::OnShowLockedToggleChange);
	
	//Aelect the first button
	OnClassButtonClicked(SelectClassButtonOne);
	SelectClassButtonOne->SetButtonState(EButtonState::ACTIVE);
}

void UTTUIMainHUD::OnClassButtonClicked(UTTUIButton* ClikedButton)
{
	for (UTTUIButton* Button : ClassSelectionButtons)
	{
		if (Button != ClikedButton)
			Button->DeselectButton();
	}

	CurrentSelectedButton = ClikedButton;
	FilterIsLocked(IsShowLocked);
}

void UTTUIMainHUD::OnCharacterSlotClicked(UTTUICharacterSlot* ClikedSlot)
{
	for (UTTUICharacterSlot* CharacterSlot : CharactersSlots)
	{
		if (CharacterSlot != ClikedSlot)
			CharacterSlot->DeselectButton();
	}

	CurrentSelectedSlot = ClikedSlot;
}

void UTTUIMainHUD::OnShowLockedToggleChange(bool IsChecked)
{
	IsShowLocked = IsChecked;
	FilterIsLocked(IsShowLocked);
}

void UTTUIMainHUD::CreateCharacters()
{
	if (Grid && ItemWidgetClass)
	{
		Grid->ClearChildren();

		const FString CharacterDataPath{ TEXT("/Script/Engine.DataTable'/Game/DataTables/DT_CharacterData.DT_CharacterData'") };

		UDataTable* CharacterTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *CharacterDataPath));

		if (CharacterTableObject)
		{
			TArray<FCharacterDataTable*> rows;
			CharacterTableObject->GetAllRows("", rows);

			Rows = (rows.Num() / Columns) + 1;
			
			for (int32 y = 0; y < Rows; ++y)
			{
				for (int32 x = 0; x < Columns; ++x)
				{
					UTTUICharacterSlot* Widget = CreateWidget<UTTUICharacterSlot>(GetWorld(), ItemWidgetClass);
					int32 index = (y * Columns) + x;

					if(index >= rows.Num()) return;

					Widget->PopulateSlot(new TTUICharacter(rows[index]));
					Widget->OnCharacterClickDelegate.AddUniqueDynamic(this, &ThisClass::OnCharacterSlotClicked);

					CharactersSlots.Add(Widget);

					if(Widget)
					{
						UUniformGridSlot* GridSlot = Grid->AddChildToUniformGrid(Widget);
						GridSlot->SetRow(y);
						GridSlot->SetColumn(x);
						Slots.Add(GridSlot);
					}
				}
			}
		}
	}
}

void UTTUIMainHUD::FilterIsLocked(bool ShowLocked)
{
	int32 row = 0;
	int32 column = 0;

	if (ShowLocked)
	{
		for (int32 i = 0; i < Slots.Num(); i++)
		{
			Slots[i]->SetRow(row);
			Slots[i]->SetColumn(column);
			

			switch (CurrentSelectedButton->GetClassType())
			{
			case EClassType::ALL:
					CharactersSlots[i]->ShowWidget();
					if (column >= Columns - 1)
					{
						column = 0;
						row++;
					}
					else
					{
						column++;
					}
				break;
			case EClassType::ASSASIN:
			case EClassType::BRAWLER:
			case EClassType::TANK:
			case EClassType::SUPPORT:
					if (CurrentSelectedButton->GetClassType() != CharactersSlots[i]->GetClassType())
					{
						CharactersSlots[i]->HideWidget();
						Slots[i]->SetColumn((i % Columns));

					}
					else
					{
						CharactersSlots[i]->ShowWidget();
						if (column >= Columns - 1)
						{
							column = 0;
							row++;
						}
						else
						{
							column++;
						}
					}
				break;
			default:
				break;
			}
		}
	}
	else
	{
		for (int32 i = 0; i < Slots.Num(); i++)
		{

			if (CharactersSlots[i]->GetIsLocked())
			{
				CharactersSlots[i]->HideWidget();

				//Set the invisible slots to at least one full row to conserv layout
				Slots[i]->SetColumn((i % Columns));
			}
			else
			{
				Slots[i]->SetRow(row);
				Slots[i]->SetColumn(column);

				switch (CurrentSelectedButton->GetClassType())
				{
				case EClassType::ALL:
					CharactersSlots[i]->ShowWidget();
					if (column >= Columns - 1)
					{
						column = 0;
						row++;
					}
					else
					{
						column++;
					}
					break;
				case EClassType::ASSASIN:
				case EClassType::BRAWLER:
				case EClassType::TANK:
				case EClassType::SUPPORT:
					if (CurrentSelectedButton->GetClassType() != CharactersSlots[i]->GetClassType())
					{
						CharactersSlots[i]->HideWidget();
						Slots[i]->SetColumn((i % Columns));
					}
					else
					{
						CharactersSlots[i]->ShowWidget();
						if (column >= Columns - 1)
						{
							column = 0;
							row++;
						}
						else
						{
							column++;
						}
					}
					break;
				default:
					break;
				}
			}

		}
	}
}
