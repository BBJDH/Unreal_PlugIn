
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"		//기본 에디터모양을 제공하는 부모 클래스


/**
 * 
 */
class EXAMPLE_API FViewportEditor 
	: public FAssetEditorToolkit
{
	//싱글턴과 유사하게 전역으로 올릴계획이다
	//창을 열때 기존창이 있다면 닫고 새로 열기 위함
public:
	static void OpenWindow(UObject* InAsset);		//창 열기 
	static void Shutdown();							//프로그램이 닫힐때 이게 열려있으면 같이 닫아주게 할 계획

	
	//FAssetEditorToolkit 순수 가상함수 override;
	virtual FName GetToolkitFName() const override;							//에디터의 식별자 이름을 리턴
	virtual FText GetBaseToolkitName() const override;						//에디터에 출력될 이름
	virtual FString GetWorldCentricTabPrefix() const override;				//에디터가 물고갈 에셋 이름앞에 출력할 에디터이름
	virtual FLinearColor GetWorldCentricTabColorScale() const override;		//창이 열릴때 아이콘 밑에 표시되는 에셋 고유 색상


protected:
	virtual bool OnRequestClose() override;		//Toolkit이 닫힐때 호출되는 함수
												//false반환시 창이 닫히지않음


private:
	static TSharedPtr<FViewportEditor> Instance;		//자기 자신에 대한 포인터를 가지고있게 할 계획

private:
	TSharedPtr<class IDetailsView> DetailsView;
	TSharedPtr<class SPreviewObject_Viewport> Viewport;
	TSharedPtr<class SWidget> Preview;

private:
	void Open(UObject* InAsset);

private:
	static const FName EditorName;			//이 창의 식별자
	static const FName ViewportTabId;		//Open()
	//static const FName DetailsTabId;
	//static const FName PreviewTabId;
};
