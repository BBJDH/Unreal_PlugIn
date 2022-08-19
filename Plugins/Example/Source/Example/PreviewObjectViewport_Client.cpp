

#include "PreviewObjectViewport_Client.h"
#include "AdvancedPreviewScene.h"

FPreviewObjectViewport_Client::FPreviewObjectViewport_Client(FPreviewScene* InPreviewScene, const TSharedRef<class SMeshObject_Viewport>& InViewport)
	: FEditorViewportClient
	(
		nullptr, 
		InPreviewScene 
		//StaticCastSharedRef<SEditorViewport>(InViewport)
		//WeakPtr에서 SharedRef로 캐스팅 다운캐스팅에도 쓰임
	)
{
	//뷰 모드설정, 라이팅포함 설정상태로 출력
	SetViewMode(VMI_Lit);

	AdvancedPreviewScene = (FAdvancedPreviewScene *)PreviewScene; 
	//FEditorViewportClient(부모)의 PreviewScene변수를 캐스팅


	SetViewLocation(FVector(0, 3, 2));						//카메라 위치
	SetViewRotation(FRotator(-45, -90, 0));					//카메라 회전
	SetViewLocationForOrbiting(FVector::ZeroVector, 500);	
	//Orbit: 궤도를 뜻함 바라보는 방향 기준 공전으로 500 이동
}

FPreviewObjectViewport_Client::~FPreviewObjectViewport_Client()
{

}
