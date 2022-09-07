
#include "SMeshObject_Viewport.h"
#include "PreviewObjectViewport_Client.h"
#include "AdvancedPreviewScene.h"
#include "Materials/MaterialInstanceConstant.h"


SMeshObject_Viewport::SMeshObject_Viewport()
{
	//우측 탭인 프리뷰 씬세팅 구성할 객체, 보여질 객체들을 관리
	Scene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
}


//실제 UI를 생성해줄 함수
void SMeshObject_Viewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
	//부모 함수 콜


	//Viewport 안에서도 이렇게 구획을 지정하여 출력 가능
	ViewportOverlay->AddSlot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		.Padding(10)
		[
			SAssignNew(OverlayText, SVerticalBox)
		];


	OverlayText->ClearChildren();
	OverlayText->AddSlot()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Viewport"))
		.TextStyle(FEditorStyle::Get(), "TextBlock.ShadowText")
		.ColorAndOpacity(FLinearColor::Blue)	//파란색 TextBlock 형성, Viewport라고 왼쪽 상단에 출력
		];

	//Scene에 바닥 깔아줄 floormesh 생성
	UStaticMesh* floormesh = LoadObject<UStaticMesh>
		(
			nullptr,											//Outer, Unreal C++책 참고
			TEXT("StaticMesh'/Engine/EditorMeshes/PhAT_FloorBox.PhAT_FloorBox'")
			);


	//StaticMesh'/Engine/EditorMeshes/PhAT_FloorBox.PhAT_FloorBox'
	FloorMesh = NewObject<UStaticMeshComponent>
		(
			GetTransientPackage(),	//Outer 지정, GetTransientPackage : 임시 저장소라는 뜻, 화면이 떠있는 동안 유지됨
			NAME_None,				//컴포넌트 이름 없음
			RF_Transient			//임시객체로 생성 
			);

	FloorMesh->SetStaticMesh(floormesh);
	FTransform transform;	//Scene 안에서 어디에 띄울지 지정

	Scene->AddComponent(FloorMesh, transform);


	//화면에 출력할 StaticMesh 불러옴 카메라모양
	UStaticMesh* mesh = LoadObject<UStaticMesh>
		(
			nullptr,											//Outer, Unreal C++책 참고
			TEXT("StaticMesh'/Game/MatineeCam_SM.MatineeCam_SM'")
		);
	//칠해줄 마테리얼 로드
	UMaterialInstanceConstant* material = LoadObject<UMaterialInstanceConstant>
		(
			nullptr,											//Outer
			TEXT("MaterialInstanceConstant'/Game/M_StaticMesh_Inst.M_StaticMesh_Inst'")
		);


	//MeshComponent 할당, Game 이외에서는 NewObject로 생성
	Mesh = NewObject<UStaticMeshComponent>
		(
			GetTransientPackage(),	//Outer 지정, GetTransientPackage : 임시 저장소라는 뜻, 화면이 떠있는 동안 유지됨
			NAME_None,				//컴포넌트 이름 없음
			RF_Transient			//임시객체로 생성 
		);
	
	Mesh->SetStaticMesh(mesh);
	Mesh->SetMaterial(0, material);


	transform.SetLocation(FVector(0, 0, 100));

	Scene->AddComponent(Mesh, transform);
}
TSharedRef<class FAdvancedPreviewScene> SMeshObject_Viewport::GetPreviewScene()
{
	return Scene.ToSharedRef();
	//SharedRef 과  Ptr은 1대1 매핑이 가능
}
void SMeshObject_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	//레퍼런스 카운트 등록할 오브젝트들 여기에 설정
	Collector.AddReferencedObject(Mesh);
	Collector.AddReferencedObject(FloorMesh);
	//생성의 역순으로 설정, 잊지말자
}


TSharedRef<FEditorViewportClient> SMeshObject_Viewport::MakeEditorViewportClient()
{
	//실제 어떤내용을 보여줄지를 결정 창이열릴때 자동생성, 닫힐때 자동 소멸
	ViewportClient = MakeShareable(new FPreviewObjectViewport_Client(Scene.Get(), SharedThis(this)));

	//ViewportClient에서 Construct()가 생성되면서 반환
	return ViewportClient.ToSharedRef();
}
