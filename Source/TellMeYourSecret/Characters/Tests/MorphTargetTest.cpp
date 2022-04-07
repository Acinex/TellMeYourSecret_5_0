#include "CoreTypes.h"
#include "TellMeYourSecret/Characters/Util/MorphTargetChange.h"

IMPLEMENT_COMPLEX_AUTOMATION_TEST(FMorphTargetTest, "TMYS.Character.Animation.MorphTargets", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

void FMorphTargetTest::GetTests(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const
{
	OutBeautifiedNames.Add(TEXT("Equal is correct"));
	OutBeautifiedNames.Add(TEXT("equal"));

	OutBeautifiedNames.Add(TEXT("CurrentValue is calculated correctly"));
	OutBeautifiedNames.Add(TEXT("currentvalue"));

	OutBeautifiedNames.Add(TEXT("Rate is calculated correctly"));
	OutBeautifiedNames.Add(TEXT("rate"));
}

bool FMorphTargetTest::RunTest(const FString& Parameters)
{
	FMorphTargetChange Change = {
		TEXT("A"),
		1,
		1
	};

	if (Parameters.Equals(TEXT("equal")))
	{
		const FMorphTargetChange ChangeB = {
			TEXT("B"),
			1,
			1
		};

		if (Change == ChangeB)
		{
			AddError(TEXT("FMorphTargetChange identifier should be the name, so they should not be equal here"));
		}
	}

	FMorphTargetExecution Execution(Change);
	if (Parameters.Equals("rate"))
	{
		TestEqual("GetRate", Execution.GetRate(), 1 / 30.0F);
		Change.Time = 0.5;
		TestEqual("GetRate", Execution.GetRate(), 0.5F / 30.0F);
	}

	if (Parameters.Equals("currentvalue"))
	{
		Execution.Step();
		TestEqual("CurrentValue", Execution.GetCurrentValue(), 0.033F, 0.01F);
		Execution.Step();
		TestEqual("CurrentValue", Execution.GetCurrentValue(), 0.066F, 0.01F);
		Execution.Step();
		TestEqual("CurrentValue", Execution.GetCurrentValue(), 0.099F, 0.01F);

		Change.Time = 0.5;
		Execution.Step();
		TestEqual("CurrentValue", Execution.GetCurrentValue(), 0.033F, 0.001F);
		Execution.Step();
		TestEqual("CurrentValue", Execution.GetCurrentValue(), 0.066F, 0.001F);
		Execution.Step();
		TestEqual("CurrentValue", Execution.GetCurrentValue(), 0.099F, 0.001F);
	}

	return true;
}
