// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands
	(
		"LoadMesh",								//����̸�
		FText::FromString("Load Mesh Data"),	//��ɿ� ���� ����(�Ƚᵵ ��)
		NAME_None,								//�θ� �ִ��� ����
		FEditorStyle::GetStyleSetName()			//������ ��Ÿ�� ����(�⺻��Ÿ�Ϸ� ������)
	)
{
	Command = MakeShareable(new FUICommandList());

}

FButtonCommand::~FButtonCommand()
{
	if(Command.IsValid())
		Command.Reset();
		
	//����Ʈ�������̱⿡ �ڵ� ������ ������ �׷��� ���� �۾��� ���ش�
}


void FButtonCommand::RegisterCommands()
{
	//TCommands ���������Լ�, ���� ��ư�� � ��ư���� ��������, � �Լ��� ���ε� �Ͽ� ���������� ���� ���� 
#define LOCTEXT_NAMESPACE ""	//���ӽ����̽� ����(������ �������� ��)
	UI_COMMAND
	(
		Id,									// ����� ID(FUICommandInfo)
		"LoadMesh",							// UI�� ��Ÿ�� Ŀ�ǵ�(�츮�� �� �ĺ���)
		"Load Mesh Data",					// ��ɿ� ���� ���� 
		EUserInterfaceActionType::Button,	// ��Ÿ���� �� Ÿ��(��ư, üũ�ڽ�, ��۹�ư ��,
		FInputChord()						// ����Ű ����(����Ű))
	);

	//UI_COMMAND(Id2, "MeshEditor", "Open Mesh Editor", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
	//���⿡ �Լ������͸� ���ε�
	Command->MapAction
	(
		Id,								//UI�� ���� ���� ����(FUICommandInfo)
		FExecuteAction::CreateRaw		//��������Ʈ�� ����(Bind�� �ƴ� Create�� ���� ����, ���ӳ��� �ƴϹǷ� UFUNCTION�� �������� ����)
		(
			this,						//�� Ŭ�����ν��Ͻ��� �ִ�
			&FButtonCommand::OnClicked	//�ش��Լ��� ���ε�
		),
		FCanExecuteAction()				//��ư�� ���� �� �ְ� ����
	);
	//Command->MapAction(Id2, FExecuteAction::CreateRaw(this, &ButtonCommand::OnClicked2), FCanExecuteAction());
}

void FButtonCommand::OnClicked()
{
	GLog->Log("Clicked!!!");


}

void FButtonCommand::OnClicked2()
{
	//Editor = MakeShareable(new FExampleEditor());
	//Editor->OpenEditor(EToolkitMode::Standalone, NewObject<UCExample>());
}
