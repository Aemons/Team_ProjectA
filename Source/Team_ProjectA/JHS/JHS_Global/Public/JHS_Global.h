#pragma once

#include "CoreMinimal.h"

//x가 nullptr이면 return
#define CheckNull(x) {if(x == nullptr) return;}

//x가 nullptr이면 y를 return
#define CheckNullResult(x, y) {if(x == nullptr) return y;}

//x가 true면 return
#define CheckTrue(x) {if(x == true) return;}

//x가 true면 y를 return
#define CheckTrueResult(x) {if(x == true) return y;}

//x가 false면 return
#define CheckFalse(x) {if(x == false) return;}

//x가 false면 y를 return
#define CheckFalseResult(x) {if(x == false) return y;}

//PRINT함수에서 가변인자 사용시 InValue에 적용해서 사용
#define VALUE_STRING(x, y) {FString::Printf(TEXT(x), y)}

//Log_Line은 수정 필요
//#define LOG_LINE() {JHS_Global::Log(__FILE__,__FUNCTION__,__LINE__);}
#define PRINT_LINE() {JHS_Global::PrintLineFunction(FString(__FILE__), FString(__FUNCTION__), __LINE__);}

class TEAM_PROJECTA_API JHS_Global
{
public:	//UE_LOG를 간략하게 사용하기 위한 함수
	//value가 int형
	static void Log(int32 InValue);
	//value가 float형
	static void Log(float InValue);
	//value가 string형
	static void Log(const FString& InValue);

public://AddOnScreenDebugMassage를 간략하게 사용하기 위한 함수
	//value가 int형
	static void Print(int32 InValue, int32 InKey = -1, FColor InColor = FColor::Green, float InDuration = 3);

	//value가 float형
	static void Print(float InValue, int32 InKey = -1, FColor InColor = FColor::Green, float InDuration = 3);

	//value가 string형
	static void Print(const FString& InValue, int32 InKey = -1, FColor InColor = FColor::Green, float InDuration = 3);

public://PRINT함수가 호출된 line을 찾기 위한 함수
	static void PrintLineFunction(const FString& InFile, const FString& InFunc, int32 InLine, FColor InColor = FColor::Magenta, int32 InKey = 0, float InDuration = 1);
};
