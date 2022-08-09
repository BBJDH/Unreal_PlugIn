
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

/**
�����ϱ� ���� ����ü 
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
	//friend�� �ξ �ܺο��� �������� ������� ��밡���ϰ� ��
	//<< ���Ͻ�Ʈ�� ��ȣ �����ε�
};

/*
�𸮾� ������ ����� ��� << �� �����ε� �Ǿ��ִ�
*/

class EXAMPLE_API FStaticMesh_Detail
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();


private:
	TArray<TWeakObjectPtr<UObject>> Objects;
	//������ �÷��Ϳ� ���� ó������ ����
	//WeakObj, Weak ��� ��۸� �����͸� ���

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;


private:
	FReply OnClicked_Paint();
	FReply OnClicked_SaveMesh();
	//Slate OnClicked�� ��������Ʈ�� Ȯ���غ���
	//�ش� ��������Ʈ�� FReply�� ��ȯ���� �� ���ִ�
	//Slate ��ư Ŭ���� ������ �Լ�
};
