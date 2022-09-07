
#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

/**
에셋 미리보기 창 생성
이 창도 Scene으로 취급됨

간단하게 바닥에 Floor를 깔고 위에 StaticMesh 생성해서 보여줌
 */
class EXAMPLE_API SMeshObject_Viewport
	: public SEditorViewport
	, public FGCObject
{
public:
	SMeshObject_Viewport();

	//실제 UI를 생성해줄 함수 실제 생성자 역할
	void Construct(const FArguments& InArgs);
	//생성과 함께 디자인도 같이 결정해줌

public:
	TSharedRef<class FAdvancedPreviewScene> GetPreviewScene();
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

protected:
	//카메라 객체를 만들어 아래의 ViewportClient에 결합, Scene 렌더링
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TSharedPtr<class FAdvancedPreviewScene> Scene;
	//카메라
	TSharedPtr<class FPreviewObjectViewport_Client> ViewportClient;

	//Scene 좌쯕 상단에 보여질 텍스트 라인
	TSharedPtr<SVerticalBox> OverlayText;

	//Scene에 보여질 객체
	class UStaticMeshComponent* Mesh;
	class UStaticMeshComponent* FloorMesh;

};
