// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LevelSetupActionPlugin : ModuleRules
{
	public LevelSetupActionPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "Blutility", "Niagara", "ContentBrowser", "InputCore", "Projects",
				"ToolMenus", "AssetTools", "GPULightmass", "Landscape", "LevelEditor"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate", "UMG", "AssetTools",
				"SlateCore", "EditorScriptingUtilities", "UnrealEd",
				"UMGEditor",               // UMG Editor module for handling UMG in editor
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
