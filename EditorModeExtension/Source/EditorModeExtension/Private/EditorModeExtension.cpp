// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "EditorModeExtensionPrivatePCH.h"
#include "EditorModeExtensionEdMode.h"

#define LOCTEXT_NAMESPACE "FEditorModeExtensionModule"

void FEditorModeExtensionModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FEditorModeExtensionEdMode>(FEditorModeExtensionEdMode::EM_EditorModeExtensionEdModeId, LOCTEXT("EditorModeExtensionEdModeName", "EditorModeExtensionEdMode"), FSlateIcon(), true);
}

void FEditorModeExtensionModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FEditorModeExtensionEdMode::EM_EditorModeExtensionEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorModeExtensionModule, EditorModeExtension)