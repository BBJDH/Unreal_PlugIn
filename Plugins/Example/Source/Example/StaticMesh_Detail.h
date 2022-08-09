
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

/**
저장하기 위한 구조체 
 */
struct FStaticMesh_DetailData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FVector2D> Uvs;
	TArray<FColor> Colors;
	TArray<int32> Indices;

	friend FArchive& operator<<(FArchive & InArchive, FStaticMesh_DetailData& InData)
	{
		return InArchive
			<< InData.Positions
			<< InData.Normals
			<< InData.Uvs
			<< InData.Colors
			<< InData.Indices;
	}
	//friend를 맺어서 외부에서 접근제한 상관없이 사용가능하게 함
	//<< 파일스트림 기호 오버로딩
};

/*
언리얼 에서는 입출력 모두 << 로 오버로딩 되어있다
*/

class EXAMPLE_API FStaticMesh_Detail
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();


private:
	TArray<TWeakObjectPtr<UObject>> Objects;
	//가비지 컬렉터에 의해 처리되지 않음
	//WeakObj, Weak 모두 댕글링 포인터를 허용

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;


private:
	FReply OnClicked_Paint();
	FReply OnClicked_SaveMesh();
	//Slate OnClicked의 델리게이트를 확인해보면
	//해당 델리게이트는 FReply를 반환함을 알 수있다
	//Slate 버튼 클릭시 동작할 함수
};
