#include "LTGenericGraphAssetEditor/Settings_LTGenericGraphEditor.h"

ULTGenericGraphEditorSettings::ULTGenericGraphEditorSettings()
{
	LTAutoLayoutStrategy = ELTAutoLayoutStrategy::Tree;

	bFirstPassOnly = false;

	bRandomInit = false;

	OptimalDistance = 100.f;

	MaxIteration = 50;

	InitTemperature = 10.f;

	CoolDownRate = 10.f;
}

ULTGenericGraphEditorSettings::~ULTGenericGraphEditorSettings()
{

}

