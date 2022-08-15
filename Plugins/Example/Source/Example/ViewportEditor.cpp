

#include "ViewportEditor.h"


const FName FViewportEditor::EditorName = "ViewportEditor";

//const FName FViewportEditor::ViewportTabId = "Viewport";
//const FName FViewportEditor::DetailsTabId = "Details";
//const FName FViewportEditor::PreviewTabId = "Preview";

TSharedPtr<FViewportEditor> FViewportEditor::Instance = nullptr;

void FViewportEditor::OpenWindow(UObject* InAsset)
{
	//Instance�� static���� ����Ǿ� ���� �޸� �������� �ö��ִ�
	if (Instance.IsValid()) //�̹� â�� �����ִٸ�
	{
		Instance->CloseWindow();	//â�� �ݰ�

		Instance.Reset();			//����� �޸� ����
		Instance = nullptr;			//�ʱ�ȭ
	}

	Instance = MakeShareable(new FViewportEditor());
	Instance->Open(InAsset);
}

void FViewportEditor::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		//Instance.Reset();
		//Instance = nullptr;
	}
}



void FViewportEditor::Open(UObject* InAsset)
{
	//â ���½� ������ ��� ���� �������(���� ������â�� ����� ���̴�)


	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs args
	(
		false,									//
		false,									//��â�� �����(���� �Ұ��ϵ��� ������)
		true,									//�˻���� ����
		FDetailsViewArgs::ObjectsUseNameArea	//Prefix�� ������Ʈ �̸����� ���
	);
	//DetailsView ������ �ʱ�ȭ �Ű����� ����
	DetailsView = prop.CreateDetailView(args);		//������ ������ ���� �ʱ�ȭ, DetailsView�� �Ҵ�
	//DetailsView->SetObject(InAsset);				//�ݵ�� ������Ʈ ����(�������� �����ε� Ÿ�� ������Ʈ ���̴� ������ �� ����)
	DetailsView->SetObject(InAsset);				//�ݵ�� ������Ʈ ����(�������� �����ε� Ÿ�� ������Ʈ ���̴� ������ �� ����)


	//Viewport = SNew(SPreviewObject_Viewport);

	//FAdvancedPreviewSceneModule& scene = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	//Preview = scene.CreateAdvancedPreviewSceneSettingsWidget(Viewport->GetPreviewScene());



	//TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("ViewportEditor_Layout")
	//	->AddArea
	//	(
	//		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
	//		->Split
	//		(
	//			FTabManager::NewStack()
	//			->SetSizeCoefficient(0.1f)
	//			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
	//		)
	//		->Split
	//		(
	//			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
	//			->SetSizeCoefficient(0.75f)
	//			->Split
	//			(
	//				FTabManager::NewStack()
	//				->AddTab(ViewportTabId, ETabState::OpenedTab)
	//			)
	//			->Split
	//			(
	//				FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
	//				->SetSizeCoefficient(0.25f)
	//				->Split
	//				(
	//					FTabManager::NewStack()
	//					->AddTab(DetailsTabId, ETabState::OpenedTab)
	//				)
	//				->Split
	//				(
	//					FTabManager::NewStack()
	//					->AddTab(PreviewTabId, ETabState::OpenedTab)
	//				)
	//			)
	//		)
	//	);

	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("ViewportEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
		);
	FAssetEditorToolkit::InitAssetEditor
	(
		EToolkitMode::Standalone,		//������ ��� (������������ ����)
		TSharedPtr<IToolkitHost>(),		//
		EditorName,						//������ �ĺ���
		layout,							//
		true,							//�޴��� ��������
		true,							//���ٸ� ��������
		InAsset
	);
}

bool FViewportEditor::OnRequestClose()
{
	return true;
}



FName FViewportEditor::GetToolkitFName() const
{
	return EditorName;
}

FText FViewportEditor::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FViewportEditor::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();
}

FLinearColor FViewportEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}
