// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"

class FLevelSetupActionPluginModule : public IModuleInterface
{
private:

	class UPrototypeSetupWidget* mWidgetRef = nullptr;

	void AddInterfaces(UObject& ObjectRef, TArray<TSubclassOf<UInterface>> ClassesRef);
	
public:

	const FName ExtName = "CustomExt";
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TSharedRef<FExtender> CreateListUI(const TArray<FString>& SelectedPaths);

	void SpawnWidget();
	
	void CreateAssets();
	void CreateCustomOptionList(FMenuBuilder& MenuBuilder);

	UWorld* CreateLevel(const FString& SourcePath, const FString& OutputPath, const FString& FileName, const FAssetToolsModule& AssetModule);

	bool SetupController(const FString& OutputPath, const FString& FileName, const FAssetToolsModule& AssetModule);
	
	bool SetupCharacter(const FString& OutputPath,
						const FString& FileName, const FAssetToolsModule& AssetModule);

	class AGameModeBase* SetupGameMode(const FString& OutputPath,
					const FString& FileName, const FAssetToolsModule& AssetModule);
	

};
