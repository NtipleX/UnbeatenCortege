#pragma once
#include "DrawDebugHelpers.h"
//Current Class Name + Function Name where this is called!
#define TRACE_STR_CUR_CLASS_FUNC (FString(__FUNCTION__))
//Current Class where this is called!
#define TRACE_STR_CUR_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )
//Current Function Name where this is called!
#define TRACE_STR_CUR_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))
//Current Line Number in the code where this is called!
#define TRACE_STR_CUR_LINE  (FString::FromInt(__LINE__))
//Current Class and Line Number where this is called!
#define TRACE_STR_CUR_CLASS_LINE (TRACE_STR_CUR_CLASS + "(" + TRACE_STR_CUR_LINE + ")")
//Current Class Name + Function Name and Line Number where this is called!
#define TRACE_STR_CUR_CLASS_FUNC_LINE (TRACE_STR_CUR_CLASS_FUNC + "(" + TRACE_STR_CUR_LINE + ")")
//Current Function Signature where this is called!
#define TRACE_STR_CUR_FUNCSIG (FString(__FUNCSIG__))
//Screen Message
#define TRACE_SCREENMSG(OutputMessage) (GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *(TRACE_STR_CUR_CLASS_FUNC_LINE + ": " + OutputMessage)) )
#define TRACE_SCREENMSG_PRINTF(FormatString , ...) (GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *(TRACE_STR_CUR_CLASS_FUNC_LINE + ": " + (FString::Printf(TEXT(FormatString), ##__VA_ARGS__ )))) )
//UE LOG!
#define TRACE_LOG(LogCategory, OutputMessage) UE_LOG(LogCategory,Log,TEXT("%s: %s"), *TRACE_STR_CUR_CLASS_FUNC_LINE, *FString(OutputMessage))
#define TRACE_LOG_PRINTF(LogCat, FormatString , ...) UE_LOG(LogCat,Log,TEXT("%s: %s"), *TRACE_STR_CUR_CLASS_FUNC_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )
#define TRACE_WARNING(LogCategory, OutputMessage) UE_LOG(LogCategory,Warning,TEXT("%s: %s"), *TRACE_STR_CUR_CLASS_FUNC_LINE, *FString(OutputMessage))
#define TRACE_WARNING_PRINTF(LogCategory, FormatString , ...) UE_LOG(LogCategory,Warning,TEXT("%s: %s"), *TRACE_STR_CUR_CLASS_FUNC_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )
#define TRACE_ERROR(LogCategory, OutputMessage) UE_LOG(LogCategory,Error,TEXT("%s: %s"), *TRACE_STR_CUR_CLASS_FUNC_LINE, *FString(OutputMessage))
#define TRACE_ERROR_PRINTF(LogCategory, FormatString , ...) UE_LOG(LogCategory,Error,TEXT("%s: %s"), *TRACE_STR_CUR_CLASS_FUNC_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )
#define TRACE_FATAL(LogCategory, OutputMessage) UE_LOG(LogCategory,Fatal,TEXT("%s: %s"), *TRACE_STR_CUR_CLASS_FUNC_LINE, *FString(OutputMessage))
#define TRACE_FATAL_PRINTF(LogCategory, FormatString , ...) UE_LOG(LogCategory,Fatal,TEXT("%s: %s"), *TRACE_STR_CUR_CLASS_FUNC_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )
//Quick warning log
#define funcLog() TRACE_WARNING(LogTemp, TRACE_STR_CUR_CLASS_FUNC)
#define cLog(str) TRACE_WARNING(LogTemp, str)
#define cfLog(FormatString, ...) TRACE_WARNING_PRINTF(LogTemp, FormatString, ##__VA_ARGS__)
#define sLog(fstring) TRACE_WARNING_PRINTF(LogTemp, "%s", *fstring)
#define nLog(fname) sLog(fname.ToString())
#define fLog(num) TRACE_WARNING_PRINTF(LogTemp, "%f", num)
#define vLog(vec) TRACE_WARNING_PRINTF(LogTemp, "%s", *vec.ToString())
#define bLog(statement) {if(statement){cLog("true")} else{cLog("false")}}
#define iLog(num) TRACE_WARNING_PRINTF(LogTemp, "%d", num)
#define sDraw(loc) DrawDebugSphere(GetWorld(), loc, 5, 5, FColor::Cyan, false, 5)
#define lDraw(loc1, loc2) DrawDebugLine(GetWorld(), loc1, loc2, FColor::Blue, false, 5)