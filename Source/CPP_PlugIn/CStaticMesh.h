
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMesh.generated.h"

UCLASS()
class CPP_PLUGIN_API ACStaticMesh : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	class UMaterialInstanceConstant* Material;
	//���� �����Ϳ��� ���͸����� �Ҵ��ϱ⿡ ���̳����� �ƴϾ ��

public:	
	ACStaticMesh();


/*
�������϶��� ����Ǵ� �Լ� ����
WITH_EDITOR : �̹� ���ǵ� ��ũ��
*/
#if WITH_EDITOR
	void Paint();
#endif


protected:
	virtual void BeginPlay() override;

};
