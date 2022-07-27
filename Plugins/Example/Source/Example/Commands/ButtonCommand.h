// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

/**
 * 
 */
class EXAMPLE_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();
	//SharedPtr 때문에 퍼블릭으로 올렸다, 왜?

public:
	virtual void RegisterCommands() override;

private:

	void OnClicked();
	void OnClicked2();


public:
	TSharedPtr<FUICommandInfo> Id;
	//UI에 대한 커맨드, 커맨드 설명, 타입 등 필요 내용을 정의

	TSharedPtr<FUICommandList> Command;
	//버튼 동작에 관한 기능을 관리, 여러개 등록 가능
};
