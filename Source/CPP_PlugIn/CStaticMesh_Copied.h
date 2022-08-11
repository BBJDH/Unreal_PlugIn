// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMesh_Copied.generated.h"

UCLASS()
class CPP_PLUGIN_API ACStaticMesh_Copied : public AActor
{
	GENERATED_BODY()
	

	private:
	UPROPERTY(VisibleDefaultsOnly)
	class UProceduralMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	class UMaterialInstanceConstant* Material;

public:
	//�ܺο��� ������ �������� �Լ���
	FORCEINLINE void SetPositions(TArray<FVector> InPositions) { Positions = InPositions; }
	FORCEINLINE void SetIndices(TArray<int32> InIndices) { Indices = InIndices; }
	FORCEINLINE void SetNormals(TArray<FVector> InNormals) { Normals = InNormals; }
	FORCEINLINE void SetUvs(TArray<FVector2D> InUvs) { Uvs = InUvs; }
	FORCEINLINE void SetColors(TArray<FColor> InColors) { Colors = InColors; }

public:
	ACStaticMesh_Copied();

	//OnConstruction ��ũ��Ʈ�� ����, BP���� �θ��Լ� ���� �ɾ��ָ�
	//���� ���ǵ� �Լ����� �����ϰ� BP���� �����Ѵ�
	virtual void OnConstruction(const FTransform& Transform) override;
	//SpawnActor�� SpawnActorDeffered ����
	//SpawnActorDeffered��   FinishSpawningActor�� ������ �߰��ȴ� �̺κп��� 
	//OnConstruction������ �� ������ ����
	//������ �����ֱ� ���� Ȯ���� ��

protected:
	virtual void BeginPlay() override;

private:
	//������ ������
	TArray<FVector> Positions;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FVector2D> Uvs;
	TArray<FColor> Colors;

};
