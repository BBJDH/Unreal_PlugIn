
#include "SMeshObject_Viewport.h"
#include "PreviewObjectViewport_Client.h"
#include "AdvancedPreviewScene.h"
#include "Materials/MaterialInstanceConstant.h"


SMeshObject_Viewport::SMeshObject_Viewport()
{
	//���� ���� ������ ������ ������ ��ü, ������ ��ü���� ����
	Scene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
}


//���� UI�� �������� �Լ�
void SMeshObject_Viewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
	//�θ� �Լ� ��


	//Viewport �ȿ����� �̷��� ��ȹ�� �����Ͽ� ��� ����
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
		.ColorAndOpacity(FLinearColor::Blue)	//�Ķ��� TextBlock ����, Viewport��� ���� ��ܿ� ���
		];

	//Scene�� �ٴ� ����� floormesh ����
	UStaticMesh* floormesh = LoadObject<UStaticMesh>
		(
			nullptr,											//Outer, Unreal C++å ����
			TEXT("StaticMesh'/Engine/EditorMeshes/PhAT_FloorBox.PhAT_FloorBox'")
			);


	//StaticMesh'/Engine/EditorMeshes/PhAT_FloorBox.PhAT_FloorBox'
	FloorMesh = NewObject<UStaticMeshComponent>
		(
			GetTransientPackage(),	//Outer ����, GetTransientPackage : �ӽ� ����Ҷ�� ��, ȭ���� ���ִ� ���� ������
			NAME_None,				//������Ʈ �̸� ����
			RF_Transient			//�ӽð�ü�� ���� 
			);

	FloorMesh->SetStaticMesh(floormesh);
	FTransform transform;	//Scene �ȿ��� ��� ����� ����

	Scene->AddComponent(FloorMesh, transform);


	//ȭ�鿡 ����� StaticMesh �ҷ��� ī�޶���
	UStaticMesh* mesh = LoadObject<UStaticMesh>
		(
			nullptr,											//Outer, Unreal C++å ����
			TEXT("StaticMesh'/Game/MatineeCam_SM.MatineeCam_SM'")
		);
	//ĥ���� ���׸��� �ε�
	UMaterialInstanceConstant* material = LoadObject<UMaterialInstanceConstant>
		(
			nullptr,											//Outer
			TEXT("MaterialInstanceConstant'/Game/M_StaticMesh_Inst.M_StaticMesh_Inst'")
		);


	//MeshComponent �Ҵ�, Game �̿ܿ����� NewObject�� ����
	Mesh = NewObject<UStaticMeshComponent>
		(
			GetTransientPackage(),	//Outer ����, GetTransientPackage : �ӽ� ����Ҷ�� ��, ȭ���� ���ִ� ���� ������
			NAME_None,				//������Ʈ �̸� ����
			RF_Transient			//�ӽð�ü�� ���� 
		);
	
	Mesh->SetStaticMesh(mesh);
	Mesh->SetMaterial(0, material);


	transform.SetLocation(FVector(0, 0, 100));

	Scene->AddComponent(Mesh, transform);
}
TSharedRef<class FAdvancedPreviewScene> SMeshObject_Viewport::GetPreviewScene()
{
	return Scene.ToSharedRef();
	//SharedRef ��  Ptr�� 1��1 ������ ����
}
void SMeshObject_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	//���۷��� ī��Ʈ ����� ������Ʈ�� ���⿡ ����
	Collector.AddReferencedObject(Mesh);
	Collector.AddReferencedObject(FloorMesh);
	//������ �������� ����, ��������
}


TSharedRef<FEditorViewportClient> SMeshObject_Viewport::MakeEditorViewportClient()
{
	//���� ������� ���������� ���� â�̿����� �ڵ�����, ������ �ڵ� �Ҹ�
	ViewportClient = MakeShareable(new FPreviewObjectViewport_Client(Scene.Get(), SharedThis(this)));

	//ViewportClient���� Construct()�� �����Ǹ鼭 ��ȯ
	return ViewportClient.ToSharedRef();
}
