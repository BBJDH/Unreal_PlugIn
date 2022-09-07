
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
	//Instance는 static으로 선언되어 상위 메모리 공간으로 올라가있다
	if (Instance.IsValid()) //이미 창이 열려있다면
	{
		Instance->CloseWindow();	//창을 닫고

		Instance.Reset();			//연결된 메모리 해제
		Instance = nullptr;			//초기화
	}

	Instance = MakeShareable(new FMeshViewer());	//FViewportEditor 기본창 생성
	Instance->Open(InAsset);
}

void FMeshViewer::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		//가비지 컬렉터가 꺼지기때문에 윈도우 자체에서 제거하도록 설정
		//만약 아래를 활성화 하면 프로그램이 꺼지고나서 터진다
		//Instance.Reset();
		//Instance = nullptr;
	}
}



void FMeshViewer::Open(UObject* InAsset)
{
	//창 오픈시 에셋을 쥐고 들어감을 기억하자(에셋 에디터창을 만드는 중이다)


	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//에디터 모듈 PropertyEditor 가져옴


	//Spawn_DetailsTab에서 사용될 DetailsView의 파라메터를 결졍해줄 구조체 args 생성
	FDetailsViewArgs args
	(
		false,									//선택할때마다 업데이트 할지
		false,									//이창을 잠글지(편집 불가하도록 만들지, 뷰어용)
		true,									//검색허용 유무(항목찾기)
		FDetailsViewArgs::ObjectsUseNameArea	//Prefix에 오브젝트 이름으로 출력 기본설정인 액터로 하면 액터창이 뜸
	);
	//DetailsView 위젯의 초기화 매개변수 설정
	DetailsView = prop.CreateDetailView(args);		//설정된 값으로 위젯 초기화, DetailsView에 할당
	//추후에 여기에 계속 커스터마이징 가능
	DetailsView->SetObject(InAsset);				//SetObject해주지 않아도 창은 뜬다
	//InAsset과 관련된 에셋까지 같이 동기화

	//슬래이트 동적할당은 SNew임을 잊지 말자 이 SEditorViewport를 상속받은 상태이다
	Viewport = SNew(SMeshObject_Viewport);

	FAdvancedPreviewSceneModule& scene = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");	//AdvancedPreviewScene 씬영역 이름(모듈이름)
	Preview = scene.CreateAdvancedPreviewSceneSettingsWidget(Viewport->GetPreviewScene());


	//창 구역을 지정해준다 말그대로 레이아웃 설정!
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("ViewportEditor_Layout")
		->AddArea	//영역 추가
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)	//NewPrimaryArea영역에서 수평분할공간 생성 (하나였던 공간이 둘로 나뉨 1대 9로 나눌계획)
			->Split		//둘로 나뉜공간중 윗공간
			(
				FTabManager::NewStack()		//이지역에서 사용될 탭 생성(스택처럼 위로 슬레이트를 쌓음)
				->SetSizeCoefficient(0.1f)	//위에서 말한 처음 분할된 10프로 공간을 사용
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)	//탭 추가 (툴바아이디, 툴바탭이 열릴때 탭이 열린상태로 설정)
				//툴바아이디는 생성시 기본으로 정해져있기때문에 가져다 쓰면 된다
			)
			->Split	//둘로 나뉜공간중 아랫공간(90프로)
			(
				//아래의 수평공간에서 NewSplitter를 통해 다시 분할
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)	//이미 나눠진 아랫공간을 이번에는 수직 분할
				->SetSizeCoefficient(0.75f)			//그중 왼쪽 공간을 75로 지정
				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)
				->Split
				(
					//우측 공간을 다시 또 나눔
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


	FAssetEditorToolkit::InitAssetEditor	//실제 창을 띄우는 작업
	(
		EToolkitMode::Standalone,		//에디터 모드 (독립창으로 설정, 월드센트릭은 창이 종속됨, 저장/열기창처럼!)
		TSharedPtr<IToolkitHost>(),		//부모창지정(없으므로 빈 객체)
		EditorName,						//에디터 식별자 ("MeshViewer")
		layout,							//위에서 지정한 레이아웃 설정
		true,							//메뉴를 보여줄지
		true,							//툴바를 보여줄지
		InAsset							//이창에서 물고들어가는 에셋
	);
}

bool FMeshViewer::OnRequestClose()
{
	return true;
}


void FMeshViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	//탭 생성시 실행되는 함수들을 여기서 바인딩 해준다
	//이 함수는 탭 생성시 호출된다

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	//부모함수 콜

	//SharedPtr을 SharedRef로 매핑해주기위해 CreateSP 사용
	//FViewportEditor의 지정함수 바인딩
	//CreateSP가 This 콜을 하고있다
	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_ViewportTab);
	TabManager->RegisterTabSpawner(ViewportTabId, tab)
	/*	.SetGroup(WorkspaceMenuCategory.ToSharedRef())*/;	
	//슬래이트 공간 구성 바인딩

	FOnSpawnTab tab2 = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_DetailsTab);
	TabManager->RegisterTabSpawner(DetailsTabId, tab2)
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
	//슬래이트 공간 구성 바인딩


	FOnSpawnTab tab3 = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_PreviewTab);
	TabManager->RegisterTabSpawner(PreviewTabId, tab3)
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
	//슬래이트 공간 구성 바인딩

}


void FMeshViewer::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	//부모함수 콜

	//각 탭 생성 함수들 바인딩 해제
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
	return EditorName.ToString();	//창이 탭으로 들어갔을때의 이름
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}

TSharedRef<SDockTab> FMeshViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)	//슬레이트 생성
		[
			//[] 안이 컨텐츠 구성하는 문법이다
			//SNew(SButton)
			//.Text(FText::FromString("TEst"))
			//SNew(STextBlock)
			//.Text(FText::FromString("ViewPortTab"))
			Viewport.ToSharedRef()		//위에서 args로 생성했던 디테일뷰 창
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
