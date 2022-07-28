#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class EXAMPLE_API FExampleStyle
{
public:
	static TSharedPtr<FExampleStyle> Get();
	//�̱��� ���� 
	static void Shutdown();
	//�̱��� ���� ShutDown�� ��ġ�� �Լ��� ����(���� �߻�)

private:
	static TSharedPtr<FExampleStyle> Instance;
	//�̱��� �ν��Ͻ�

public:
	FExampleStyle();
	~FExampleStyle();
	//����� �������� �����ڴ� �ۺ��̾�� �Ѵ�

private:
	void RegisterIcon(const FString& InName, const FString & InPath, const FVector2D & InIconSize, FSlateIcon& OutSlateIcon);

private:
	const FName StyleSetName = "ExampleStyle";

	TSharedPtr<class FSlateStyleSet> StyleSet;

public:
	//�ε��� ������
	FSlateIcon ToolBar_Icon;
	FSlateIcon ToolBar_Icon2;
	FSlateIcon MenuItem_Icon;

};
