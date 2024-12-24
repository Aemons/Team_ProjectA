#pragma once

#include "CoreMinimal.h"

//x�� nullptr�̸� return
#define CheckNull(x) {if(x == nullptr) return;}

//x�� nullptr�̸� y�� return
#define CheckNullResult(x, y) {if(x == nullptr) return y;}

//x�� true�� return
#define CheckTrue(x) {if(x == true) return;}

//x�� true�� y�� return
#define CheckTrueResult(x) {if(x == true) return y;}

//x�� false�� return
#define CheckFalse(x) {if(x == false) return;}

//x�� false�� y�� return
#define CheckFalseResult(x) {if(x == false) return y;}

//PRINT�Լ����� �������� ���� InValue�� �����ؼ� ���
#define VALUE_STRING(x, y) {FString::Printf(TEXT(x), y)}

//Log_Line�� ���� �ʿ�
//#define LOG_LINE() {JHS_Global::Log(__FILE__,__FUNCTION__,__LINE__);}
#define PRINT_LINE() {JHS_Global::PrintLineFunction(FString(__FILE__), FString(__FUNCTION__), __LINE__);}

class TEAM_PROJECTA_API JHS_Global
{
public:	//UE_LOG�� �����ϰ� ����ϱ� ���� �Լ�
	//value�� int��
	static void Log(int32 InValue);
	//value�� float��
	static void Log(float InValue);
	//value�� string��
	static void Log(const FString& InValue);

public://AddOnScreenDebugMassage�� �����ϰ� ����ϱ� ���� �Լ�
	//value�� int��
	static void Print(int32 InValue, int32 InKey = -1, FColor InColor = FColor::Green, float InDuration = 3);

	//value�� float��
	static void Print(float InValue, int32 InKey = -1, FColor InColor = FColor::Green, float InDuration = 3);

	//value�� string��
	static void Print(const FString& InValue, int32 InKey = -1, FColor InColor = FColor::Green, float InDuration = 3);

public://PRINT�Լ��� ȣ��� line�� ã�� ���� �Լ�
	static void PrintLineFunction(const FString& InFile, const FString& InFunc, int32 InLine, FColor InColor = FColor::Magenta, int32 InKey = 0, float InDuration = 1);
};
