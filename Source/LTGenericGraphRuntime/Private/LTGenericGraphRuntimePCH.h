// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

// #include "CoreUObject.h"
// #include "Engine.h"

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.
#include "ILTGenericGraphRuntime.h"

#define LOG_INFO(FMT, ...) UE_LOG(LogLTGenericGraph, Display, (FMT), ##__VA_ARGS__)
#define LOG_WARNING(FMT, ...) UE_LOG(LogLTGenericGraph, Warning, (FMT), ##__VA_ARGS__)
#define LOG_ERROR(FMT, ...) UE_LOG(LogLTGenericGraph, Error, (FMT), ##__VA_ARGS__)
