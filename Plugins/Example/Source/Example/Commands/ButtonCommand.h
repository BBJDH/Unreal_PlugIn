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
	//SharedPtr ������ �ۺ����� �÷ȴ�, ��?

public:
	virtual void RegisterCommands() override;

private:

	void OnClicked();
	void OnClicked2();


public:
	TSharedPtr<FUICommandInfo> Id;
	//UI�� ���� Ŀ�ǵ�, Ŀ�ǵ� ����, Ÿ�� �� �ʿ� ������ ����

	TSharedPtr<FUICommandList> Command;
	//��ư ���ۿ� ���� ����� ����, ������ ��� ����
};
