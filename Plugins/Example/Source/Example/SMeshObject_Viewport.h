
#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

/**
에셋 미리보기 창 생성
이 창도 Scene으로 취급됨
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
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TSharedPtr<class FAdvancedPreviewScene> Scene;
	TSharedPtr<class FPreviewObjectViewport_Client> ViewportClient;

	TSharedPtr<SVerticalBox> OverlayText;

	class UStaticMeshComponent* Mesh;
	class UStaticMeshComponent* FloorMesh;

};
