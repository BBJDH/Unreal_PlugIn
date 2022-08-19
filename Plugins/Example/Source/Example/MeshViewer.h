
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"		//�⺻ �����͸���� �����ϴ� �θ� Ŭ����


/**
 * 
 */
class EXAMPLE_API FMeshViewer
	: public FAssetEditorToolkit
{
	//�̱��ϰ� �����ϰ� �������� �ø���ȹ�̴�
	//â�� ���� ����â�� �ִٸ� �ݰ� ���� ���� ����
public:
	static void OpenWindow(UObject* InAsset);		//â ����, ������ â�� �׻� ������ ���� ������ 
	static void Shutdown();							//���α׷��� ������ �̰� ���������� ���� �ݾ��ְ� �� ��ȹ


	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	//â�� ������ ��
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	//â�� ������ ��
	
	//FAssetEditorToolkit ���� �����Լ� override;
	virtual FName GetToolkitFName() const override;							//�������� �ĺ��� �̸��� ����
	virtual FText GetBaseToolkitName() const override;						//�����Ϳ� ��µ� �̸�
	virtual FString GetWorldCentricTabPrefix() const override;				//�����Ͱ� ���� ���� �̸��տ� ����� �������̸�
	virtual FLinearColor GetWorldCentricTabColorScale() const override;		//â�� ������ ������ �ؿ� ǥ�õǴ� ���� ���� ����


protected:
	virtual bool OnRequestClose() override;		//Toolkit�� ������ ȣ��Ǵ� �Լ�
												//false��ȯ�� â�� ����������

private:
	TSharedRef<SDockTab> Spawn_ViewportTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_PreviewTab(const FSpawnTabArgs& InArgs);


private:
	static TSharedPtr<FMeshViewer> Instance;		//�ڱ� �ڽſ� ���� �����͸� �������ְ� �� ��ȹ
	//���۷����� ���� ����Ѵ�

private:
	TSharedPtr<class IDetailsView> DetailsView;				//�����Ϻ� â(�����ʿ� �ߴ���)
	TSharedPtr<class SMeshObject_Viewport> Viewport;
	TSharedPtr<class SWidget> Preview;

private:
	void Open(UObject* InAsset);

private:
	static const FName EditorName;			//�� â�� �ĺ���
	static const FName ViewportTabId;		//�� �̸�
	static const FName DetailsTabId;		//�� �̸�
	static const FName PreviewTabId;		//�� �̸�
};
