// Fill out your copyright notice in the Description page of Project Settings.


#include "PrototypeSetupWidget.h"

#include "EditorUtilityWidgetComponents.h"

void UPrototypeSetupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btnCreate->OnClicked.AddDynamic(this, &ThisClass::OnCreateButtonClicked);
}

void UPrototypeSetupWidget::OnCreateButtonClicked()
{
	if(OnCreateAssetButtonClicked.IsBound())
	{
		OnCreateAssetButtonClicked.Execute();
	}
}
