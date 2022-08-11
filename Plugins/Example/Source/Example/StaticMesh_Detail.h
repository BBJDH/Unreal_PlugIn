
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

/**
저장하기 위한 구조체
직렬화는 하지 않을 예정
하지만 바이트 스트림에 전송 가능하도록
 */
struct FStaticMesh_DetailData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FVector2D> Uvs;
	TArray<FColor> Colors;
	TArray<int32> Indices;

	//부피값 저장
	FVector Extent;
	//최대반경 저장
	float Radius;


	friend FArchive& operator<<(FArchive & InArchive, FStaticMesh_DetailData& InData)
	{
		return InArchive				//받은 아카이브
			<< InData.Positions			//계속해서
			<< InData.Normals			//바이트를
			<< InData.Uvs				//전송
			<< InData.Colors			//오버로딩
			<< InData.Indices			//되어 있음
			<< InData.Extent
			<< InData.Radius;
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
