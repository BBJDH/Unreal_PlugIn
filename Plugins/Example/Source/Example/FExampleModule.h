
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FExampleModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void AddToolBar(FToolBarBuilder& InBuilder);
	void AddToolBar2(FToolBarBuilder& InBuilder);

	void AddMenuItem(FMenuBuilder& InBuilder);


private:
	TSharedPtr<FExtender> Extender;
	//F���λ�(�Ϲ�Ŭ����) �⺻ ���漱��Ǿ��ִ�
	//UI Ȯ�忡���� ����, 


	/*
	����� ������, �⺻ ���漱������ �����ִ�
	����ũ �����͵� ���������� ����ũ ���۷����� �������� �ʴ´�
	(������ �������� �����Ƿ� ���۷����� ���� �� ����)
	
	��ũ ������
	�츮�� ���� ���� ������ó�� ��� ����, ��۸� �������� ������ ����
	
	*/
};
