
#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

/**
���� �̸����� â ����
�� â�� Scene���� ��޵�

�����ϰ� �ٴڿ� Floor�� ��� ���� StaticMesh �����ؼ� ������
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
	//ī�޶� ��ü�� ����� �Ʒ��� ViewportClient�� ����, Scene ������
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TSharedPtr<class FAdvancedPreviewScene> Scene;
	//ī�޶�
	TSharedPtr<class FPreviewObjectViewport_Client> ViewportClient;

	//Scene �©P ��ܿ� ������ �ؽ�Ʈ ����
	TSharedPtr<SVerticalBox> OverlayText;

	//Scene�� ������ ��ü
	class UStaticMeshComponent* Mesh;
	class UStaticMeshComponent* FloorMesh;

};
