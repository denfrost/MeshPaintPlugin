// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeshPaintPluginEdModeToolkit.h"
#include "MeshPaintPluginEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"

//*
#include "EditorStyleSet.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Slate/Public/Widgets/Layout/SSeparator.h"

#define LOCTEXT_NAMESPACE "FMeshPaintPluginEdModeToolkit"

FMeshPaintPluginEdModeToolkit::FMeshPaintPluginEdModeToolkit()
{
	UE_LOG(LogTemp, Log, TEXT("===================Open Export OverrideVertexColor Toolkit==================="));
	StoredColors.Empty();
	PtrOutInt = MakeShareable(new uint32(911));
}

void FMeshPaintPluginEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{

	UE_LOG(LogTemp, Log, TEXT("Init Block!"));

	//OVCTextChangedEvent.AddRaw(this, &FMeshPaintPluginEdModeToolkit::Test); 	// Assign on Event

	ChildSlot[
		SAssignNew(ToolkitWidget, SBorder)
			.IsEnabled(&FMeshPaintPluginEdModeToolkit::IsWidgetEnabled)
			[

				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.Padding(0.0f, 1.0f)
			.FillWidth(1)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("VertexColorPaint_PaintDataLabel", "VertexColor Exporter ver 0.3a by denbaster@gmail.com (c) 06.9.2017"))
			] /*
			+ SHorizontalBox::Slot()
				.Padding(0.0f, 1.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("VertexColorPaint_PaintDataLabel", " 06.09.2017"))
				]*/
			]
		+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSeparator)
				.Orientation(Orient_Horizontal)
			]
		+ SVerticalBox::Slot()
			.AutoHeight()
			[

				// Path
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			.VAlign(VAlign_Fill)
			.FillWidth(1.0f)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.FillWidth(1.0f)
			[
				SAssignNew(OVCTextBox, SEditableTextBox)
				.MinDesiredWidth(128.0f)
			.RevertTextOnEscape(true)
			]

		+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(2.0f, 0.0f, 0.0f, 0.0f)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.OnClicked(this, &FMeshPaintPluginEdModeToolkit::FindOVCButtonClicked)
			[
				SNew(SImage).Image(FEditorStyle::GetBrush("ContentBrowser.PathPickerButton"))
			]
			]
			]
			]
		/*
		+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoHeight()
			[
				//Locals::MakeButton(LOCTEXT("GetInfoButtonLabel", "Get VertexColor Info"))
				SNew(SButton)
				.Text(LOCTEXT("TestOVCButtonLabel", "Test OverrideVertexColor"))
				.OnClicked(this, &FEditorModeExtensionEdModeToolkit::TestOVCButtonClicked)
			]
		*/
		+SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoHeight()
			[
				SNew(SButton)
				.Text(LOCTEXT("ExportOVCButtonLabel", "Export OverrideVertexColor to File"))
			.OnClicked(this, &FMeshPaintPluginEdModeToolkit::OnButtonClickExportOVC, PtrOutInt)
			]
		+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoHeight()
			[
				SNew(SButton)
				.Text(LOCTEXT("ImportOVCButtonLabel", "Import OverrideVertexColor from File"))
			.OnClicked(this, &FMeshPaintPluginEdModeToolkit::OnButtonClickImportOVC, PtrOutInt)
			]
			]
	];
	FModeToolkit::Init(InitToolkitHost);
}

FName FMeshPaintPluginEdModeToolkit::GetToolkitFName() const
{
	return FName("MeshPaintPluginEdMode");
}

FText FMeshPaintPluginEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("MeshPaintPluginEdModeToolkit", "DisplayName", "MeshPaintPluginEdMode Tool");
}

class FEdMode* FMeshPaintPluginEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FMeshPaintPluginEdMode::EM_MeshPaintPluginEdModeId);
}

//SaveLoad Start
/** SaveLoad Section*/
bool FMeshPaintPluginEdModeToolkit::SaveDataToFile(const FString& FullFilePath, FBufferArchive& ToBinary)
{
	if (ToBinary.Num() <= 0) return false;
	//~
	//Step 2: Binary to Hard Disk
	if (FFileHelper::SaveArrayToFile(ToBinary, *FullFilePath))
	{
		// Free Binary Array 	
		ToBinary.FlushCache();
		ToBinary.Empty();

		UE_LOG(LogTemp, Log, TEXT("Save Success! %s"), *FullFilePath);
		return true;
	}

	// Free Binary Array 	
	ToBinary.FlushCache();
	ToBinary.Empty();

	UE_LOG(LogTemp, Log, TEXT("File Could Not Be Saved!"));
	return false;
}

TArray<uint8> FMeshPaintPluginEdModeToolkit::LoadDataFromFile(const FString& FullFilePath)
{
	TArray<uint8> BinaryArchive;
	if (!FFileHelper::LoadFileToArray(BinaryArchive, *FullFilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("FFILEHELPER: >> Invalid File"));
		return BinaryArchive;
	}
	UE_LOG(LogTemp, Log, TEXT("Succes Load File %s"), *FullFilePath);
	return BinaryArchive;
}

//Button for widgets
FReply FMeshPaintPluginEdModeToolkit::TestOVCButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Dynamic Call"));
	//OVCTextBox->SetText(FText::FromString("Dermo"));
	return FReply::Handled();
}

// Dialogs Menu
FReply FMeshPaintPluginEdModeToolkit::FindOVCButtonClicked()
{
	TArray<FString> OpenFilenames;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	bool bOpened = false;
	if (DesktopPlatform != NULL)
	{
		const FString DefaultPath = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_OPEN);
		//TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().AddWindow(Window.ToSharedRef());
		TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().GetVisibleMenuWindow();
		//TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(); //AsShared()
		void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid()) ? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;

		bOpened = DesktopPlatform->OpenFileDialog(
			ParentWindowHandle,
			TEXT("Select OVC file.."),
			TEXT(""),
			TEXT(""),
			TEXT("OVC file (*.ovc)|*.ovc"),
			EFileDialogFlags::None,
			OpenFilenames);
		//*/
		UE_LOG(LogTemp, Log, TEXT("OpenDialog"));
	}

	if (DesktopPlatform == nullptr)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("SaveLogDialogUnsupportedError", "Saving is not supported on this platform!"));

		return FReply::Handled();
	}

	if (bOpened == true)
	{
		if (OpenFilenames.Num() > 0)
		{
			OVCTextBox->SetText(FText::FromString(OpenFilenames[0]));
		}
		else
		{
			bOpened = false;
		}
	}
	return FReply::Handled();
}

void FMeshPaintPluginEdModeToolkit::SaveOVCButtonClicked()
{
	TArray<FString> OpenFilenames;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	bool bOpened = false;
	if (DesktopPlatform != NULL)
	{
		const FString DefaultPath = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_OPEN);
		TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().GetVisibleMenuWindow();
		void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid()) ? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;
		// SelectedActorName for default name of export file
		USelection& SelectedActors = *GEditor->GetSelectedActors();
		FString SelectedActorName = *SelectedActors.GetSelectedObject(0)->GetClass()->GetName();
		bOpened = DesktopPlatform->SaveFileDialog(
			ParentWindowHandle,
			TEXT("Select OVC file.."),
			TEXT(""),
			TEXT("" + SelectedActorName),
			TEXT("OVC file (*.ovc)|*.ovc"),
			EFileDialogFlags::None,
			OpenFilenames);
		//*/
		UE_LOG(LogTemp, Log, TEXT("OpenDialog"));
	}

	if (DesktopPlatform == nullptr)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("SaveLogDialogUnsupportedError", "Saving is not supported on this platform!"));

		return;
	}

	if (bOpened == true)
	{
		if (OpenFilenames.Num() > 0)
		{
			OVCTextBox->SetText(FText::FromString(OpenFilenames[0]));
		}
		else
		{
			bOpened = false;
		}
	}
	return;
}

FReply FMeshPaintPluginEdModeToolkit::OnButtonClickExportOVC(TSharedPtr<uint32> num)
{
	FMessageLog OVCEditorErrors("VertexExport");
	SaveOVCButtonClicked();
	OVCEditorErrors.NewPage(LOCTEXT("OVC_ExportLogLabel", "OVC: Export Vertex Colors"));
	GEditor->BeginTransaction(LOCTEXT("ExportOVCTransactionName", "Export OVC file"));
	FString Path = OVCTextBox->GetText().ToString();
	if (Path.Len() == 0)
	{
		OVCEditorErrors.Warning(LOCTEXT("ExportOVC_ImportErrPathInvalid", "Path  for OVC file invalid."));
		OVCEditorErrors.Notify();
		return FReply::Handled();
	}

	TArray<FColor> colors;
	colors = CopyInstanceVertexColors();
	if (colors.Num() == 0)
	{
		OVCEditorErrors.Warning(LOCTEXT("ExportOVC_ImportErrPathInvalid", "OVC colors invalid."));
		OVCEditorErrors.Notify();
		return FReply::Handled();
	}
	FBufferArchive BinaryArchive;
	BinaryArchive << colors;
	SaveDataToFile(Path, BinaryArchive); //"\\test.ovc"

	OVCTextChangedEvent.Broadcast(); //event fire

	OVCEditorErrors.Info(LOCTEXT("ExportOVC_ImportErrPathInvalid", "Export OVC file succes."));
	OVCEditorErrors.Notify();
	GEditor->EndTransaction();
	return FReply::Handled();
}

FReply FMeshPaintPluginEdModeToolkit::OnButtonClickImportOVC(TSharedPtr<uint32> num)
{
	GEditor->BeginTransaction(LOCTEXT("ImportOVCTransactionName", "Import OVC file"));
	FindOVCButtonClicked();
	FMessageLog OVCEditorErrors("VertexImport");
	OVCEditorErrors.NewPage(LOCTEXT("OVC_ImportLogLabel", "OVC: Import Vertex Colors"));
	FString Path = OVCTextBox->GetText().ToString();
	if (Path.Len() == 0)
	{
		OVCEditorErrors.Warning(LOCTEXT("ExportOVC_ImportErrPathInvalid", "Path for OVC file invalid."));
		OVCEditorErrors.Notify();
		return FReply::Handled();
	}

	TArray<FColor> colors;
	TArray<uint8> BinaryArchive = LoadDataFromFile(Path); //"\\test.ovc"
	FMemoryReader Ar = FMemoryReader(BinaryArchive, true); //true, free data after done
	Ar.Seek(0); //make sure we are at the beginning
	Ar << colors;
	UE_LOG(LogTemp, Log, TEXT("OutFromBin colors: %d"), colors.Num());
	//Import and Paste procces
	if (colors.Num() == 0)
	{
		OVCEditorErrors.Warning(LOCTEXT("ExportOVC_ImportErrPathInvalid", "OVC colors invalid."));
		OVCEditorErrors.Notify();
		return FReply::Handled();
	}
	Path.Split("/", NULL, &Path, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	UE_LOG(LogTemp, Log, TEXT("===================Input File %s"), *Path);
	FillVertexColorsAllLODs(colors, Path);
	OVCEditorErrors.Info(LOCTEXT("ExportOVC_ImportErrPathInvalid", "Import OVC file succes."));
	OVCEditorErrors.Notify();
	GEditor->EndTransaction();
	return FReply::Handled();
}
//SaveLoad Finish

FString FMeshPaintPluginEdModeToolkit::ActorGetUniqueID(AActor* A)
{
	//FString ObjectID = (FString*)(A.GetUniqueID().);
	return FString::FromInt(A->GetUniqueID()); //Avoid problems BP with int64
}

static uint32 GetUniqueID(AActor* A)
{
	return A->GetUniqueID();
}

void FMeshPaintPluginEdModeToolkit::FillVertexColorsAllLODs(TArray<FColor>& InColors, FString FileName)
{
	USelection& SelectedActors = *GEditor->GetSelectedActors();
	if (SelectedActors.Num() != 1)
	{
		// For multy select each selected actor
		for (int32 Actori = 0; Actori < SelectedActors.Num(); ++Actori)
		{
			AActor* LevelActor = Cast<AActor>(SelectedActors.GetSelectedObject(Actori));
			//FillVertexColorsToActor(LevelActor, InColors);
		}
	}
	else
	{
		FileName.Split(".", &FileName, NULL, ESearchCase::IgnoreCase, ESearchDir::FromStart);
		TArray<AActor*> ChildsActors;
		AActor* LevelActor = Cast<AActor>(SelectedActors.GetSelectedObject(0));
		LevelActor->GetAllChildActors(ChildsActors); 		// Check actor selected.. ohave child!s
		UE_LOG(LogTemp, Log, TEXT("===================Try Import count Child Actors! %d"), ChildsActors.Num());
		if (ChildsActors.Num() != 0)
		{
			for (const auto& Child : ChildsActors)
			{
				TArray<UStaticMeshComponent*> SMComponents;

				Child->GetComponents<UStaticMeshComponent>(SMComponents);
				UE_LOG(LogTemp, Log, TEXT("===================Child Actor = %s"), *Child->GetClass()->GetName());
				UE_LOG(LogTemp, Log, TEXT("===================Filename = %s"), *FileName);
				UE_LOG(LogTemp, Log, TEXT("===================Child SMcomponents = %d"), SMComponents.Num());
				UE_LOG(LogTemp, Log, TEXT("===================File count VColors  = %d"), InColors.Num());
				FString Id = FString::FromInt(Child->GetUniqueID());
				Id = ActorGetUniqueID(Child);
				UE_LOG(LogTemp, Log, TEXT("===================Child UniqueID UObject = %s"), *Id);
				if (*Child->GetClass()->GetName() == FileName)
				{
					UE_LOG(LogTemp, Log, TEXT("===================Match!"));
					//FillVertexColorsToActor(Child, InColors);
					//Child->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
				}
			}
		}
		else
		{
			// only with 1 actor selected..!
			//FillVertexColorsToActor(LevelActor, InColors);
		}
	}
}

/** OVC Copies vertex colors associated with the currently selected Mesh/Actor */
TArray<FColor> FMeshPaintPluginEdModeToolkit::CopyInstanceVertexColors()
{
	UE_LOG(LogTemp, Log, TEXT("===================CopyInstanceVertexColors"));
	TArray<FColor> Colors;
	USelection& SelectedActors = *GEditor->GetSelectedActors();
	if (SelectedActors.Num() != 1)
	{
		UE_LOG(LogTemp, Log, TEXT("===================SelectedActors count = %d"), SelectedActors.Num());
		// warning - works only with 1 actor selected..!
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("=$=================SelectedActors count = %d"), SelectedActors.Num());
		UE_LOG(LogTemp, Log, TEXT("=0=================VertexActorEditorMode Begins"));
		UE_LOG(LogTemp, Log, TEXT("=1=================Get VertexColor Info"));
		// For each selected actor
		AActor* LevelActor = Cast<AActor>(SelectedActors.GetSelectedObject(0));
		TArray<UStaticMeshComponent*> StaticMeshComponents;
		LevelActor->GetComponents<UStaticMeshComponent>(StaticMeshComponents, true);
		//UStaticMeshComponent* StaticMeshComponent = StaticMeshComponents[0];
		StaticMeshComponents.Sort(); // STable movign actor asset after exported. Guaranty unique sort every time! Same in Expoert\Import
		UE_LOG(LogTemp, Log, TEXT("===================StaticMeshComponents count = %d, Actor = %s"), StaticMeshComponents.Num(), *LevelActor->GetName());
		for (const auto& StaticMeshComponent : StaticMeshComponents)
		{
			UE_LOG(LogTemp, Log, TEXT("===================have %s"), *StaticMeshComponent->GetName());
			if (StaticMeshComponent)
			{
				UE_LOG(LogTemp, Log, TEXT("===================exporting [%s]"), *StaticMeshComponent->GetName());
				//FPerComponentVertexColorData& PerComponentData = CopiedColorsByComponent[CopiedColorsByComponent.Add(FPerComponentVertexColorData(StaticMeshComponent->StaticMesh, StaticMeshComponent->GetBlueprintCreatedComponentIndex()))];
				if (StaticMeshComponent->GetStaticMesh())
				{
					int32 NumLODs = StaticMeshComponent->GetStaticMesh()->GetNumLODs();
					for (int32 CurLODIndex = 0; CurLODIndex < NumLODs; ++CurLODIndex)
					{
						//FPerLODVertexColorData& LodColorData = PerComponentData.PerLODVertexColorData[PerComponentData.PerLODVertexColorData.AddZeroed()];

						UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh();
						FStaticMeshLODResources& LODModel = StaticMeshComponent->GetStaticMesh()->RenderData->LODResources[CurLODIndex];
						FColorVertexBuffer* ColBuffer = &LODModel.VertexBuffers.ColorVertexBuffer;

						FPositionVertexBuffer* PosBuffer = &LODModel.VertexBuffers.PositionVertexBuffer;

						// Is there an override buffer? If so, copy colors from there instead...
						if (StaticMeshComponent->LODData.Num() > CurLODIndex)
						{
							FStaticMeshComponentLODInfo& ComponentLODInfo = StaticMeshComponent->LODData[CurLODIndex];
							if (ComponentLODInfo.OverrideVertexColors)
							{
								ColBuffer = ComponentLODInfo.OverrideVertexColors;
							}
						}

						// Copy the colour buffer
						if (ColBuffer && PosBuffer)
						{
							uint32 NumColVertices = ColBuffer->GetNumVertices();
							uint32 NumPosVertices = PosBuffer->GetNumVertices();

							if (NumColVertices == NumPosVertices)
							{
								// valid color buffer matching the pos verts
								for (uint32 VertexIndex = 0; VertexIndex < NumColVertices; VertexIndex++)
								{
									uint32 DwCol = ColBuffer->VertexColor(VertexIndex).DWColor();
									FColor Fc = ColBuffer->VertexColor(VertexIndex);
									//UE_LOG(LogTemp, Log, TEXT("Vertex %d Col[%d] %s"), VertexIndex, DwCol, *Fc.ToString());
									Colors.Add(Fc);
									//SaveText += *Fc.ToString();
								}
								UE_LOG(LogTemp, Log, TEXT("===================Exported Vertices := %d"), NumColVertices);
								//FFileHelper::SaveStringToFile(SaveText, *SaveDirectory);
								//return Colors;
							}
							else
							{
								UE_LOG(LogTemp, Log, TEXT("mismatched or empty color buffer - just use white"));
								// mismatched or empty color buffer - just use white
								for (uint32 VertexIndex = 0; VertexIndex < NumPosVertices; VertexIndex++)
								{
									Colors.Add(FColor::White);
								}
							}
						}

					}
				}
				else
				{
					const FText Message = FText::Format(LOCTEXT("ExportOVC_ImportErrPathInvalid", "Eport Erorr by invalid Asset! Component {0}\n\n Have empty Static Mesh and must to fix."), FText::FromString(*StaticMeshComponent->GetName()));
					FMessageDialog::Open(EAppMsgType::Ok, Message);
					Colors.Empty();
					return Colors;
				}
			}
			FString Id = ActorGetUniqueID(LevelActor);
			UE_LOG(LogTemp, Log, TEXT("===================Actor UniqueID UObject = %s"), *Id);
			UE_LOG(LogTemp, Log, TEXT("===================Exported All Colors %d, Actor = %s"), Colors.Num(), *LevelActor->GetName());
		}
	}
	return Colors;
}

void FMeshPaintPluginEdModeToolkit::FillVertexColorsToActor(AActor* LevelActor, TArray<FColor>& InColors)
{
	uint32 CurrNumVertices = 0;
	TArray<UStaticMeshComponent*> StaticMeshComponents;

	UE_LOG(LogTemp, Log, TEXT("===================Try Import ActorClass! %s"), *LevelActor->GetClass()->GetName());
	LevelActor->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	StaticMeshComponents.Sort(); // STable movign actor asset after exported. Guaranty unique sort every time!
	UE_LOG(LogTemp, Log, TEXT("===================StaticMeshComponents count = %d"), StaticMeshComponents.Num());
	for (const auto& StaticMeshComponent : StaticMeshComponents)
	{
		if (StaticMeshComponent)
		{
			int32 NumLODs = StaticMeshComponent->GetStaticMesh()->GetNumLODs();
			for (int32 CurLODIndex = 0; CurLODIndex < NumLODs; ++CurLODIndex)
			{
				UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh();

				const int32 NumMeshLODs = StaticMeshComponent->GetStaticMesh()->GetNumLODs();
				UE_LOG(LogTemp, Log, TEXT("===================LODS count = %d"), NumMeshLODs);
				StaticMeshComponent->SetLODDataCount(NumMeshLODs, NumMeshLODs);
				uint32 LODIndex = 0;

				for (FStaticMeshComponentLODInfo& LODInfo : StaticMeshComponent->LODData)
				{
					StaticMeshComponent->RemoveInstanceVertexColorsFromLOD(LODIndex);
					check(LODInfo.OverrideVertexColors == nullptr);

					const FStaticMeshLODResources& LODModel = StaticMeshComponent->GetStaticMesh()->RenderData->LODResources[LODIndex];
					const FPositionVertexBuffer& PositionVertexBuffer = LODModel.VertexBuffers.PositionVertexBuffer;
					const uint32 NumVertices = PositionVertexBuffer.GetNumVertices();
					//stat LOD Info
					UE_LOG(LogTemp, Log, TEXT("===================CurrentNumVertice : = %d"), CurrNumVertices);
					UE_LOG(LogTemp, Log, TEXT("===================LOD Vertices : = %d try import"), NumVertices);


					LODInfo.OverrideVertexColors = new FColorVertexBuffer;
					TArray<FColor> MeshColors;// = MeshColors.AddUninitialized[NumVertices];
					for (int32 i = 0; i != NumVertices; i++)
					{
						MeshColors.Add(InColors[CurrNumVertices]);
						CurrNumVertices++;
					}

					//LODInfo.OverrideVertexColors->InitFromSingleColor(InColor, NumVertices);
					LODInfo.OverrideVertexColors->InitFromColorArray(MeshColors); // fragment big massive
					UE_LOG(LogTemp, Log, TEXT("===================UpdateVertexColors for Component : = %s"), *StaticMeshComponent->GetName());
					BeginInitResource(LODInfo.OverrideVertexColors); //  thread Render be warning

					StaticMeshComponent->CachePaintedDataIfNecessary();
					StaticMeshComponent->MarkRenderStateDirty();
					//CurrNumVertices += NumVertices-1; //save position in buffer
					LODIndex++;
				}
				//StaticMeshComponent->bDisallowMeshPaintPerInstance = true; // restict MeshPaint

				//StaticMeshComponent->bDisallowMeshPaintPerInstance = true; // restict MeshPaint
			}
		}
	}

}
#undef LOCTEXT_NAMESPACE
