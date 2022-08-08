
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
	//직접 에디터에서 메터리얼을 할당하기에 다이나믹이 아니어도 됨

public:	
	ACStaticMesh();


/*
에디터일때만 실행되는 함수 정의
WITH_EDITOR : 이미 정의된 매크로
*/
#if WITH_EDITOR
	void Paint();
#endif


protected:
	virtual void BeginPlay() override;

};
