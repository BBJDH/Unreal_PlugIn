
using UnrealBuildTool;

public class CPP_PlugIn : ModuleRules
{
	public CPP_PlugIn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);
        //���Ե��丮 �߰�

        //UMG �� ��� ���Ӽ� ����
        PublicDependencyModuleNames.Add("Core");
        PublicDependencyModuleNames.Add("CoreUObject");
        PublicDependencyModuleNames.Add("Engine");
        PublicDependencyModuleNames.Add("InputCore");
        PublicDependencyModuleNames.Add("AIModule");

	}
}
