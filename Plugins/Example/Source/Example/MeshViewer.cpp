
#include "MeshViewer.h"
#include "AdvancedPreviewSceneModule.h"
#include "SMeshObject_Viewport.h"

const FName FMeshViewer::EditorName = "MeshViewer";

const FName FMeshViewer::ViewportTabId = "Viewport";
const FName FMeshViewer::DetailsTabId = "Details";
const FName FMeshViewer::PreviewTabId = "Preview";

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;

void FMeshViewer::OpenWindow(UObject* InAsset)
{
	//Instance�� static���� ����Ǿ� ���� �޸� �������� �ö��ִ�
	if (Instance.IsValid()) //�̹� â�� �����ִٸ�
	{
		Instance->CloseWindow();	//â�� �ݰ�

		Instance.Reset();			//����� �޸� ����
		Instance = nullptr;			//�ʱ�ȭ
	}

	Instance = MakeShareable(new FMeshViewer());	//FViewportEditor �⺻â ����
	Instance->Open(InAsset);
}

void FMeshViewer::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		//������ �÷��Ͱ� �����⶧���� ������ ��ü���� �����ϵ��� ����
		//���� �Ʒ��� Ȱ��ȭ �ϸ� ���α׷��� �������� ������
		//Instance.Reset();
		//Instance = nullptr;
	}
}



void FMeshViewer::Open(UObject* InAsset)
{
	//â ���½� ������ ��� ���� �������(���� ������â�� ����� ���̴�)


	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//������ ��� PropertyEditor ������


	//Spawn_DetailsTab���� ���� DetailsView�� �Ķ���͸� �������� ����ü args ����
	FDetailsViewArgs args
	(
		false,									//�����Ҷ����� ������Ʈ ����
		false,									//��â�� �����(���� �Ұ��ϵ��� ������, ����)
		true,									//�˻���� ����(�׸�ã��)
		FDetailsViewArgs::ObjectsUseNameArea	//Prefix�� ������Ʈ �̸����� ��� �⺻������ ���ͷ� �ϸ� ����â�� ��
	);
	//DetailsView ������ �ʱ�ȭ �Ű����� ����
	DetailsView = prop.CreateDetailView(args);		//������ ������ ���� �ʱ�ȭ, DetailsView�� �Ҵ�
	//���Ŀ� ���⿡ ��� Ŀ���͸���¡ ����
	DetailsView->SetObject(InAsset);				//SetObject������ �ʾƵ� â�� ���
	//InAsset�� ���õ� ���±��� ���� ����ȭ

	//������Ʈ �����Ҵ��� SNew���� ���� ���� �� SEditorViewport�� ��ӹ��� �����̴�
	Viewport = SNew(SMeshObject_Viewport);

	FAdvancedPreviewSceneModule& scene = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");	//AdvancedPreviewScene ������ �̸�(����̸�)
	Preview = scene.CreateAdvancedPreviewSceneSettingsWidget(Viewport->GetPreviewScene());


	//â ������ �������ش� ���״�� ���̾ƿ� ����!
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("ViewportEditor_Layout")
		->AddArea	//���� �߰�
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)	//NewPrimaryArea�������� ������Ұ��� ���� (�ϳ����� ������ �ѷ� ���� 1�� 9�� ������ȹ)
			->Split		//�ѷ� ���������� ������
			(
				FTabManager::NewStack()		//���������� ���� �� ����(����ó�� ���� ������Ʈ�� ����)
				->SetSizeCoefficient(0.1f)	//������ ���� ó�� ���ҵ� 10���� ������ ���
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)	//�� �߰� (���پ��̵�, �������� ������ ���� �������·� ����)
				//���پ��̵�� ������ �⺻���� �������ֱ⶧���� ������ ���� �ȴ�
			)
			->Split	//�ѷ� ���������� �Ʒ�����(90����)
			(
				//�Ʒ��� ����������� NewSplitter�� ���� �ٽ� ����
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)	//�̹� ������ �Ʒ������� �̹����� ���� ����
				->SetSizeCoefficient(0.75f)			//���� ���� ������ 75�� ����
				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)
				->Split
				(
					//���� ������ �ٽ� �� ����
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.25f)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(DetailsTabId, ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabId, ETabState::OpenedTab)
					)
				)
			)
		);


	FAssetEditorToolkit::InitAssetEditor	//���� â�� ���� �۾�
	(
		EToolkitMode::Standalone,		//������ ��� (����â���� ����, ���弾Ʈ���� â�� ���ӵ�, ����/����âó��!)
		TSharedPtr<IToolkitHost>(),		//�θ�â����(�����Ƿ� �� ��ü)
		EditorName,						//������ �ĺ��� ("MeshViewer")
		layout,							//������ ������ ���̾ƿ� ����
		true,							//�޴��� ��������
		true,							//���ٸ� ��������
		InAsset							//��â���� ������� ����
	);
}

bool FMeshViewer::OnRequestClose()
{
	return true;
}


void FMeshViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	//�� ������ ����Ǵ� �Լ����� ���⼭ ���ε� ���ش�
	//�� �Լ��� �� ������ ȣ��ȴ�

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	//�θ��Լ� ��

	//SharedPtr�� SharedRef�� �������ֱ����� CreateSP ���
	//FViewportEditor�� �����Լ� ���ε�
	//CreateSP�� This ���� �ϰ��ִ�
	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_ViewportTab);
	TabManager->RegisterTabSpawner(ViewportTabId, tab)
	/*	.SetGroup(WorkspaceMenuCategory.ToSharedRef())*/;	
	//������Ʈ ���� ���� ���ε�

	FOnSpawnTab tab2 = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_DetailsTab);
	TabManager->RegisterTabSpawner(DetailsTabId, tab2)
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
	//������Ʈ ���� ���� ���ε�


	FOnSpawnTab tab3 = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_PreviewTab);
	TabManager->RegisterTabSpawner(PreviewTabId, tab3)
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
	//������Ʈ ���� ���� ���ε�

}


void FMeshViewer::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	//�θ��Լ� ��

	//�� �� ���� �Լ��� ���ε� ����
	TabManager->UnregisterTabSpawner(ViewportTabId);
	TabManager->UnregisterTabSpawner(DetailsTabId);
	TabManager->UnregisterTabSpawner(PreviewTabId);
}


FName FMeshViewer::GetToolkitFName() const
{
	return EditorName;
}

FText FMeshViewer::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FMeshViewer::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();	//â�� ������ �������� �̸�
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}

TSharedRef<SDockTab> FMeshViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)	//������Ʈ ����
		[
			//[] ���� ������ �����ϴ� �����̴�
			//SNew(SButton)
			//.Text(FText::FromString("TEst"))
			//SNew(STextBlock)
			//.Text(FText::FromString("ViewPortTab"))
			Viewport.ToSharedRef()		//������ args�� �����ߴ� �����Ϻ� â
		];
}

TSharedRef<SDockTab> FMeshViewer::Spawn_DetailsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FMeshViewer::Spawn_PreviewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			Preview.ToSharedRef()
		];
}
