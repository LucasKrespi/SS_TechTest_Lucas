// Fill out your copyright notice in the Description page of Project Settings.


#include "TTUICharacter.h"
#include "TTUICharacterSlot.h"


TTUICharacter::TTUICharacter(FCharacterDataTable* DataRow)
{
	Name = DataRow->Name;
	ClassIcon = DataRow->ClassIcon;
	IsLocked = DataRow->IsLocked;
	CharacterPortrait = DataRow->CharacterPortrait;
	SkillLevel = DataRow->SkillLevel;
	ClassType = DataRow->ClassType;
}

TTUICharacter::~TTUICharacter()
{
}


