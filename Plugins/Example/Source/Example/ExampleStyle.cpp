

#include "ExampleStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FExampleStyle> FExampleStyle::Instance = nullptr;

TSharedPtr<FExampleStyle> FExampleStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FExampleStyle());
	return Instance;
}

void FExampleStyle::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}


FExampleStyle::FExampleStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));
	//쉐어드 포인터의 생성자는 퍼블릭이어야 한다

	FString path = IPluginManager::Get().FindPlugin("Example")->GetContentDir();
	//플러그인(모듈네임)을 찾아 해당 컨텐츠 폴더 경로를 반환(GetContentDir)
	//GLog->Log(*path);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *path);
	StyleSet->SetContentRoot(path);
	//FSlateStyleSet의 기본 경로를 등록(아이콘 추가할 때마다 여기서 쉽게 부르기 위해)
	
	// 아이콘 등록(폴더로부터)  (아이콘 이름[식별자], 경로 "/"에 파일명 더함, 사이즈, 할당 할 곳)
	//"aaa"/"bbb" => "aaa/bbb"
	RegisterIcon("ToolBar_Icon", path / TEXT("T_Radial_Local_Space.png"), FVector2D(48, 48), ToolBar_Icon);
	RegisterIcon("ToolBar_Icon2", path / TEXT("icon_MatEd_Home_40x.png"), FVector2D(48, 48), ToolBar_Icon2);
	RegisterIcon("MenuItem_Icon", path / TEXT("T_Radial_Local_Space.png"), FVector2D(16, 16), MenuItem_Icon);



	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	//공유 포인터 SharedPtr이 가진 주소반환함수 Get에 대한 참조 ->FSlateStyleSet 반환(path를 포함)
	
}

FExampleStyle::~FExampleStyle()
{

	if (StyleSet.IsValid() == false) return;

	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);
	StyleSet.Reset();
}


void FExampleStyle::RegisterIcon(const FString& InName, const FString & InPath, const FVector2D & InIconSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath, InIconSize);
	//런타임에서는 new 쓰면 안된다 에디터라서 쓰지만 그래도..
	//FSlateImageBrush : 아이콘 표현을 위한 브러시

	FString name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(name), brush);
	//StyleSetName 의 기본 경로로부터 함수로 받아온 InName 으로 아이콘을 등록, 나중에 InName를 식별자로도 사용

	//최종적으로 OutSlateIcon에 할당 및 반환
	OutSlateIcon = FSlateIcon(FName(StyleSetName), FName(name));
	//어떤 스타일셋에 속해있는지, 그리고 이름
}