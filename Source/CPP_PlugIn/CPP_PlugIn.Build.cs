
using UnrealBuildTool;

public class CPP_PlugIn : ModuleRules
{
	public CPP_PlugIn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);
        //포함디렉토리 추가

        //UMG 용 모듈 종속성 구성
        PublicDependencyModuleNames.Add("Core");
        PublicDependencyModuleNames.Add("CoreUObject");
        PublicDependencyModuleNames.Add("Engine");
        PublicDependencyModuleNames.Add("InputCore");
        PublicDependencyModuleNames.Add("AIModule");

	}
}
