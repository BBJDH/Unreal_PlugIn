// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Example : ModuleRules
{
	public Example(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.Add(ModuleDirectory);
        //���������� ���ٸ� Private public�� ���ĵȴ�


        PublicDependencyModuleNames.Add("Core");
        PublicDependencyModuleNames.Add("CPP_PlugIn");
        //��ȯ������ ��������!! ���� �÷����� �÷����� ����

        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");

        //UI�� ���α׷��� �� �� �ִ� ���
        PrivateDependencyModuleNames.Add("Slate");
        PrivateDependencyModuleNames.Add("SlateCore");
        PrivateDependencyModuleNames.Add("EditorStyle");
        PrivateDependencyModuleNames.Add("Projects");
        PrivateDependencyModuleNames.Add("GameplayDebugger");
        //��ũ ���� 2019, 1120�� ��ٸ� �̰��� �߰�
    }
}
