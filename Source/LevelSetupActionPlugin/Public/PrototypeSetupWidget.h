// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "PrototypeSetupWidget.generated.h"


DECLARE_DELEGATE(FOnCreateButtonClickedSignature);

UCLASS()
class LEVELSETUPACTIONPLUGIN_API UPrototypeSetupWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GameMode")
	TSubclassOf<class AGameModeBase> BaseGameMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GameMode")
	bool bGameModeShouldImplementInterface;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="GameMode", meta=(EditCondition="bGameModeShouldImplementInterface", EditConditionHides))
	TArray<TSubclassOf<UInterface>> GameModeInterfacesToAdd;
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Controller")
	TSubclassOf<class APlayerController> BaseController;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Controller")
	bool bControllerShouldImplementInterface;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Controller", meta=(EditCondition="bControllerShouldImplementInterface", EditConditionHides))
	TArray<TSubclassOf<UInterface>> ControllerInterfacesToAdd;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character")
	TSubclassOf<class ACharacter> BaseCharacter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character")
	bool bCharacterShouldImplementInterface;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character", meta=(EditCondition="bControllerShouldImplementInterface", EditConditionHides))
	TArray<TSubclassOf<UInterface>> CharacterInterfacesToAdd;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Base")
	TSoftObjectPtr<UWorld> BaseTemplateLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Privates")
	FString DevName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Privates")
	FString Focus;
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UEditorUtilityButton* btnCreate;

	UFUNCTION()
	void OnCreateButtonClicked();

	
	FOnCreateButtonClickedSignature OnCreateAssetButtonClicked;
};
