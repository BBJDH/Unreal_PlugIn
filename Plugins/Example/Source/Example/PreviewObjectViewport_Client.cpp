

#include "PreviewObjectViewport_Client.h"
#include "AdvancedPreviewScene.h"
#include "SMeshObject_Viewport.h"

FPreviewObjectViewport_Client::FPreviewObjectViewport_Client(FPreviewScene* InPreviewScene, const TSharedRef<class SMeshObject_Viewport>& InViewport)
	: FEditorViewportClient
	(
		nullptr,			//이객체의 부모클라이언트가 있는지??
		InPreviewScene,		//물고들어갈 SceneS
		StaticCastSharedRef<SEditorViewport>(InViewport)	//StaticCastSharedRef 알아볼것, InViewport가 카메라임을 기억하자
		//WeakPtr에서 SharedRef로 캐스팅 다운캐스팅에도 쓰임
	)
{
	//뷰 모드설정, 라이팅포함 설정상태로 출력
	SetViewMode(VMI_Lit);	//라이팅 포함 모드`

	AdvancedPreviewScene = (FAdvancedPreviewScene *)PreviewScene; 
	//FEditorViewportClient(부모)의 PreviewScene변수를 캐스팅


	//SetViewLocation(FVector(0, 3, 2));						//카메라 위치
	SetViewRotation(FRotator(-45, -90, 0));					//카메라 회전
	SetViewLocationForOrbiting(FVector(0,0,75), 500);	
	//SetViewLocationForOrbiting(FVector::ZeroVector, 500);	
	//Orbit: 궤도를 뜻함 바라보는 방향 기준 공전으로 500 이동
	//내가 지정한 중심점(ZeroVector)으로부터 지정한 거리로 바라봄
}

FPreviewObjectViewport_Client::~FPreviewObjectViewport_Client()
{

}
