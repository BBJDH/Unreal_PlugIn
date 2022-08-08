

#include "StaticMesh_Detail.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

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
}

FReply FStaticMesh_Detail::OnClicked_Paint()
{
	GLog->Log(TEXT("Paint"));
	return FReply::Handled();
	//�̰� ���̴� �����ð���..
}