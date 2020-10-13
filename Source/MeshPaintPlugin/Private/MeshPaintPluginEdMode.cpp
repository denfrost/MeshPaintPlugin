// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeshPaintPluginEdMode.h"
#include "MeshPaintPluginEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FMeshPaintPluginEdMode::EM_MeshPaintPluginEdModeId = TEXT("EM_MeshPaintPluginEdMode");

FMeshPaintPluginEdMode::FMeshPaintPluginEdMode()
{

}

FMeshPaintPluginEdMode::~FMeshPaintPluginEdMode()
{

}

void FMeshPaintPluginEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FMeshPaintPluginEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FMeshPaintPluginEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FMeshPaintPluginEdMode::UsesToolkits() const
{
	return true;
}




