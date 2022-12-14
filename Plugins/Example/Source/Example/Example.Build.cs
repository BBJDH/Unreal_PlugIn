// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Example : ModuleRules
{
	public Example(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.Add(ModuleDirectory);
        //내부적으로 쓴다면 Private public은 전파된다


        PublicDependencyModuleNames.Add("Core");


        PublicDependencyModuleNames.Add("CPP_PlugIn");
        //순환참조에 주의하자!! 게임 플러그인 플러그인 게임

        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");

        //UI를 프로그래밍 할 수 있는 모듈
        PrivateDependencyModuleNames.Add("Slate");
        PrivateDependencyModuleNames.Add("SlateCore");
        PrivateDependencyModuleNames.Add("EditorStyle");
        PrivateDependencyModuleNames.Add("Projects");
        PrivateDependencyModuleNames.Add("GameplayDebugger");
        PrivateDependencyModuleNames.Add("DesktopPlatform");           
        PrivateDependencyModuleNames.Add("MainFrame");          
        PrivateDependencyModuleNames.Add("UnrealEd");   //에디터모듈      
        PrivateDependencyModuleNames.Add("AdvancedPreviewScene");   
        PrivateDependencyModuleNames.Add("InputCore");   
        //링크 에러 2019, 1120이 뜬다면 이곳에 추가
    }
}
