

#include "CStaticMesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
/*
게임에서 마테리얼을 바꾼다면 다이나믹 
에디터에서 마테리얼을 만든다면 InstanceConstants
인스턴스는 서로간에 값을 공유한 상태?
*/
ACStaticMesh::ACStaticMesh()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	//StaticMesh'/Game/MatineeCam_SM1.MatineeCam_SM1'

	UStaticMesh * mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/MatineeCam_SM.MatineeCam_SM'");
	Mesh->SetStaticMesh(mesh);

	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/M_StaticMesh_Inst.M_StaticMesh_Inst'");
	Mesh->SetMaterial(0, Material);
}

void ACStaticMesh::BeginPlay()
{
	Super::BeginPlay();
}

/*
에디터일때만 실행되는 함수 정의
WITH_EDITOR : 이미 정의된 매크로
*/
#if WITH_EDITOR

void ACStaticMesh::Paint()
{
	/*
	SIMD : 16 바이트(4*4,Vector4) 전송방식을 채택
	XYZW W가 0이면 방향, 1이면 위치 이동행렬이 곱해지는가 고민해보자
	
	*/
	for (FVectorParameterValue& value : Material->VectorParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("Color") == 0) //우리가 마테리얼 블프에서 지정했던 변수명(Color)와 일치한다면 0
			Material->SetVectorParameterValueEditorOnly
			(
				value.ParameterInfo,
				FLinearColor::MakeRandomColor()
			);
	}
}
#endif
