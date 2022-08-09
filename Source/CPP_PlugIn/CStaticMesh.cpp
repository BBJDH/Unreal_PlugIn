

#include "CStaticMesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
/*
���ӿ��� ���׸����� �ٲ۴ٸ� ���̳��� 
�����Ϳ��� ���׸����� ����ٸ� InstanceConstants
�ν��Ͻ��� ���ΰ��� ���� ������ ����?
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
�������϶��� ����Ǵ� �Լ� ����
WITH_EDITOR : �̹� ���ǵ� ��ũ��
*/
#if WITH_EDITOR

void ACStaticMesh::Paint()
{
	/*
	SIMD : 16 ����Ʈ(4*4,Vector4) ���۹���� ä��
	XYZW W�� 0�̸� ����, 1�̸� ��ġ �̵������ �������°� ����غ���
	
	*/
	for (FVectorParameterValue& value : Material->VectorParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("Color") == 0) //�츮�� ���׸��� �������� �����ߴ� ������(Color)�� ��ġ�Ѵٸ� 0
			Material->SetVectorParameterValueEditorOnly
			(
				value.ParameterInfo,
				FLinearColor::MakeRandomColor()
			);
	}
}
#endif
