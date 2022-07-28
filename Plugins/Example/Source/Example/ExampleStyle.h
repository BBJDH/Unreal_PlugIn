#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class EXAMPLE_API FExampleStyle
{
public:
	static TSharedPtr<FExampleStyle> Get();
	//싱글턴 생성 
	static void Shutdown();
	//싱글턴 해제 ShutDown은 겹치는 함수가 있음(문제 발생)

private:
	static TSharedPtr<FExampleStyle> Instance;
	//싱글턴 인스턴스

public:
	FExampleStyle();
	~FExampleStyle();
	//쉐어드 포인터의 생성자는 퍼블릭이어야 한다

private:
	void RegisterIcon(const FString& InName, const FString & InPath, const FVector2D & InIconSize, FSlateIcon& OutSlateIcon);

private:
	const FName StyleSetName = "ExampleStyle";

	TSharedPtr<class FSlateStyleSet> StyleSet;

public:
	//로드할 아이콘
	FSlateIcon ToolBar_Icon;
	FSlateIcon ToolBar_Icon2;
	FSlateIcon MenuItem_Icon;

};
