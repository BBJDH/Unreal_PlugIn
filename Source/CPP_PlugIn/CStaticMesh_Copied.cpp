

#include "CStaticMesh_Copied.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
ACStaticMesh_Copied::ACStaticMesh_Copied()
{
	bRunConstructionScriptOnDrag = false;
	//마우스 드래그중에 컨스트럭션 스크립트 콜을 할지 말지 설정
	//켜두면 계속 우리가 만듬 함수가 호출되어 렌더링에 들어가므로 false로 설정

	CHelpers::CreateComponent(this, &Mesh, "Mesh");

	//경로의 마테리얼로 메쉬의 마테리얼을 지정
	//MaterialInstanceConstant'/Game/M_StaticMesh_Inst.M_StaticMesh_Inst'
	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/M_StaticMesh_Inst.M_StaticMesh_Inst'");
	Mesh->SetMaterial(0, Material);

}

void ACStaticMesh_Copied::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACStaticMesh_Copied::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Mesh->CreateMeshSection
	(
		0,
		Positions, 
		Indices, 
		Normals, 
		Uvs, 
		Colors, 
		TArray<FProcMeshTangent>(), 
		true
	);


}

