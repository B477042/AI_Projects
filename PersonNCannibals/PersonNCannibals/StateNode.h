#pragma once
//#include "AActor.h"
#include <list>
#include<vector>
#include<iostream>

using namespace std;


/*

	문제의 상태가 저장될 노드 입니다.

	Goal과 Start 지점에 누가 있는지
	그 다음은 어떤 노드와 연결 되있는지 
	무게값은 얼마인지

	그리고 현재 상황의 결과 값이 무엇인지 알려줍니다


	결과는 continue, Dead가 있습니다.

*/

//강의 지역에 대한 정보를 저장하는 구조체
struct FRegion
{
public:
	FRegion(int n_Missionary=0, int n_Cannibals=0,bool bBoat=false) :n_Missionary(n_Missionary), n_Cannibals(n_Cannibals),bIsBoatInThere(bBoat) {}

	int GetMissionaries() { return n_Missionary; }
	int GetCannibals() { return n_Cannibals; }
	bool IsBoatInThere() { return bIsBoatInThere; }
	//선교사들이 죽을 수 있는 상황인지 계산해서 return한다. 선교사수<식인종
	bool IsKillHappend()
	{
		if (n_Missionary < n_Cannibals&&n_Missionary>0)return true;
		return false;
	}

private:

	int n_Missionary;
	int n_Cannibals;
	bool bIsBoatInThere;
};

class AStateNode 	
{
public:
	//GoalSide와 StartSide를 지정
	AStateNode(FRegion* GoalSide = nullptr, FRegion*StartSide = nullptr) :GoalSide(GoalSide), StartSide(StartSide)
	{
		//만약 입력인자가 없다면 파괴 시킨다.
		if (GoalSide == nullptr || StartSide == nullptr)delete this;
		//보트 데이터를 입력하지 않은 경우
		if (isBoatInBoth() || isBoatNoWhere())delete this;
		bIsClear = false;
		bIsAnyoneDead = false;
		judgeResult();
		bIsVisted = false;
		
	}

	//nextNodes가 비어있다면 leaf node가 된다.
	bool IsLeafNode() { if (nextNodes.empty())return true; return false; }
	bool IsNodeDead() { return bIsAnyoneDead; }
	bool IsVisted() { return bIsVisted; }
	bool IsClear() { return bIsClear; }
	void SetVisited(bool bResult) { bIsVisted = bResult; }

	 
	 void  EndPlay();

	//이전 노드를 설정해줍니다
	void SetPrevNode(AStateNode* Other);
	//nextNodes에 newNode를 추가한다
	void AddNextNode(AStateNode* newNode);
	
	//현재 상황에 대해 출력합니다.
	void PrintSituation();
	//방문기록을 지웁니다
	void ResetNode();


	const list<AStateNode*> GetPrevNode() { return prevNode; }
	const list<AStateNode*> GetNextNodes() { return nextNodes; }
	
private:

	//현재 지역들을 검사해서 이 노드가 어떤 상태인지 검사한다.
	void judgeResult();
	//Boat가 양쪽에 있는지 검사한다. 
	bool isBoatInBoth();
	//양쪽 다 boat가 없는지 검사한다. 없다면 true
	bool isBoatNoWhere();

private:
	//다음 노드들
	list<AStateNode*> nextNodes;
	//이전 노드들
	list<AStateNode*> prevNode;
	//누가 죽었는지 판별한다
	bool bIsAnyoneDead;
	FRegion* StartSide;
	FRegion* GoalSide;
	bool bIsClear;
	bool bIsVisted;
};

