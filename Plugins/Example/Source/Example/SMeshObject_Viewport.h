
#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

/**
���� �̸����� â ����
�� â�� Scene���� ��޵�
 */
class EXAMPLE_API SMeshObject_Viewport
	: public SEditorViewport
	, public FGCObject
{
public:
	SMeshObject_Viewport();

	//���� UI�� �������� �Լ� ���� ������ ����
	void Construct(const FArguments& InArgs);
	//������ �Բ� �����ε� ���� ��������

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
