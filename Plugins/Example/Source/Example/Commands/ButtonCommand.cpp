// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands
	(
		"LoadMesh",								//명령이름
		FText::FromString("Load Mesh Data"),	//명령에 대한 설명(안써도 됨)
		NAME_None,								//부모가 있는지 유무
		FEditorStyle::GetStyleSetName()			//에디터 스타일 지정(기본스타일로 지정함)
	)
{
	Command = MakeShareable(new FUICommandList());

}

FButtonCommand::~FButtonCommand()
{
	if(Command.IsValid())
		Command.Reset();
		
	//스마트포인터이기에 자동 해제가 되지만 그래도 해제 작업을 해준다
}


void FButtonCommand::RegisterCommands()
{
	//TCommands 순수가상함수, 실제 버튼이 어떤 버튼으로 보여질지, 어떤 함수를 바인드 하여 동작할지에 대한 정보 
#define LOCTEXT_NAMESPACE ""	//네임스페이스 열기(원래는 국가명이 들어감)
	UI_COMMAND
	(
		Id,									// 명령의 ID(FUICommandInfo)
		"LoadMesh",							// UI에 나타날 커맨드(우리가 쓸 식별자)
		"Load Mesh Data",					// 명령에 대한 설명 
		EUserInterfaceActionType::Button,	// 나타나게 할 타입(버튼, 체크박스, 토글버튼 등,
		FInputChord()						// 단축키 정의(단축키))
	);

	//UI_COMMAND(Id2, "MeshEditor", "Open Mesh Editor", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
	//여기에 함수포인터를 바인딩
	Command->MapAction
	(
		Id,								//UI에 대한 정보 연결(FUICommandInfo)
		FExecuteAction::CreateRaw		//델리게이트와 동일(Bind가 아닌 Create를 통해 연결, 게임내가 아니므로 UFUNCTION도 선언하지 않음)
		(
			this,						//이 클래스인스턴스에 있는
			&FButtonCommand::OnClicked	//해당함수를 바인딩
		),
		FCanExecuteAction()				//버튼이 눌릴 수 있게 설정
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
