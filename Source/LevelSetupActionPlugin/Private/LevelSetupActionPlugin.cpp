// Copyright Epic Games, Inc. All Rights Reserved.

#include "LevelSetupActionPlugin.h"
#include "ContentBrowserModule.h"
#include "EditorUtilityLibrary.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "LevelEditorSubsystem.h"
#include "PrototypeSetupWidget.h"
#include "Factories/BlueprintFactory.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet2/BlueprintEditorUtils.h"


#define LOCTEXT_NAMESPACE "FLevelSetupActionPluginModule"

class ULevelEditorSubsystem;
class UEditorAssetLibrary;

void FLevelSetupActionPluginModule::StartupModule()
{
	FContentBrowserModule& module = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	TArray<FContentBrowserMenuExtender_SelectedPaths>& extender = module.GetAllPathViewContextMenuExtenders();
	extender.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this,
		&FLevelSetupActionPluginModule::CreateListUI));
}

void FLevelSetupActionPluginModule::ShutdownModule()
{

}

TSharedRef<FExtender> FLevelSetupActionPluginModule::CreateListUI(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> extender(new FExtender());

	if(SelectedPaths.Num() > 0)
	{
		extender->AddMenuExtension(FName("ValidateAssetsPath"),
									EExtensionHook::After,
									nullptr,
									FMenuExtensionDelegate::CreateRaw(this, &FLevelSetupActionPluginModule::CreateCustomOptionList));
	}
	
	return extender;
}

void FLevelSetupActionPluginModule::CreateCustomOptionList(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("SetupPrototype")),
		FText::FromString(TEXT("Creates the files for isolation system creation")),
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &FLevelSetupActionPluginModule::SpawnWidget));
}

void FLevelSetupActionPluginModule::SpawnWidget()
{
	if(UEditorUtilitySubsystem* subsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>())
	{
		
		const FString path = "/LevelSetupActionPlugin/BP_LevelDialogWidget.BP_LevelDialogWidget";

		if(UEditorUtilityWidgetBlueprint* editorBPWidget = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr, *path))
		{
			if (UEditorUtilityWidget* edWidget = subsystem->SpawnAndRegisterTab(editorBPWidget))
			{
				mWidgetRef = Cast<UPrototypeSetupWidget>(edWidget);
				if(mWidgetRef)
				{
					mWidgetRef->OnCreateAssetButtonClicked.BindRaw(this, &FLevelSetupActionPluginModule::CreateAssets);
				}
			}
		}
	}
}



void FLevelSetupActionPluginModule::CreateAssets()
{
	FString path;
	UEditorUtilityLibrary::GetCurrentContentBrowserPath(path);

	if(!path.IsEmpty())
	{
		FString debugStr = FString::Printf(TEXT("Spawn Prototype at: %s \t Widget Ref: %s"), *path, *mWidgetRef->DevName);
		FAssetToolsModule& assetModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
		auto LevelPath = mWidgetRef->BaseTemplateLevel.ToSoftObjectPath().GetLongPackageName();

		if(!LevelPath.IsEmpty())
		{
			// Get the assets
			const FString devNameStr = (mWidgetRef->DevName == "")? "defaultUser" : mWidgetRef->DevName;
			const FString focusStr = mWidgetRef->Focus;
			// Create the names
			const FString levelName = FString::Printf(TEXT("%sLevel_%s"), *devNameStr, *focusStr);
			const FString controllerName = FString::Printf(TEXT("BP_%sController_%s"), *devNameStr, *focusStr);
			const FString charName = FString::Printf(TEXT("BP_%sChar_%s"), *devNameStr, *focusStr);
			const FString gameModeName = FString::Printf(TEXT("BP_%sGameMode_%s"), *devNameStr, *focusStr);

			// Create the path
			const FString FolderName = FString::Printf(TEXT("%s_%s"), *devNameStr, *focusStr);
			const FString dir = FPaths::Combine(path, FolderName);
			
			if(!FPaths::DirectoryExists(dir))
			{
				IFileManager::Get().MakeDirectory(*dir);
			}

			// Create the Level
			if(UWorld* world = CreateLevel(LevelPath, dir, levelName, assetModule))
			{
				// Create the Controller
				SetupController(dir, controllerName, assetModule);

				// Create the Character
				SetupCharacter(dir, charName, assetModule);

				// Create the Game Mode
				AGameModeBase* gameMode = SetupGameMode(dir, gameModeName, assetModule);

				if(AWorldSettings* settings = world->GetWorldSettings())
				{
					settings->DefaultGameMode = gameMode->GetClass();
				}
			}
		}
	}
}

UWorld* FLevelSetupActionPluginModule::CreateLevel(const FString& SourcePath, const FString& OutputPath, const FString& FileName,
													const FAssetToolsModule& AssetModule)
{
	UObject* originalAsset = LoadObject<UObject>(nullptr, *SourcePath);
	UObject* newObj = AssetModule.Get().DuplicateAsset(FileName, OutputPath, originalAsset);
	if(newObj)
	{
		UWorld* world = Cast<UWorld>(newObj);
		if (world) return world;
	}
	
	return nullptr;
}

bool FLevelSetupActionPluginModule::SetupController(const FString& OutputPath,
													const FString& FileName, const FAssetToolsModule& AssetModule)
{
	UBlueprintFactory* bpFactory = NewObject<UBlueprintFactory>();
	bpFactory->ParentClass = mWidgetRef->BaseController;
	UObject* obj = AssetModule.Get().CreateAsset(FileName, OutputPath, UBlueprint::StaticClass(), bpFactory);

	/*
	// Try to cast the object to Blueprint
	if(mWidgetRef->bControllerShouldImplementInterface)
	{
		UBlueprint* bp = Cast<UBlueprint>(obj);
		if(bp)
		{
			const auto interfaceClasses = mWidgetRef->ControllerInterfacesToAdd;

			if(!interfaceClasses.IsEmpty())
			{
				for (auto ic : interfaceClasses)
				{
					FTopLevelAssetPath LevelAssetPath = ic->GetClassPathName();
					FBlueprintEditorUtils::ImplementNewInterface(bp, LevelAssetPath);
				}
			}
		}
	}
*/
	
	// This implements the interfaces from the user if the condition is true
	if(mWidgetRef->bControllerShouldImplementInterface)
	{
		AddInterfaces(*obj, mWidgetRef->ControllerInterfacesToAdd);
	}

	
	return obj != nullptr;
}

bool FLevelSetupActionPluginModule::SetupCharacter(const FString& OutputPath,
													const FString& FileName, const FAssetToolsModule& AssetModule)
{
	UBlueprintFactory* bpFactory = NewObject<UBlueprintFactory>();
	bpFactory->ParentClass = mWidgetRef->BaseCharacter;
	UObject* obj = AssetModule.Get().CreateAsset(FileName, OutputPath, UBlueprint::StaticClass(), bpFactory);

	// This implements the interfaces from the user if the condition is true
	if(mWidgetRef->bCharacterShouldImplementInterface)
	{
		AddInterfaces(*obj, mWidgetRef->CharacterInterfacesToAdd);
	}
	return obj != nullptr;
}

class AGameModeBase* FLevelSetupActionPluginModule::SetupGameMode(const FString& OutputPath,
													const FString& FileName, const FAssetToolsModule& AssetModule)
{
	UBlueprintFactory* gmFactory = NewObject<UBlueprintFactory>();

	// TODO: Need to change to the one user provides
	gmFactory->ParentClass = mWidgetRef->BaseGameMode;

	// TODO: the Asset name will be given by the user
	UObject* obj = AssetModule.Get().CreateAsset(FileName,
		OutputPath, UBlueprint::StaticClass(), gmFactory);

	// This implements the interfaces from the user if the condition is true
	if(mWidgetRef->bGameModeShouldImplementInterface)
	{
		AddInterfaces(*obj, mWidgetRef->GameModeInterfacesToAdd);
	}

	// This code below is to change the elements inside the blueprint
	// --- First it checks if the object can be casted to a blueprint
	if(UBlueprint* bp = Cast<UBlueprint>(obj))
	{
		// --- Then it gets the parent class of the blueprint
		UClass* gmClass = bp->GeneratedClass;

		// --- Then it checks if the class is a child of Game Mode
		if(gmClass && gmClass->IsChildOf(AGameModeBase::StaticClass()))
		{
			// --- Then it casts the Object reference to Game Mode 
			AGameModeBase* gm = Cast<AGameModeBase>(gmClass->GetDefaultObject());
			if(gm)
			{
				// --- Finally, if all the checks passes, it will change the things in that class
				//TODO: Need to add more to this
				gm->PlayerControllerClass = mWidgetRef->BaseController;
				gm->DefaultPawnClass = mWidgetRef->BaseCharacter;
				return gm;
			}
		}
	}

	return nullptr;
}

void FLevelSetupActionPluginModule::AddInterfaces(UObject& ObjectRef, TArray<TSubclassOf<UInterface>> ClassesRef)
{
	// Try to cast the object to Blueprint
	if(UBlueprint* bp = Cast<UBlueprint>(&ObjectRef))
	{
		if(!ClassesRef.IsEmpty())
		{
			for (auto c : ClassesRef)
			{
				FTopLevelAssetPath LevelAssetPath = c->GetClassPathName();
				FBlueprintEditorUtils::ImplementNewInterface(bp, LevelAssetPath);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLevelSetupActionPluginModule, LevelSetupActionPlugin)