// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Editor/UnrealEd/Public/Toolkits/BaseToolkit.h"
#include "Color.h"
#include "Components/StaticMeshComponent.h"

class FEditorModeExtensionEdModeToolkit : public FModeToolkit
{
public:
	/*Constructor*/
	FEditorModeExtensionEdModeToolkit();

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }

	virtual void Init(const TSharedPtr< class IToolkitHost >& InitToolkitHost);
	/*Vertex operations*/
	static void FillVertexColorsAllLODs(TArray<FColor>& InColors,FString FileName);
	static TArray<FColor> CopyInstanceVertexColors();
	static void FillVertexColorsToActor(AActor* LevelActor, TArray<FColor>& InColors);

	TSharedPtr<uint32> PtrOutInt;

	//SaveLoadData
	static bool SaveDataToFile(const FString& FullFilePath, FBufferArchive& ToBinary);
	static TArray<uint8> LoadDataFromFile(const FString& FullFilePath);

	static FString ActorGetUniqueID(AActor * A);
	static uint32 GetUniqueID(AActor * A);

	//Event driven
	void Test();
	//DECLARE_MULTICAST_DELEGATE(FOVCTextChangedEvent)

	DECLARE_EVENT(FEditorModeExtensionEdModeToolkit, FOVCTextChangedEvent);
	FOVCTextChangedEvent& OnOVCTextChangedEvent()
	{
		return OVCTextChangedEvent;
	}

private:
	FOVCTextChangedEvent OVCTextChangedEvent;
	bool IsWidgetEnabled;
	TArray<FColor> StoredColors;
	TSharedPtr<SWidget> ToolkitWidget;
	TSharedPtr<SEditableTextBox> OVCTextBox;

	FReply FindOVCButtonClicked();
	void SaveOVCButtonClicked();
	FReply OnButtonClickExportOVC(TSharedPtr<uint32> num);
	FReply OnButtonClickImportOVC(TSharedPtr<uint32> num);
	FReply TestOVCButtonClicked();
protected:
	FSimpleSlot ChildSlot;
};


