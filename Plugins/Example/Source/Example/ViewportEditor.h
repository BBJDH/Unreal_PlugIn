
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"		//�⺻ �����͸���� �����ϴ� �θ� Ŭ����


/**
 * 
 */
class EXAMPLE_API FViewportEditor 
	: public FAssetEditorToolkit
{
	//�̱��ϰ� �����ϰ� �������� �ø���ȹ�̴�
	//â�� ���� ����â�� �ִٸ� �ݰ� ���� ���� ����
public:
	static void OpenWindow(UObject* InAsset);		//â ���� 
	static void Shutdown();							//���α׷��� ������ �̰� ���������� ���� �ݾ��ְ� �� ��ȹ

	
	//FAssetEditorToolkit ���� �����Լ� override;
	virtual FName GetToolkitFName() const override;							//�������� �ĺ��� �̸��� ����
	virtual FText GetBaseToolkitName() const override;						//�����Ϳ� ��µ� �̸�
	virtual FString GetWorldCentricTabPrefix() const override;				//�����Ͱ� ���� ���� �̸��տ� ����� �������̸�
	virtual FLinearColor GetWorldCentricTabColorScale() const override;		//â�� ������ ������ �ؿ� ǥ�õǴ� ���� ���� ����


protected:
	virtual bool OnRequestClose() override;		//Toolkit�� ������ ȣ��Ǵ� �Լ�
												//false��ȯ�� â�� ����������


private:
	static TSharedPtr<FViewportEditor> Instance;		//�ڱ� �ڽſ� ���� �����͸� �������ְ� �� ��ȹ

private:
	TSharedPtr<class IDetailsView> DetailsView;
	TSharedPtr<class SPreviewObject_Viewport> Viewport;
	TSharedPtr<class SWidget> Preview;

private:
	void Open(UObject* InAsset);

private:
	static const FName EditorName;			//�� â�� �ĺ���
	static const FName ViewportTabId;		//Open()
	//static const FName DetailsTabId;
	//static const FName PreviewTabId;
};
