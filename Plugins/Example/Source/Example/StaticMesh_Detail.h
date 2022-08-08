
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

/**
 * 
 */
class EXAMPLE_API FStaticMesh_Detail
	: public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();


public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;


private:
	FReply OnClicked_Paint();
	//Slate ��ư Ŭ���� ������ �Լ�
};