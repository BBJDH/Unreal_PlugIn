

#include "ViewportEditor.h"


const FName FViewportEditor::EditorName = "ViewportEditor";

//const FName FViewportEditor::ViewportTabId = "Viewport";
//const FName FViewportEditor::DetailsTabId = "Details";
//const FName FViewportEditor::PreviewTabId = "Preview";

TSharedPtr<FViewportEditor> FViewportEditor::Instance = nullptr;

void FViewportEditor::OpenWindow(UObject* InAsset)
{
	//Instance는 static으로 선언되어 상위 메모리 공간으로 올라가있다
	if (Instance.IsValid()) //이미 창이 열려있다면
	{
		Instance->CloseWindow();	//창을 닫고

		Instance.Reset();			//연결된 메모리 해제
		Instance = nullptr;			//초기화
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
	//창 오픈시 에셋을 쥐고 들어감을 기억하자(에셋 에디터창을 만드는 중이다)


	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs args
	(
		false,									//
		false,									//이창을 잠글지(편집 불가하도록 만들지)
		true,									//검색허용 유무
		FDetailsViewArgs::ObjectsUseNameArea	//Prefix에 오브젝트 이름으로 출력
	);
	//DetailsView 위젯의 초기화 매개변수 설정
	DetailsView = prop.CreateDetailView(args);		//설정된 값으로 위젯 초기화, DetailsView에 할당
	//DetailsView->SetObject(InAsset);				//반드시 오브젝트 설정(세부정보 위젯인데 타깃 오브젝트 없이는 동작할 수 없다)
	DetailsView->SetObject(InAsset);				//반드시 오브젝트 설정(세부정보 위젯인데 타깃 오브젝트 없이는 동작할 수 없다)


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
		EToolkitMode::Standalone,		//에디터 모드 (독립실행으로 설정)
		TSharedPtr<IToolkitHost>(),		//
		EditorName,						//에디터 식별자
		layout,							//
		true,							//메뉴를 보여줄지
		true,							//툴바를 보여줄지
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
