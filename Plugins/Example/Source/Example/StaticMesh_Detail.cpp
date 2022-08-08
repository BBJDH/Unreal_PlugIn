

#include "StaticMesh_Detail.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> FStaticMesh_Detail::MakeInstance()
{
	return MakeShareable(new FStaticMesh_Detail());
	//기본 생성자로 ShareRef 반환
}

void FStaticMesh_Detail::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//GLog->Log(TEXT("Open Detail Tab"));
	//클릭시 디테일 창 띄워짐

	IDetailCategoryBuilder & mesh = DetailBuilder.EditCategory("Mesh");
	//Mesh라는 카테고리가 있다면 그것을 리턴 없으면 만들어서 리턴
	// => Mesh라고하는 카테고리 지역이 생성, 혹은 있는곳으로부터 편집

	//UI출력은 전부 Text로 
	mesh.AddCustomRow(FText::FromString("Color"))	//Color로 디테일 검색되도록 지정
	.NameContent()	//이름 영역이 자료형은 배열로 취급됨 
	[
		SNew(STextBlock)		//Slate 동적할당
		.Text(FText::FromString("Color"))	//제목 지정
	]
	.ValueContent()	//값 영역 (제목 오른쪽)
	.VAlign(VAlign_Center)	//수직정렬
	.MaxDesiredWidth(250)	//최대 넓이 250
	[
		SNew(SButton)	//버튼 동적할당
		.VAlign(VAlign_Center)	//수직정렬은 가운데정렬로
		.HAlign(HAlign_Fill)	//가로정렬은 꽉차게
		.OnClicked(this, &FStaticMesh_Detail::OnClicked_Paint)	//버튼을 눌렀을때의 이벤트
		.Content()	//이 해당 지역의 내용물을 설정
		[
			SNew(STextBlock)	//텍스트 블록 설정
			.Text(FText::FromString("Paint"))	//
		]
	];
}

FReply FStaticMesh_Detail::OnClicked_Paint()
{
	GLog->Log(TEXT("Paint"));
	return FReply::Handled();
	//이거 차이는 다음시간에..
}