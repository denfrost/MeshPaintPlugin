// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "EditorModeExtensionPrivatePCH.h"
#include "EditorModeExtensionEdMode.h"
#include "EditorModeExtensionEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"

const FEditorModeID FEditorModeExtensionEdMode::EM_EditorModeExtensionEdModeId = TEXT("EM_EditorModeExtensionEdMode");

FEditorModeExtensionEdMode::FEditorModeExtensionEdMode()
{

}

FEditorModeExtensionEdMode::~FEditorModeExtensionEdMode()
{

}

void FEditorModeExtensionEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FEditorModeExtensionEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FEditorModeExtensionEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FEditorModeExtensionEdMode::UsesToolkits() const
{
	return true;
}




