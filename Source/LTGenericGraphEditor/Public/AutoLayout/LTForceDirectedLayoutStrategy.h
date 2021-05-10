#pragma once

#include "CoreMinimal.h"
#include "LTAutoLayoutStrategy.h"
#include "LTForceDirectedLayoutStrategy.generated.h"

UCLASS()
class LTGENERICGRAPHEDITOR_API ULTForceDirectedLayoutStrategy : public ULTAutoLayoutStrategy
{
	GENERATED_BODY()
public:
	ULTForceDirectedLayoutStrategy();
	virtual ~ULTForceDirectedLayoutStrategy();

	virtual void Layout(UEdGraph* EdGraph) override;

protected:
	virtual FBox2D LayoutOneTree(ULTGenericGraphNode* RootNode, const FBox2D& PreTreeBound);

protected:
	bool bRandomInit;
	float InitTemperature;
	float CoolDownRate;
};
