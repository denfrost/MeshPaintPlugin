// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeshPaintPlugin.h"
#include "MeshPaintPluginEdMode.h"

#define LOCTEXT_NAMESPACE "FMeshPaintPluginModule"

void FMeshPaintPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FMeshPaintPluginEdMode>(FMeshPaintPluginEdMode::EM_MeshPaintPluginEdModeId, LOCTEXT("MeshPaintPluginEdModeName", "MeshPaintPluginEdMode"), FSlateIcon(), true);
}

void FMeshPaintPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FMeshPaintPluginEdMode::EM_MeshPaintPluginEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMeshPaintPluginModule, MeshPaintPlugin)