// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"

#include "DesktopPlatformModule.h"
#include "Runtime/Core/Public/Serialization/BufferArchive.h"

//#include "EditorStyleSet.h"
//#include "StaticMeshResources.h"
//#include "Components/StaticMeshComponent.h"
//#include "Components/MeshComponent.h"

#include "EditorDirectories.h"
#include "Widgets/SCompoundWidget.h"

class MESHPAINTPLUGIN_API FMeshPaintPluginEdModeToolkit : public FModeToolkit
{
public:

	FMeshPaintPluginEdModeToolkit();
	
	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }

	/**Vertex operations**/
	static void FillVertexColorsAllLODs(TArray<FColor>& InColors, FString FileName);
	static void FillVertexColorsToActor(AActor* LevelActor, TArray<FColor>& InColors);
	static TArray<FColor> CopyInstanceVertexColors();
	/*Returns the unique ID of the object for Actor...these are reused so it is only unique while the object is alive. Useful as a tag.*/
	static FString ActorGetUniqueID(AActor * A);
	static uint32 GetUniqueID(AActor * A);
	/*Is a non-intrusive reference-counted authoritative object pointer.*/
	TSharedPtr<uint32> PtrOutInt;

	/**SaveLoadData**/
	static bool SaveDataToFile(const FString& FullFilePath, FBufferArchive& ToBinary);
	static TArray<uint8> LoadDataFromFile(const FString& FullFilePath);
	/**Event**/
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

	FSimpleSlot ChildSlot = nullptr;
};
