// Fill out your copyright notice in the Description page of Project Settings.


#include "TTUIToggle.h"
#include "Runtime/UMG/Public/UMG.h"

bool UTTUIToggle::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;
	if (!ensure(CheckBox != nullptr)) return false;

	CheckBox->OnCheckStateChanged.AddDynamic(this, &UTTUIToggle::OnCheckChange);


	return false;
}

void UTTUIToggle::OnCheckChange(bool checked)
{
	OnCheckStateChangeDelegate.Broadcast(checked);
}
