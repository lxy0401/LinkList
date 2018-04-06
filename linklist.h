#pragma once
typedef char LinkNodeType; 

typedef struct LinkNode 
{ 
    LinkNodeType data; 
    struct LinkNode* next; 
}LinkNode; 

//1.链表初始化
void LinkListInit(LinkNode** node); 

//2.尾插
void LinkListPushBack(LinkNode** phead, LinkNodeType value); 

//3.尾删
void LinkListPopBack(LinkNode** phead); 

//4.头插
void LinkListPushFront(LinkNode** phead,LinkNodeType value);

//5.头删
void LinkListPopFront(LinkNode** phead);

//6.将一个新节点插入到pos之后
void LinkListInsert(LinkNode* phead,LinkNode* pos,LinkNodeType value);

//7.将一个新节点插入到pos之前
void LinkListInsertBefore(LinkNode** phead,LinkNode* pos,LinkNodeType value);

//对LinkListInsertBefore进行优化O(n)->O(1)
void LinkListInsertBefore2(LinkNode* pos,LinkNodeType value);

//8.删除pos位置节点
void LinkListErase(LinkNode** phead,LinkNode* pos);

//对LinkListErase进行优化
void LinkListErase2(LinkNode** phead,LinkNode* pos);

//9.找到节点就返回节点对应的地址，若没找到就返回NULL
LinkNode* LinkListFind(LinkNode* head,LinkNodeType to_find);

//10.删除指定元素
void LinkListRemove(LinkNode** phead,LinkNodeType to_remove);

//11.删除所有指定元素
void LinkListRemoveall(LinkNode** phead,LinkNodeType to_remove);

//12.判断链表是否为空，若为空返回1，否则返回0
int LinkListEmpty(LinkNode* head);

//13.求链表的长度
int LinkListSize(LinkNode* head);

//14.找第一个节点
LinkNode* LinkListFront(LinkNode* head);

//15.找最后一个节点
LinkNode* LinkListBack(LinkNode* head);

//16.链表销毁
void LinkListDestroy(LinkNode** phead);

/********
 *
 *以下为面试题目
 *
 *
 *********/

//1.将链表从最后一个元素到第一个元素开始打印
void LinkListPrintReverse(LinkNode* head);

//2.约瑟夫环问题
LinkNode* JosphCricle(LinkNode* head,int M);

//3.链表逆置
void LinkListReverse(LinkNode** phead);

//优化LinkListReverse
void LinkListReverse2(LinkNode** phead);

//4.对单链表进行排序（冒泡法）
void LinkListBubbleSort(LinkNode* head);

//5.合并两个有序链表并且之后依旧有序
LinkNode* LinkListMerge(LinkNode* head1,LinkNode* head2);

//6.查找链表对中间节点，只能遍历一次链表
LinkNode* LinkListFindMidNode(LinkNode* head);

//7.查找链表对倒数第k个节点
LinkNode* LinkListFindLastKNode(LinkNode* head,int k);

//8.删除倒数第k个节点
void LinkListEraseLastKNode(LinkNode** phead,int k);

//9.判断单链表是否带环
LinkNode* LinkListHasCricle(LinkNode* head);

//10.计算环对长度
//size_t LinkListCricleLen(LinkNode* head);

//11.求环的入口
LinkNode* LinkListCricleEntty(LinkNode* head);

//12.判断两个环是否相交（链表不带环）
int LinkListHasCross(LinkNode* head1,LinkNode* head2);

//13.若相交，求交点
LinkNode* LinkListCrossPos(LinkNode* head1,LinkNode* head2);

//14.两个链表是否相交（可能带环）
int LinkListHasCrossWithCrecle(LinkNode* head1,LinkNode* head2);

//15.若相交，求交点（环外相交）
LinkNode* LinkListCrossWithCirclePos(LinkNode* head1,LinkNode* head2);

//16.找两个已排序链表对相同部分
LinkNode* LinkListUnionSet(LinkNode* head1,LinkNode* head2);

typedef struct ComplexNode
{
    LinkNodeType data;
    struct ComplexNode* next;
    struct ComplexNode* random;
}ComplexNode;

//17.复杂链表拷贝
ComplexNode* CopyComplexList(ComplexNode* head);
