// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTUIButton.h"
/**
 * 
 */

class SS_TECHTEST_LUCAS_API TTUICharacter
{
public:
	TTUICharacter(struct FCharacterDataTable* DataRow);
	~TTUICharacter();
public:
	
	FText Name;
	UTexture2D* ClassIcon;
	FString ClassType;
	bool IsLocked;
	UTexture2D* CharacterPortrait;
	int32 SkillLevel;
};
