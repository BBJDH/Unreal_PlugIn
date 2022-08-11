

#include "StaticMesh_Detail.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#include "IDesktopPlatform.h"
#include "Interfaces/IMainFrameModule.h"	//�𸮾� ���������� ������
#include "DesktopPlatformModule.h"			//������ �ڵ� ����, ��������
#include "Serialization/BufferArchive.h"	
#include "Misc/FileHelper.h"


#include "CStaticMesh.h"
#include "Components/StaticMeshComponent.h"

TSharedRef<IDetailCustomization> FStaticMesh_Detail::MakeInstance()
{
	return MakeShareable(new FStaticMesh_Detail());
	//�⺻ �����ڷ� ShareRef ��ȯ
}

void FStaticMesh_Detail::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//GLog->Log(TEXT("Open Detail Tab"));
	//Ŭ���� ������ â �����

	IDetailCategoryBuilder & mesh = DetailBuilder.EditCategory("Mesh");
	//Mesh��� ī�װ��� �ִٸ� �װ��� ���� ������ ���� ����
	// => Mesh����ϴ� ī�װ� ������ ����, Ȥ�� �ִ°����κ��� ����

	//UI����� ���� Text�� 
	mesh.AddCustomRow(FText::FromString("Color"))	//Color�� ������ �˻��ǵ��� ����
	.NameContent()	//�̸� ������ �ڷ����� �迭�� ��޵� 
	[
		SNew(STextBlock)		//Slate �����Ҵ�
		.Text(FText::FromString("Color"))	//���� ����
	]
	.ValueContent()	//�� ���� (���� ������)
	.VAlign(VAlign_Center)	//��������
	.MaxDesiredWidth(250)	//�ִ� ���� 250
	[
		SNew(SButton)	//��ư �����Ҵ�
		.VAlign(VAlign_Center)	//���������� ������ķ�
		.HAlign(HAlign_Fill)	//���������� ������
		.OnClicked(this, &FStaticMesh_Detail::OnClicked_Paint)	//��ư�� ���������� �̺�Ʈ
		.Content()	//�� �ش� ������ ���빰�� ����
		[
			SNew(STextBlock)	//�ؽ�Ʈ ��� ����
			.Text(FText::FromString("Paint"))	//
		]
	];


	//�����Ϸ��̾ƿ� �߰�
	mesh.AddCustomRow(FText::FromString("SaveMesh"))	//Color�� ������ �˻��ǵ��� ����(�ĺ���)
		.NameContent()	//�̸� ������ �ڷ����� �迭�� ��޵� 
		[
			SNew(STextBlock)		//Slate �����Ҵ�
			.Text(FText::FromString("Save"))	//���� ����
		]
	.ValueContent()	//�� ���� (���� ������)
		.VAlign(VAlign_Center)	//��������
		.MaxDesiredWidth(250)	//�ִ� ���� 250
		[
			SNew(SButton)	//��ư �����Ҵ�
			.VAlign(VAlign_Center)	//���������� ������ķ�
		.HAlign(HAlign_Fill)	//���������� ������
		.OnClicked(this, &FStaticMesh_Detail::OnClicked_SaveMesh)	//��ư�� ���������� �̺�Ʈ
		.Content()	//�� �ش� ������ ���빰�� ����
		[
			SNew(STextBlock)	//�ؽ�Ʈ ��� ����
			.Text(FText::FromString("Save!"))	//
		]
		];

	DetailBuilder.GetObjectsBeingCustomized(Objects);
	//������ ������Ʈ���� Objects�� �޾ƿ�
}

FReply FStaticMesh_Detail::OnClicked_Paint()
{
	//GLog->Log(TEXT("Paint"));

	//���õ� ��� ������Ʈ �̸����� ���
	//for (TWeakObjectPtr<UObject> obj : Objects)
	//	GLog->Log(*obj->GetName());

	//���õ� ������Ʈ�� �� ù��°�� ACStaticMesh�� ĳ����
	ACStaticMesh* mesh = Cast<ACStaticMesh>(Objects[0]);

	//�����ߴٸ� Paint() ȣ��
	if (!!mesh)
		mesh->Paint();
	//���׸����� �����÷��� ĥ�ϴ� �Լ�

	return FReply::Handled();
	//���� slate�� ó���� �ñ��� �ʰ� ���⼭ ����
	//Unhandled ���� �������� ó���� �ѱ�
}

FReply FStaticMesh_Detail::OnClicked_SaveMesh()
{
	ACStaticMesh* meshActor = Cast<ACStaticMesh>(Objects[0]);
	//������ ù��° ����
	if (meshActor == nullptr) return FReply::Handled();

	/*
	������ �ڷ����� ACStaticMesh���� Ȯ�εǾ���
	���� ������ ��������
	������ ������ �ҷ���������
	Static Mesh�� ĳ����
	*/
	UActorComponent * actorComponent = meshActor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	//�������� ActorComponent �̴�
	//�ٽ� ĳ�������ش�
	UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(actorComponent);

	if(meshComponent == nullptr) 	return FReply::Unhandled();	// �������� ó���� �� �ְ� �н�!

	UStaticMesh* mesh = meshComponent->GetStaticMesh();		//���⿡ ���� ������ �ִ�!
	FStaticMeshRenderData * renderData =  mesh->RenderData.Get(); //RenderData�� UniquePtr�̴�

	if(renderData->LODResources.Num()<1) return FReply::Unhandled();
	//������ ������ ���ٴ°��� �ǹ� LOD �迭�� ����ִٴ°��� �Ǵ� �� ��

	//������ ������ ��ȿ �ϴٸ� ���� ������ 0�� LOD ������ ����

	FStaticMeshLODResources& lod = renderData->LODResources[0];
	FPositionVertexBuffer& vb = lod.VertexBuffers.PositionVertexBuffer;
	//�� �������� ��ġ, �÷�����, ���
	FStaticMeshVertexBuffer& meshVB = lod.VertexBuffers.StaticMeshVertexBuffer;
	//��ֺ���, UV, ź��Ʈ����(��ָ�)

	FColorVertexBuffer& colorVB = lod.VertexBuffers.ColorVertexBuffer;
	FRawStaticIndexBuffer& ib = lod.IndexBuffer;

	if (vb.GetNumVertices() < 1) return FReply::Unhandled();
	if (ib.GetNumIndices() < 1) return FReply::Unhandled();
	//���� �迭�̳� �ε��� �迭�� 1���� ������ �׸� ������ ���ٴ� �ǹ̷� �ؼ�

	uint32 vertexCount = vb.GetNumVertices();	//���� ����
	int32 indexCount = ib.GetNumIndices();		//�ε��� �� /3 �ϸ� ������ ��

	GLog->Logf(TEXT("Vertex Count : %d"), vertexCount);
	GLog->Logf(TEXT("Index Count : %d"), indexCount);


	FString path;
	FPaths::GetPath(path);	//���� ���� ��θ� ������


	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	//MainFrame -> ������ â ��ü(�𸮾��� ����)

	void* handle =  mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	/*
	 mainFrame.GetParentWindow() ���� ������ ȭ��
	 >GetNativeWindow()->GetOSWindowHandle() ���� �ڵ��� ������
	//�ڵ��̶�? �����쿡�� �� ���α׷��� ���� �ּ����� �����쿡�� ���α׷��� �ĺ��ϴ� ID
	WHAND�� void*
	*/


	IDesktopPlatform * platform = FDesktopPlatformModule::Get();
	//���� ����(�г�)������
	/*
	������ ���� ������Ʈ
	�̿� ��ũ����
	���� ������ ���� �ĺ��� �ĺ� ����
	�𸮾� ���� ��
	������ ���������� �˻�
	*/
	TArray<FString> fileNames;

	//������������ ���� ���̾�α� ����
	platform->SaveFileDialog
	(
		handle,								//��Ŀ���� ����� �ڵ� ���(modaless?)
		"Save Dialog",						//����� â ����
		path,								//�ҷ����� ���
		"FileName",							//�⺻ ���� �̸�
		"Mesh Binary File(*.bin)|*.bin",	//(Ȯ���� ����) |������ ���͸��� Ȯ���ڵ� ǥ��
		EFileDialogFlags::None,				//������ ��������(���̾�α� ������ ���ÿ� �����ϴ� ������)
		fileNames							//������ ���ϸ��(TArray<FString> ���� ����)
	);
	//���ϵ� ���ڿ�?
	if (fileNames.Num() < 1) return FReply::Unhandled();//���� �гη� ����
	//���ڵ� ���� �ڵ� ����


	//GLog->Log(path);
	//���� �ͳθ� ����



	//������ �ϳ��� ���� ����
	FStaticMesh_DetailData data;
	TArray<FColor> colors;
	colorVB.GetVertexColors(colors);
	//�÷��� ���� ���ְ� ���ؽ� ����ŭ ���� ��ȿ�ϵ��� �Ҵ�
	//for������ ���� �ֱ� ����

	if (colors.Num() < 1)	//�ش� ������ �÷��� �������� �ʴ´ٸ� ���� ����ŭ �÷��� �Ҵ�
	{
		for (uint32 i = 0; i < vertexCount; i++)
			colors.Add(FColor(0, 0, 0, 255));
	}


	/*
	���Ǹ� ���ϱ� ���� ����
	*/
	FVector minBounds = FVector(MAX_FLT, MAX_FLT, MAX_FLT);
	FVector maxBounds = FVector(-MAX_FLT, -MAX_FLT, -MAX_FLT);

	for (uint32 i = 0; i < vertexCount; i++)
	{

		FVector position = vb.VertexPosition(i);

		//������ �ּҰ� ������Ʈ
		if (position.X < minBounds.X)	minBounds.X = position.X;
		if (position.Y < minBounds.Y)	minBounds.Y = position.Y;
		if (position.Z < minBounds.Z)	minBounds.Z = position.Z;

		//������ �ִ밪 ������Ʈ
		if (position.X > maxBounds.X)	maxBounds.X = position.X;
		if (position.Y > maxBounds.Y)	maxBounds.Y = position.Y;
		if (position.Z > maxBounds.Z)	maxBounds.Z = position.Z;

		data.Positions.Add(vb.VertexPosition(i));	//���ؽ� ��ȣ�� �ִ� ���ؽ� ������
		data.Normals.Add(meshVB.VertexTangentZ(i));	// ����߰�, Z�� ��� X�� ź��Ʈ����, y�� ����ź��Ʈ
		data.Uvs.Add(meshVB.GetVertexUV(i, 0));
		data.Colors.Add(colors[i]);

	}

	//������ ������ �� ������ �Ÿ��� ���, ���Ƿ� ����
	float x = FMath::Abs(minBounds.X - maxBounds.X);
	float y = FMath::Abs(minBounds.Y - maxBounds.Y);
	float z = FMath::Abs(minBounds.Z - maxBounds.Z);

	//���� �Է�
	data.Extent = FVector(x, y, z);

	//�� ���߿� ���� ū �������� Radius�� ����
	data.Radius = FMath::Max(x, y);
	data.Radius = FMath::Max(data.Radius, z);

	GLog->Logf(TEXT("x : %0.1f, y : %0.1f, z : %0.1f"), x, y, z);
	GLog->Logf(TEXT("Radius : %f"), data.Radius);


	//�ε��� �������� 
	TArray<uint32> indices;
	//��ȯ TArray<uint32>
	ib.GetCopy(indices);
	//�����ͷ� �ε��� ����, ���, 0������
	//Add�Լ��� ��� �����ͷ� �ִ� Insert ���
	data.Indices.Insert((int32*)indices.GetData(), indexCount,0);


	FBufferArchive buffer;		//FArchive�κ��� ��ӹ޾����Ƿ� <<������ �����ε� ��ȿ
	buffer << data;				//������ �����ε��� �Լ� ȣ��

	//.Bin ���Ϸ� ���� �Լ�
	FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);
	/*
	SaveString - �ؽ�Ʈ�� ����
	ArrayFile - ���̳ʸ��� ����
	*/
	//������ �ٷ�� �Լ����� ����,  

	//ĳ�÷� �� �о ���� �׻� ���۴� ����ش�
	//���Ͻ�Ʈ���� �׿��ִ� �����Ͱ� ������ ���� �����Ƿ� ������ ������
	buffer.FlushCache();	//ĳ�ÿ� �ִ� �����͸� �� ��Ʈ������ �δ�(���ϳ�������)
	buffer.Empty();			//��Ʈ�� Ŭ����




	/*
	�̹��� ���ڿ��� �����ϴ� ���� ����
	
	*/
	FString str;
	
	str.Append(FPaths::GetCleanFilename(fileNames[0])); // �ش��ο��� �� �ǳ� ���ϸ� ����
	str.Append(" File Saved.");
	GLog->Log(*str);

	//�ؽ�Ʈ ���Ϸ� ���� ����
	FString text;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		text.Append(data.Positions[i].ToString() + ", ");
		text.Append(data.Normals[i].ToString() + ", ");
		text.Append(data.Uvs[i].ToString() + ", ");
		text.Append(data.Colors[i].ToString() + "\r\n");
	}

	FString txtFileName = FPaths::GetBaseFilename(fileNames[0], false); //�� �ڿ� Ȯ���ڸ� �����ϰ� ������
	FString txtSaveName = txtFileName + ".csv";							//Ȯ���ڸ� ���Ƿ�.csv�� �ٲ�
	//.csv�� ���� ���� �Ǵ� �ؽ�Ʈ ����

	//�ؽ�Ʈ�� ����
	FFileHelper::SaveStringToFile(text, *txtSaveName);// txtSaveName - ������ ���� ��

	str = "";
	str.Append(FPaths::GetCleanFilename(txtSaveName));
	str.Append(" File Saved.");
	GLog->Log(*str);


	return FReply::Handled();
}