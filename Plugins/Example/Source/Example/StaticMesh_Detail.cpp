

#include "StaticMesh_Detail.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "IDesktopPlatform.h"
#include "Interfaces/IMainFrameModule.h"	//�𸮾� ���������� ������
#include "DesktopPlatformModule.h"			//������ �ڵ� ����, ��������
#include "Serialization/BufferArchive.h"	

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
	TArray<FString> fileNames;
	platform->SaveFileDialog
	(
		handle,								//��Ŀ���� ����� �ڵ� ���(modaless?)
		"Save Dialog",						//����� â ����
		path,								//�ҷ����� ���
		"",									//�⺻ ���� �̸�
		"Mesh Binary File(*.bin)|*.bin",	//(Ȯ���� ����) |������ ���͸��� Ȯ���ڵ� ǥ��
		EFileDialogFlags::None,				//������ ��������
		fileNames							//������ ���ϸ��
	);
	if (fileNames.Num() < 1) return FReply::Handled();//�ش� â�� �������� ����


	//GLog->Log(path);
	//���� �ͳθ� ����



	//������ �ϳ��� ���� ����
	FStaticMesh_DetailData data;
	TArray<FColor> colors;
	colorVB.GetVertexColors(colors);

	if (colors.Num() < 1)	//�ش� ������ �÷��� �������� �ʴ´ٸ� ���� ����ŭ �÷��� �Ҵ�
	{
		for (uint32 i = 0; i < vertexCount; i++)
			colors.Add(FColor(0, 0, 0));
	}

	for (uint32 i = 0; i < vertexCount; i++)
	{
		data.Positions.Add(vb.VertexPosition(i));
		data.Normals.Add(meshVB.VertexTangentZ(i));	// ����߰�, Z�� ��� X�� ź��Ʈ����
		data.Uvs.Add(meshVB.GetVertexUV(i, 0));
		data.Colors.Add(colors[i]);

	}

	TArray<uint32> indices;
	ib.GetCopy(indices);
	data.Indices.Insert((int32*)indices.GetData(), indexCount,0);


	FBufferArchive buffer;
	buffer << data;				//������ �����ε��� �Լ� ȣ��

	FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);
	//������ �ٷ�� �Լ����� ����, 

	//ĳ�÷� �� �о ���� �׻� ���۴� ����ش�
	//���Ͻ�Ʈ���� �׿��ִ� �����Ͱ� ������ ���� �����Ƿ� ������ ������
	buffer.FlushCache();	
	buffer.Empty();


	//FString str;
	//str.Append(FPaths::GetCleanFilename(fileNames[0]));
	//str.Append(" File Saved.");
	//GLog->Log(*str);


	//FString text;
	//for (int32 i = 0; i < data.Positions.Num(); i++)
	//{
	//	text.Append(data.Positions[i].ToString() + ", ");
	//	text.Append(data.Normals[i].ToString() + ", ");
	//	text.Append(data.Uvs[i].ToString() + ", ");
	//	text.Append(data.Colors[i].ToString() + "\r\n");
	//}

	//FString txtFileName = FPaths::GetBaseFilename(fileNames[0], false);
	//FString txtSaveName = txtFileName + ".csv";

	//FFileHelper::SaveStringToFile(text, *txtSaveName);


	//str = "";
	//str.Append(FPaths::GetCleanFilename(txtSaveName));
	//str.Append(" File Saved.");
	//GLog->Log(*str);


	return FReply::Handled();
}