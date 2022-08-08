
#include "CDrawVertex.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"

ACDrawVertex::ACDrawVertex()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

	CHelpers::CreateComponent<UProceduralMeshComponent>(this, &Mesh, "Mesh");


	FVector p = FVector(0.5f, 0.5f, 0.5f);


	//그리는 순서 2 1 0,  3 1 2
	//Front
	/*
	1 3
	0 2
	*/

	//front
	Positions.Add(FVector(-p.X, -p.Y, -p.Z)); Uvs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-p.X, -p.Y, +p.Z)); Uvs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-p.X, +p.Y, -p.Z)); Uvs.Add(FVector2D(1, 1));
	Positions.Add(FVector(-p.X, +p.Y, +p.Z)); Uvs.Add(FVector2D(1, 0));


	for (int i = 0; i < 4; i++)
	{
		Normals.Add(FVector(-1, 0, 0));
		Colors.Add(FColor(128, 0, 0, 255));
	}
	AddTriangles(0);



	//Back
	Positions.Add(FVector(+p.X, +p.Y, -p.Z)); Uvs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+p.X, +p.Y, +p.Z)); Uvs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+p.X, -p.Y, -p.Z)); Uvs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+p.X, -p.Y, +p.Z)); Uvs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(+1, 0, 0));
		Colors.Add(FColor(0, 128, 0, 255));
	}
	AddTriangles(4);


	//Top
	Positions.Add(FVector(-p.X, -p.Y, +p.Z)); Uvs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+p.X, -p.Y, +p.Z)); Uvs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-p.X, +p.Y, +p.Z)); Uvs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+p.X, +p.Y, +p.Z)); Uvs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, +1));
		Colors.Add(FColor(0, 0, 128, 255));
	}
	AddTriangles(8);


	//Bottom
	Positions.Add(FVector(-p.X, -p.Y, -p.Z)); Uvs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-p.X, +p.Y, -p.Z)); Uvs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+p.X, -p.Y, -p.Z)); Uvs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+p.X, +p.Y, -p.Z)); Uvs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, -1));
		Colors.Add(FColor(0, 128, 128, 255));
	}
	AddTriangles(12);


	//Left
	Positions.Add(FVector(+p.X, -p.Y, -p.Z)); Uvs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+p.X, -p.Y, +p.Z)); Uvs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-p.X, -p.Y, -p.Z)); Uvs.Add(FVector2D(1, 1));
	Positions.Add(FVector(-p.X, -p.Y, +p.Z)); Uvs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, -1, 0));
		Colors.Add(FColor(128, 0, 128, 255));
	}
	AddTriangles(16);


	//Right
	Positions.Add(FVector(-p.X, +p.Y, -p.Z)); Uvs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-p.X, +p.Y, +p.Z)); Uvs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+p.X, +p.Y, -p.Z)); Uvs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+p.X, +p.Y, +p.Z)); Uvs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, +1, 0));
		Colors.Add(FColor(128, 128, 128, 255));
	}
	AddTriangles(20);


	Mesh->CreateMeshSection(0, Positions, Indices, Normals, Uvs, Colors, TArray<FProcMeshTangent>(), true);
	//LOD 0 번이 가장 정밀한 모델
	Mesh->SetRelativeScale3D(FVector(100));
}

void ACDrawVertex::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACDrawVertex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//한면을 같은 색으로 지정, i번째 면으로 계산
	for (int i = 0; i < Colors.Num() / 4; i++)
	{
		FColor color = FColor::MakeRandomColor();
		color.A = 255;

		Colors[i * 4 + 0] = color;
		Colors[i * 4 + 1] = color;
		Colors[i * 4 + 2] = color;
		Colors[i * 4 + 3] = color;
	}

	Mesh->UpdateMeshSection(0, Positions, Normals, Uvs, Colors, TArray<FProcMeshTangent>());


}

void ACDrawVertex::AddTriangles(int32 InStart)
{
	Indices.Add(InStart + 2);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 0);

	Indices.Add(InStart + 3);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 2);
}
