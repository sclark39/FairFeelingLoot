// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LootTableBlueprintLibrary.h"

float ULootTableBlueprintLibrary::GetLootStat(const FLootRecipe &Loot, FGameplayTag StatType, float DefaultValue)
{
	const int32* lookup = Loot.StatLookup.Find(StatType);
	if (lookup)
		return Loot.Stats[*lookup].StatValue;

	return DefaultValue;
}


void ULootTableBlueprintLibrary::SetLootStat(FLootRecipe &Loot, FGameplayTag StatType, float StatValue)
{
	const int* lookup = Loot.StatLookup.Find(StatType);
	if (!lookup)
	{
		lookup = &Loot.StatLookup.Add(StatType, Loot.Stats.Num());
		Loot.Stats.Push({ StatType, StatValue });
	}
	else
	{
		Loot.Stats[*lookup].StatValue = StatValue;
	}
}

void ULootTableBlueprintLibrary::RemoveLootStat(FLootRecipe &Loot, FGameplayTag StatType)
{
	const int* lookup = Loot.StatLookup.Find(StatType);
	if (lookup)
	{
		Loot.Stats.RemoveAt(*lookup);

		// Rebuild lookup array
		Loot.StatLookup.Empty();
		for (int i = 0; i < Loot.Stats.Num(); i++)
		{
			Loot.StatLookup.Add(Loot.Stats[i].StatType, i);
		}
	}
}

/*



// Algorithm Source: Leva, J. L. 1992. A fast normal random number generator.
float LevaRatioOfUniformsGaussian(const FRandomStream &RNG)
{
	// Constants
	const static float VMAX = FMath::Sqrt(2.0f / EULERS_NUMBER);
	const float s = 0.449871;
	const float t = -0.386595;
	const float a = 0.19600;
	const float b = 0.25472;
	const float r1 = 0.27597;
	const float r2 = 0.27846;

	// Find a point inside the valid region
	for (int i = 0; i < 10; i++)
	{
		const float u = RNG.FRand();
		const float v = (RNG.FRand() - 0.5f) * 2.0f * VMAX;

		// No division by zero!
		if (u < SMALL_NUMBER)
			continue;

		const float x = u - s;
		const float y = FMath::Abs(v) - t;
		const float Q = x * x + y * (a * y - b * x);

		// If not inside inner boundary, need to test
		if (r1 <= Q)
		{
			// If outside outer boundary, reject
			if (r2 < Q)
				continue;
			// If outside acceptance region, reject
			else if (-4.0f * (u*u) * FMath::Log2(u) < (v*v))
				continue;
		}

		UE_LOG(LogTemp, Log, TEXT("Leva Gaussian number found in %d cycles"), i);
		return (v / u);
	}

	UE_LOG(LogTemp, Error, TEXT("Leva Gaussian number failed to generate in 10 cycles"));
	return 0;
}


float MarsagliaGaussian(const FRandomStream &RNG)
{
	float v1, v2, s;
	do {
		v1 = RNG.FRandRange(-1.0f, 1.0f);
		v2 = RNG.FRandRange(-1.0f, 1.0f);
		s = v1 * v1 + v2 * v2;
	} while (s >= 1.0f || s == 0.0f);

	s = FMath::Sqrt(-2.0f * FMath::Log2(s)) / s;
	return v1 * s;
}


float ULootTableBlueprintLibrary::NextGaussian(const FRandomStream &RNG, float Min, float Max, float Sigma)
{
	const float Mean = (Max + Min) / 2.0f;
	const float StdDev = (Max - Min) / 2.0f / FMath::Max(1.0f, Sigma);

	for (int i = 0; i < 100; i++)
	{
		const float r = Mean + LevaRatioOfUniformsGaussian(RNG) * StdDev;
		if (Min <= r && r <= Max)
		{
			UE_LOG(LogTemp, Log, TEXT("Gaussian number in range found in %d cycles"), i);
			return r;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Gaussian number failed to generate in 100 cycles"))
		return 0;

}
*/