// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EditorModeExtension : ModuleRules
{
	public EditorModeExtension(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicIncludePaths.AddRange(
			new string[] {
				"EditorModeExtension/Public",
                "Developer/DesktopPlatform/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"EditorModeExtension/Private",
                //"Developer/DesktopPlatform/Private"
				// ... add other private include paths required here ...
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);

        PrivateIncludePathModuleNames.AddRange(
                new string[] {
					//"SlateFileDialogs",
				}
            );

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
                "RenderCore", // Graphic Vertex Buffer Opeartion
                "EditorStyle" // SlateBrush editor elements
                //"ShaderCore" // EditorMode namespace Graphic Buffer Opeartion

				// ... add private dependencies that you statically link with here ...	
			}
			);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
                //"SlateFileDialogs"
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
