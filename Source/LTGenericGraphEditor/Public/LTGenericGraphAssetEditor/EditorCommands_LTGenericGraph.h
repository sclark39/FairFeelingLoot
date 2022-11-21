// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class LTGENERICGRAPHEDITOR_API FEditorCommands_LTGenericGraph : public TCommands<FEditorCommands_LTGenericGraph>
{
public:
	/** Constructor */
	FEditorCommands_LTGenericGraph()
		: TCommands<FEditorCommands_LTGenericGraph>("LTGenericGraphEditor", NSLOCTEXT("Contexts", "LTGenericGraphEditor", "Generic Graph Editor"), NAME_None, FAppStyle::GetAppStyleSetName())
	{
	}
	
	TSharedPtr<FUICommandInfo> GraphSettings;
	TSharedPtr<FUICommandInfo> AutoArrange;

	virtual void RegisterCommands() override;
};
