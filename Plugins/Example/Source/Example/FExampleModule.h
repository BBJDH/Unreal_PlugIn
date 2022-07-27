
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
	//F접두사(일반클래스) 기본 전방선언되어있다
	//UI 확장에대한 정의, 


	/*
	쉐어드 포인터, 기본 전방선언으로 잡혀있다
	유니크 포인터도 존재하지만 유니크 레퍼런스가 존재하지 않는다
	(유일한 소유권을 가지므로 레퍼런스가 생길 수 없다)
	
	위크 포인터
	우리가 흔히 쓰는 포인터처럼 사용 가능, 댕글링 포인터의 위험이 존재
	
	*/
};
