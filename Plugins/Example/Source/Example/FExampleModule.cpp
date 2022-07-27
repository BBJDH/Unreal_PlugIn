
#include "FExampleModule.h"
#include "ExampleStyle.h"
#include "Commands/ButtonCommand.h"
#include "ExampleDebuggerCategory.h"


#include "LevelEditor.h"
#include "GameplayDebugger.h"

#define LOCTEXT_NAMESPACE "FExampleModule"
//���� ������ �����ϱ� ���Ѱ�
//���� �����̽��� ��Ƶ� ���ӽ����̽� �̸��� FExampleModule��
//�۷ι� ������ ���� �۾��Ҷ��� ���� ��ũ�θ� ����ؾ� �Ѵ� 

/*
�÷������� ���� �ٷﺼ ����
��� ���ٿ� ��ư �߰�
 - �׽�Ʈ������ ������ �޼����� ����
 ���� ������ �޴����� �߰�

�������� ������ ���������� ��Ŭ�� - ���� ���� �Ŵ� �߰�

���� ������ Ŭ���� ���� ������ â�� ��ư �߰�
 - �ش� �޽ð� �������ִ� ������������ �����Ͽ� ������

*/

void FExampleModule::StartupModule()
{

	FExampleStyle::Get();
	//�̱��� ����

	//����� �����Ҷ� ����


	//ToolBar
	{
		Extender = MakeShareable(new FExtender());
		//����Ʈ ������ �Ҵ�, �޴��� Ȯ�� (�����°� ����)

		FButtonCommand::Register();
		//�̱��� ����

		//��������Ʈ ����, ��ȯ(��ư�� ��ϵɶ� �����ϴ� ������ ���ε�)
		FToolBarExtensionDelegate toolBar = FToolBarExtensionDelegate::CreateRaw
		(
			this,
			&FExampleModule::AddToolBar
		);

		//�̹� ���ǵ� ��������Ʈ�� �Լ� ���ε�

		Extender->AddToolBarExtension		//���� �޴� �߰� �Լ�
		(
			"Compile",						//Compile ����
			EExtensionHook::Before,			//������ ���� �տ� ����(�� �Ǵ� ���ǽ��ۺκ� ��������)
			FButtonCommand::Get().Command,	// ��ư���� �ҷ���(TCommands.Get�� �����ϰ��ִ� Weak�����͸� Shared�����ͷ� Pin()�� ���� ĳ�����ؼ� ��ȯ
			toolBar							//������ �������̼� ���ε�
		);
		//������ Ȯ����(Compile)���� ���� ������ Ȯ���մϴ�. : ���ٿ� �߰�
		//�̱��� ����


		//Ȯ���� ����ϱ����� Ÿ���� ���� ������ ����� �ҷ��´�,LoadModuleChecked<FLevelEditorModule>
		//FLevelEditorModule�� ���۷����� ��ȯ(���������� �о��)
		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
		//GetToolBarExtensibilityManager()���������Ϳ��� ���ٸ� ��ȯ, AddExtender() ���� Ȯ�� ���

	}


	//Gameplay Debugger
	{

		//gameplayDebugger.Get().RegisterCategory("Example", );
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();
		//�̱��� ����
		
		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&FExampleDebuggerCategory::MakeInstance);
		//��������Ʈ ����, ��� ����� gameplayDebugger�� ��� �Լ� ȣ���� �ɶ� ����� �Լ� ���ε��� ��������Ʈ
		gameplayDebugger.Get().RegisterCategory
		(
			"Example",													//����� ī�װ� �̸�
			category,													//�Ķ���Ͱ� ���� ��������Ʈ(TSharedRef ��ȯ)
			EGameplayDebuggerCategoryState::EnabledInGameAndSimulate	//���Ӹ��, �ùķ��̼Ǹ��, �Ѵ� �������� ����
		);
		gameplayDebugger.NotifyCategoriesChanged();						//ī�װ��� �ٲ������ ȣ��
		//ī�װ��� �ٲ������ �˸�

	}
}

void FExampleModule::ShutdownModule()
{
	if (IGameplayDebugger::IsAvailable())//����� �̱����� �����Ǿ� �ִٸ�
		IGameplayDebugger::Get().UnregisterCategory("Example");		//�ش� ī�װ� ����

	//����� ����� �� ����
	FExampleStyle::Shutdown();

}



void FExampleModule::AddToolBar(FToolBarBuilder & InBuilder)
{
	//FToolBarBuilder : ���ٻ���
	//levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	//��Ͻ� ����� �Լ�(��ư �߰��� �ؾ��� ��)
	//���� ����� ��� ���� ������ ���⿡ ����
	InBuilder.AddSeparator();
	//��Ƽ�� �߰�
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().Id,
		NAME_None,
		FText::FromString("Load Mesh"),			//�����Ϳ� ��Ÿ�� ��ư�̸�
		FText::FromString("Load Mesh Data"),	//����
		//TAttribute<FSlateIcon>()				//������ ����Ʈ
		FExampleStyle::Get()->ToolBar_Icon		//������ �츮�� �����
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