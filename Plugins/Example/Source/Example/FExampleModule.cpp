
#include "FExampleModule.h"
#include "ExampleStyle.h"
#include "Commands/ButtonCommand.h"
#include "ExampleDebuggerCategory.h"


#include "LevelEditor.h"
#include "GameplayDebugger.h"

#define LOCTEXT_NAMESPACE "FExampleModule"
//다중 국가를 지원하기 위한것
//네임 스페이스로 잡아둠 네임스페이스 이름을 FExampleModule로
//글로벌 지원시 본래 작업할때는 위의 매크로를 사용해야 한다 

/*
플러그인을 통해 다뤄볼 내용
상단 툴바에 버튼 추가
 - 테스트용으로 눌러서 메세지만 띄우기
 같은 내용을 메뉴에도 추가

에디터의 콘텐츠 브라우저에서 우클릭 - 에셋 생성 매뉴 추가

액터 생성후 클릭시 우측 디테일 창에 버튼 추가
 - 해당 메시가 가지고있는 렌더링정보를 추출하여 보여줌

*/

void FExampleModule::StartupModule()
{

	FExampleStyle::Get();
	//싱글턴 생성

	//모듈이 시작할때 실행


	//ToolBar
	{
		Extender = MakeShareable(new FExtender());
		//스마트 포인터 할당, 메뉴바 확장 (접히는게 가능)

		FButtonCommand::Register();
		//싱글턴 생성

		//델리게이트 생성, 반환(버튼에 등록될때 시행하는 내용을 바인딩)
		FToolBarExtensionDelegate toolBar = FToolBarExtensionDelegate::CreateRaw
		(
			this,
			&FExampleModule::AddToolBar
		);

		//이미 정의된 델리게이트에 함수 바인딩

		Extender->AddToolBarExtension		//툴바 메뉴 추가 함수
		(
			"Compile",						//Compile 구역
			EExtensionHook::Before,			//컴파일 섹션 앞에 삽입(뒤 또는 섹션시작부분 지정가능)
			FButtonCommand::Get().Command,	// 버튼정보 불러옴(TCommands.Get는 내포하고있는 Weak포인터를 Shared포인터로 Pin()을 통해 캐스팅해서 반환
			toolBar							//실행할 델리게이션 바인딩
		);
		//지정된 확장점(Compile)에서 도구 모음을 확장합니다. : 툴바에 추가
		//싱글톤 접근


		//확장을 등록하기위할 타겟인 레벨 에디터 모듈을 불러온다,LoadModuleChecked<FLevelEditorModule>
		//FLevelEditorModule의 레퍼런스로 반환(모듈네임으로 읽어옴)
		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
		//GetToolBarExtensibilityManager()레벨에디터에서 툴바를 반환, AddExtender() 통해 확장 등록

	}


	//Gameplay Debugger
	{

		//gameplayDebugger.Get().RegisterCategory("Example", );
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();
		//싱글턴 생성
		
		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&FExampleDebuggerCategory::MakeInstance);
		//델리게이트 생성, 모듈 실행시 gameplayDebugger의 등록 함수 호출이 될때 실행될 함수 바인딩될 델리게이트
		gameplayDebugger.Get().RegisterCategory
		(
			"Example",													//디버그 카테고리 이름
			category,													//파라미터가 없는 델리게이트(TSharedRef 반환)
			EGameplayDebuggerCategoryState::EnabledInGameAndSimulate	//게임모드, 시뮬레이션모드, 둘다 보여줄지 여부
		);
		gameplayDebugger.NotifyCategoriesChanged();						//카테고리가 바뀌었음을 호출
		//카테고리가 바뀌었음을 알림

	}
}

void FExampleModule::ShutdownModule()
{
	if (IGameplayDebugger::IsAvailable())//디버거 싱글턴이 생성되어 있다면
		IGameplayDebugger::Get().UnregisterCategory("Example");		//해당 카테고리 제거

	//모듈이 종료될 때 실행
	FExampleStyle::Shutdown();

}



void FExampleModule::AddToolBar(FToolBarBuilder & InBuilder)
{
	//FToolBarBuilder : 툴바생성
	//levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	//등록시 실행될 함수(버튼 추가시 해야할 일)
	//툴바 모양이 어떻게 정의 될지를 여기에 정의
	InBuilder.AddSeparator();
	//파티션 추가
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().Id,
		NAME_None,
		FText::FromString("Load Mesh"),			//에디터에 나타날 버튼이름
		FText::FromString("Load Mesh Data"),	//툴팁
		//TAttribute<FSlateIcon>()				//아이콘 디폴트
		FExampleStyle::Get()->ToolBar_Icon		//아이콘 우리가 만든거
	);

}

void FExampleModule::AddToolBar2(FToolBarBuilder & InBuilder)
{

}

void FExampleModule::AddMenuItem(FMenuBuilder& InBuilder)
{

}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExampleModule, Example)