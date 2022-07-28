

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
	//����� �������� �����ڴ� �ۺ��̾�� �Ѵ�

	FString path = IPluginManager::Get().FindPlugin("Example")->GetContentDir();
	//�÷�����(������)�� ã�� �ش� ������ ���� ��θ� ��ȯ(GetContentDir)
	//GLog->Log(*path);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *path);
	StyleSet->SetContentRoot(path);
	//FSlateStyleSet�� �⺻ ��θ� ���(������ �߰��� ������ ���⼭ ���� �θ��� ����)
	
	// ������ ���(�����κ���)  (������ �̸�[�ĺ���], ��� "/"�� ���ϸ� ����, ������, �Ҵ� �� ��)
	//"aaa"/"bbb" => "aaa/bbb"
	RegisterIcon("ToolBar_Icon", path / TEXT("T_Radial_Local_Space.png"), FVector2D(48, 48), ToolBar_Icon);
	RegisterIcon("ToolBar_Icon2", path / TEXT("icon_MatEd_Home_40x.png"), FVector2D(48, 48), ToolBar_Icon2);
	RegisterIcon("MenuItem_Icon", path / TEXT("T_Radial_Local_Space.png"), FVector2D(16, 16), MenuItem_Icon);



	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	//���� ������ SharedPtr�� ���� �ּҹ�ȯ�Լ� Get�� ���� ���� ->FSlateStyleSet ��ȯ(path�� ����)
	
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
	//��Ÿ�ӿ����� new ���� �ȵȴ� �����Ͷ� ������ �׷���..
	//FSlateImageBrush : ������ ǥ���� ���� �귯��

	FString name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(name), brush);
	//StyleSetName �� �⺻ ��ηκ��� �Լ��� �޾ƿ� InName ���� �������� ���, ���߿� InName�� �ĺ��ڷε� ���

	//���������� OutSlateIcon�� �Ҵ� �� ��ȯ
	OutSlateIcon = FSlateIcon(FName(StyleSetName), FName(name));
	//� ��Ÿ�ϼ¿� �����ִ���, �׸��� �̸�
}