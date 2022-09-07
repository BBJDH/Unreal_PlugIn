

#include "PreviewObjectViewport_Client.h"
#include "AdvancedPreviewScene.h"
#include "SMeshObject_Viewport.h"

FPreviewObjectViewport_Client::FPreviewObjectViewport_Client(FPreviewScene* InPreviewScene, const TSharedRef<class SMeshObject_Viewport>& InViewport)
	: FEditorViewportClient
	(
		nullptr,			//�̰�ü�� �θ�Ŭ���̾�Ʈ�� �ִ���??
		InPreviewScene,		//����� SceneS
		StaticCastSharedRef<SEditorViewport>(InViewport)	//StaticCastSharedRef �˾ƺ���, InViewport�� ī�޶����� �������
		//WeakPtr���� SharedRef�� ĳ���� �ٿ�ĳ���ÿ��� ����
	)
{
	//�� ��弳��, ���������� �������·� ���
	SetViewMode(VMI_Lit);	//������ ���� ���`

	AdvancedPreviewScene = (FAdvancedPreviewScene *)PreviewScene; 
	//FEditorViewportClient(�θ�)�� PreviewScene������ ĳ����


	//SetViewLocation(FVector(0, 3, 2));						//ī�޶� ��ġ
	SetViewRotation(FRotator(-45, -90, 0));					//ī�޶� ȸ��
	SetViewLocationForOrbiting(FVector(0,0,75), 500);	
	//SetViewLocationForOrbiting(FVector::ZeroVector, 500);	
	//Orbit: �˵��� ���� �ٶ󺸴� ���� ���� �������� 500 �̵�
	//���� ������ �߽���(ZeroVector)���κ��� ������ �Ÿ��� �ٶ�
}

FPreviewObjectViewport_Client::~FPreviewObjectViewport_Client()
{

}
