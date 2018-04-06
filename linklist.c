#include"linklist.h"
#include<stdlib.h>

//1.链表初始化
void LinkListInit(LinkNode** node) 
{
    *node = NULL;
}

void LinkListInit2(LinkNode* node)
{
    node = NULL;
}

LinkNode* LinkListInit3()
{
    return NULL;
}

LinkNode* CreateNode(LinkNodeType value)
{
    LinkNode *new_node=(LinkNode*)malloc(sizeof(LinkNode));
    new_node->data=value;
    new_node->next=NULL;
    return new_node;
}
//2.尾插
void LinkListPushBack(LinkNode** phead, LinkNodeType value)
{
    if(phead == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead == NULL)
    {
	//空链表
	*phead=CreateNode(value);
	return ;
    }
    //链表非空
    LinkNode *cur=*phead;
    while(cur->next!=NULL)
    {
	cur=cur->next;
    }
    LinkNode *new_node=CreateNode(value);
    cur->next=new_node;
    new_node->next=NULL;
    return ;
}

void DestroyNode(LinkNode *node)
{
    //free(*node->data);
    free(node);
    return ;
}

//3.尾删
void LinkListPopBack(LinkNode** phead)
{
    if(phead == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead==NULL)
    {
	//空链表
	return ;
    }
    if((*phead)->next==NULL)
    {
	//只有一个元素
	DestroyNode(*phead);
	*phead=NULL;
	return ;
    }
    LinkNode *cur=*phead;
    LinkNode *pre=NULL;
    while(cur->next!=NULL)
    {
	pre=cur;
	cur=cur->next;
    }
    //当循环结束，cur指向最后一个节点，pre指向倒数第二个节点
    pre->next=NULL;
    DestroyNode(cur);
    return ;
}

//4.头插
void LinkListPushFront(LinkNode** phead,LinkNodeType value)
{
    if(phead == NULL)
    {
	//非法输入
	return ;
    }
    LinkNode* new_node=CreateNode(value);
    new_node->next=*phead;
    *phead=new_node;
}

//5.头删
void LinkListPopFront(LinkNode** phead)
{
    if(phead == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead == NULL)
    {
	//空链表
	return ;
    }
    LinkNode* to_erase=*phead;
    *phead=(*phead)->next;
    DestroyNode(to_erase);
    return ;
}

//6.将一个新节点插入到pos之后
void LinkListInsert(LinkNode* phead,LinkNode* pos,LinkNodeType value)
{
    if(pos == NULL)
    {
	//非法输入
	//pos表示一个节点的指针，若pos为空，则表示根本不存在这样的节点
    return ;
    }
    LinkNode* new_node=CreateNode(value);
    new_node->next=pos->next;
    pos->next=new_node;
    return ;

}

/*
//将一个新节点插入到pos之前
void LinkListInsertBefore(LinkNode** phead,LinkNode* pos,LinkNodeType value)
{
    if(phead == NULL || pos == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead == pos)
    {
	//要插入的位置为头结点
	LinkListPushFront(phead,value);
	return ;
    }
    LinkNode *cur=*phead;
    for(;cur!=NULL;cur=cur->next)
    {
	if(cur->next==pos)
	{
	    break;
	}
    }
    //循环结束后要知道是由于哪种情况导致的循环结束到底找没找到pos
    if(cur == NULL)
    {
	//没找到
	return ;
    }
    LinkListInsert(phead,cur,&value);
    return ;
}
*/

//7.对LinkListInsertBefore进行优化O(n)->O(1)
void LinkListInsertBefore2(LinkNode* pos,LinkNodeType value)
{
    if(pos == NULL)
    {
	//非法输入
	return ;
    }
    LinkNode* new_node=CreateNode(pos->data);
    new_node->next=pos->next;
    pos->next=new_node;
    pos->data=value;
    //或者将上面四行代码改为
    //LinkListInsert(pos,pos->data);
    //pos->data=value;
}

//8.删除pos位置节点
void LinkListErase(LinkNode** phead,LinkNode* pos)
{
    if(phead == NULL || pos == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead == NULL)
    {
	//空链表
	return ;
    }
    LinkNode *cur=*phead;
    for(;cur!=NULL;cur=cur->next)
    {
	if(cur->next==pos)
	{
	    break;
	}
    }
    //循环结束之后要判定是找到了退出还是没找到pos退出
    if(cur == NULL)
    {
	return ;
    }
    cur->next=pos->next;
    DestroyNode(pos);
    return ;
}

//对LinkListErase进行优化
void LinkListErase2(LinkNode** phead,LinkNode* pos)
{
    if(phead == NULL || pos == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead == NULL)
    {
	//空链表
	return ;
    }
    if(pos->next == NULL)
    {
	//要删除的元素为最后一个元素
	LinkListPopBack(phead);
	return ;
    }
    pos->data=pos->next->data;
    LinkNode* to_erase=pos->next;
    pos->next=to_erase->next;
    DestroyNode(to_erase);
}

//9.找到节点就返回节点对应的地址，若没找到就返回NULL
LinkNode* LinkListFind(LinkNode* head,LinkNodeType to_find)
{
    if(head == NULL)
    {
	//空链表
	return NULL;
    }
    LinkNode* cur=head;
    while(cur!=NULL)
    {
	if(cur->data==to_find)
	{
	    return cur;
	}
	cur=cur->next;
    }
    return NULL;
}

//10删除指定元素
void LinkListRemove(LinkNode** phead,LinkNodeType to_remove)
{////
    if(phead == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead == NULL)
    {
	//空链表
	return ;
    }
    //删除的元素恰好是第一个
    if((*phead)->data==to_remove)
    {
	LinkNode* to_delete=*phead;
	*phead=(*phead)->next;
	DestroyNode(to_delete);
	return ;
    }
    LinkNode* cur=*phead;
    for(;cur->next!=NULL;cur=cur->next)
    {
	if(cur->next->data==to_remove)
	{
	    //cur指向要删除的元素的前一个元素的位置
	    LinkNode* to_delete=cur->next;
	    cur->next=to_delete->next;
	    DestroyNode(to_delete);
	}
    }
    return ;
}

//11.删除所有指定的元素
void LinkListRemoveall(LinkNode** phead,LinkNodeType to_remove)
{
    if(phead == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead == NULL)
    {
	//空链表
	return ;
    }
    while(1)
    {
	LinkNode* pos=LinkListFind(*phead,to_remove);
	if(pos==NULL)
	{
	    //没有找到
	    return ;
	}
	LinkListErase(phead,pos);
    }
    return ;
}

//12.判断链表是否为空，若为空返回1，否则返回0
int LinkListEmpty(LinkNode* head)
{
//    return head == NULL?1:0;
    if(head == NULL)
    {
	//空链表
	return 1;
    }
    return 0;
}

//13.求链表的长度(节点数)
int LinkListSize(LinkNode* head)
{
    if(head == NULL)
    {
	//空链表
	return 0;
    }
    LinkNode* cur=head;
    size_t size=0;
    while(cur!=NULL)
    {
        ++size;
	    cur=cur->next;
    }
    return size;
}

//14.找第一个节点
LinkNode* LinkListFront(LinkNode* head)
{
    return head;
}

//15.找最后一个节点
LinkNode* LinkListBack(LinkNode* head)
{
    if(head == NULL)
    {
        //空链表
	    return NULL;
    }
    LinkNode* cur=head;
    while(cur->next!=NULL)
    {
	cur=cur->next;
    }
    return cur;
}

//16.链表销毁
void LinkListDestroy(LinkNode** phead)
{
    if(phead == NULL)
    {
	//非法输入
	return ;
    }
    if(*phead == NULL)
    {
	//空链表
	return ;
    }
    LinkNode* cur=*phead;
    while(cur!=NULL)
    {
	LinkNode* to_delete=cur;
	cur=cur->next;
	DestroyNode(to_delete);
    }
    *phead == NULL;
}


/**
 *
 *
 *
 *以下为面试题目
 *以下为面试题目
 *以下为面试题目
 *以下为面试题目
 *
 *
 *
 *
 */
//1.将链表从最后一个元素到第一个元素开始打印
#include <stdio.h>
void LinkListPrintReverse(LinkNode* head)
{
    if(head == NULL)
    {
        //空链表
        return ;
    }
    //运用递归
    LinkListPrintReverse(head->next);
    printf("%c",head->data);
}

//2约瑟夫环
LinkNode* JosphCricle(LinkNode* head,int M)
{
    if(head == NULL)
    {
        //空链表
        return NULL;
    }
    LinkNode* cur=head;
    while(cur->next!=cur)
    {
        int i=1;
        for(;i<M;++i)
        {
            cur=cur->next;
        }
        //cur指向的元素就是要被吃掉的元素
        printf("%c\n",cur->data);
        cur->data=cur->next->data;
        LinkNode* to_delete=cur->next;
        cur->next=to_delete->next;
        DestroyNode(to_delete);
    }
    return cur;
}

//3.链表逆置
void LinkListReverse(LinkNode** phead)
{
    if(phead == NULL)
    {
        //非法输入
        return;
    }
    if(*phead == NULL)
    {
        //空链表
        return ;
    }
    if((*phead)->next == NULL)
    {
        //只有一个元素
        return ;
    }
    LinkNode* cur=*phead;
    while(cur->next!=NULL)
    {
        LinkNode* to_delete=cur->next;
        //把这个节点删除掉
        cur->next=to_delete->next;
        //把删除掉的元素插入到链表头部
        to_delete->next=*phead;
        *phead=to_delete;
    }
    return ;
}

//优化LinkListReverse
void LinkListReverse2(LinkNode** phead)
{
    if(phead == NULL)
    {
        //非法输入
        return ;
    }
    if(*phead == NULL)
    {
        //空链表
        return ;
    }
    if((*phead)->next==NULL)
    {
        //只有一个元素
        return ;
    }
    LinkNode* cur=(*phead)->next;
    LinkNode* pre=(*phead);
    while(cur!=NULL)
    {
        LinkNode* next=cur->next;
        //修改cur->next指针的指向
        cur->next=pre;
        //交换pre cur指针
        pre=cur;
        cur=cur->next;
    }
    //修改头指针指向
    *phead=pre;
}

//交换两个值
void Swap(LinkNodeType* a,LinkNodeType* b)
{
    LinkNodeType tmp=*a;
    *a=*b;
    *b=tmp;
}
//4.对单链表进行排序（冒泡法）
void LinkListBubbleSort(LinkNode* head)
{
    if(head == NULL)
    {
        //空链表
        return ;
    }
    if(head->next = NULL)
    {
        //只有一个节点
        return;
    }
    LinkNode* count=head;
    LinkNode* tail=NULL;//结束标记
    //第一重循环表示排序的趟数
    for(;count!=NULL;count=count->next)
    {
        LinkNode* cur=head;
        //第二重循环表示保证将当前最大值冒到最后
        for(;cur->next!=tail;cur=cur->next)
        {
            if(cur->data>cur->next->data)
            {
                Swap(&cur->data,&cur->next->data);
            }
        }
        tail=cur;
    }
    return ;
}

//5.合并两个有序链表并且之后依旧有序
LinkNode* LinkListMerge(LinkNode* head1,LinkNode* head2)
{
    if(head1 == NULL)
    {
        return head2;
    }
    if(head2 == NULL)
    {
        return head1;
    }
    LinkNode* cur1=head1;
    LinkNode* cur2=head2;
    //用来指向新链表的头结点和尾节点
    LinkNode* new_head=NULL;
    LinkNode* new_tail=NULL;
    while(cur1=NULL&&cur2!=NULL)
    {
        if(cur1->data<cur2->data)
        {
            if(new_tail == NULL)
            {
                new_tail=new_tail=cur1;
            }
            else
            {
                new_tail->next=cur1;
                new_tail=new_tail->next;
            }
            cur1=cur1->next;
        }
        else if(cur1->data>cur1->data)
        {
            if(new_tail == NULL)
            {
                new_tail=new_tail=cur2;
            }
            else
            {
                new_tail->next=cur2;
                new_tail-new_tail->next;
            }
        }
    }
    //有一方已经先到达结尾，要将剩余部分接到新的链表之后
    if(cur1=NULL)
    {
        new_tail->next=cur1;
    }
    else
    {
        new_tail->next=cur2;
    }
    return new_head;
}

//6.查找单链表的中间节点，只能遍历一次链表
LinkNode* LinkListFindMidNode(LinkNode* head)
{
    if(head == NULL)
    {
        //空链表
        return NULL;
    }
    LinkNode* slow=head;
    LinkNode* fast=head;
    while(fast!=NULL&&fast->next!=NULL)
    {
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}

//7.查找链表的倒数第k个节点
LinkNode* LinkListFindLastKNode(LinkNode* head,int k)
{
    if(head == NULL)
    {
        //空链表
        return NULL;
    }
    LinkNode* fast=head;
    LinkNode* slow=head;
    //让fast先走k步
    int i=0;
    for(;i<k;++i)
    {
        if(fast==NULL)
        {
            break;
        }
        fast=fast->next;
    }
    if(i!=0)
    {
        //没走完，k的数值超过链表长度
        return NULL;
    }
    while(fast!=NULL)
    {
        fast=fast->next;
        slow=slow->next;
    }
    return slow;
}

//8.删除倒数第k个节点
void LinkListEraseLastKNode(LinkNode** phead,int k)
{
    if(phead == NULL)
    {
        //非法输入
        return ;
    }
    if(*phead == NULL)
    {
        //空链表
        return ;
    }
    int len=LinkListSize(*phead);
    if(k>len)
    {
        return ;
    }
    if(k == len)
    {
        //要删除的元素为第一个
        LinkNode* to_delete=*phead;
        *phead=(to_delete)->next;
        DestroyNode(to_delete);
        return ;
    }
    LinkNode* pre=*phead;
    int i=0;
    for(;i<len-(k+1);++i)
    {
        pre=pre->next;
    }
    //循环结束后意味着pre已指向要删除元素的前一个节点
    LinkNode* to_delete=pre->next;
    pre->next=to_delete->next;
    DestroyNode(to_delete);
    //return ;
}

//9.判断单链表是否带环
LinkNode* LinkListHasCricle(LinkNode* head)
{
    if(head == NULL)
    {
        //空链表
        return NULL;
    }
    LinkNode* fast=head;
    LinkNode* slow=head;
    while(fast!=NULL&&fast->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
        if(fast==slow)
        {
            return slow;
        }
    }
    return NULL;
}

//10.计算环的长度
size_t LinkListCricleLen(LinkNode* head)
{
    if(head == NULL)
    {
        //空链表
        return 0;
    }
    LinkNode* meet_node=LinkListHasCricle(head);
    if(meet_node == NULL)
    {
        return 0;
    }
    LinkNode* cur=meet_node->next;
    size_t len=1;
    while(cur!=meet_node)
    {
        cur=cur->next;
        len++;
    }
    return len;
}

//11.求环的入口
LinkNode* LinkListCricleEntry(LinkNode* head)
{
    if(head == NULL)
    {
        //空链表
        return NULL;
    }
    LinkNode* meet_node=LinkListHasCricle(head);
    if(meet_node == NULL)
    {
        return NULL;
    }
    LinkNode* cur1=head;
    LinkNode* cur2=meet_node;
    while(cur1!=cur2)
    {
        cur1=cur1->next;
        cur2=cur2->next;
    }
    return cur1;
}

//12.判断两个链表是否相交（链表不带环）
int LinkListHasCross(LinkNode* head1,LinkNode* head2)
{
    if(head1 == NULL||head2 == NULL)
    {
        //空链表
        return 0;
    }
    LinkNode* cur1=head1;
    LinkNode* cur2=head2;
    for(;cur1->next!=NULL;cur1=cur1->next);
    for(;cur2->next!=NULL;cur2=cur2->next);
    return cur1 == cur2?1:0;
}

//13.接上一问题：若相交，求交点
LinkNode* LinkListCrossPos(LinkNode* head1,LinkNode* head2)
{
    size_t len1=LinkListSize(head1);
    size_t len2=LinkListSize(head2);
    LinkNode* cur1=head1;
    LinkNode* cur2=head2;
    if(len1>len2)
    {
        size_t i=0;
        for(;i<len1-len2;++i)
        {
            cur1=cur1->next;
        }
    }
    else
    {
        size_t i=0;
        for(;i<len2-len1;++i)
        {
            cur2=cur2->next;
        }
        while(cur1!=NULL&&cur2!=NULL)
        {
            if(cur1 == cur2)
            {
                return cur1;
            }
            cur1=cur1->next;
            cur2=cur2->next;
        }
        return NULL;
    }
}

//14.两个链表是否相交（可能带环）
int LinkListHasCrossWithCircle(LinkNode* head1,LinkNode* head2)
{
    //分别求两个链表的入口
    LinkNode* entry1=LinkListCricleEntry(head1);
    LinkNode* entry2=LinkListCricleEntry(head2);
    //（1）若两个链表都不带环，则用上面的方法
    if(entry1 == NULL && entry2 == NULL)
    {
        return LinkListHasCross(head1,head2);
    }
    //（2）若有一个带环，一个不带环，则返回不相交
    if((entry1 == NULL && entry2!=NULL)||(entry1!=NULL && entry2 == NULL))
    {
        return 0;
    }
    //（3）若两个都带环
    //1）若入口点重合，说明环外相交
    if(entry1 == entry2)
    {
        return 1;
    }
    //2）若从一个入口点出发，绕环一周能到达第二个入口点，则说明是环内相交
    LinkNode* cur=entry1->next;
    while(cur!=entry1)
    {
        if(cur == entry2)
        {
            return 1;
        }
        cur=cur->next;
    }
    //3）若以上两种情况都不是，则不相交
    return 0;
}

//15.接上一问题：若相交，求交点(环外相交)
LinkNode* LinkListCrossWithCirclePos(LinkNode* head1,LinkNode* head2)
{
    LinkNode* longlist=NULL;
    LinkNode* shortlist=NULL;
    LinkNode* cur1=head1;
    LinkNode* cur2=head2;
    int count1=0;
    int count2=0;
    int gap=0;
    LinkNode* meet_node=LinkListHasCricle(head1);
    while(cur1!=meet_node)
    {
        count1++;
        cur1=cur1->next;
    }
    while(cur2!=meet_node)
    {
        count2++;
        cur2=cur2->next;
    }
    longlist=head1;
    shortlist=head2;
    if(count1<count2)
    {
        longlist=head2;
        shortlist=head1;
    }
    gap=abs(count1-count2);
    while(gap--)
    {
        longlist=longlist->next;
    }
    while(shortlist!=longlist)
    {
        shortlist=shortlist->next;
        longlist=longlist->next;
    }
    return shortlist;
}
//16.找两个已排序链表的相同部分（默认每个链表中不包含连续相同的元素，如2333333）
LinkNode* LinkListUnionSet(LinkNode* head1,LinkNode* head2)
{
    LinkNode* cur1=head1;
    LinkNode* cur2=head2;
    LinkNode* new_head=NULL;
    LinkNode* new_tail=NULL;
    while(cur1!= NULL && cur2!=NULL)
    {
        if(cur1->data<cur2->data)
        {
            cur1=cur1->next;
        }
        else if(cur1->data>cur2->data)
        {
            cur2=cur2->next;
        }
        else{   //cur1=cur2
            if(new_head==NULL)
            {
                new_head=new_tail=CreateNode(cur1->data);
                cur1=cur1->next;
                cur2=cur2->next;
            }
            else{
                new_tail->next=CreateNode(cur2->data);
                new_tail=new_tail->next;
                cur1=cur1->next;
                cur2=cur2->next;
            }
            //cur1=cur1->next;
            //cur2=cur2->next;

            }
        //return new_head;
    }
    return new_head;
}

//17.复杂链表拷贝
typedef struct ComplexNode
{
    LinkNodeType data;
    struct ComplexNode* next;
    struct ComplexNode* random;
}ComplexNode;

ComplexNode* CreateComplexNode(LinkNodeType value)
{
    ComplexNode* new_node=(ComplexNode*)malloc(sizeof(ComplexNode));
    new_node->data=value;
    new_node->next=NULL;
    new_node->random=NULL;
    return new_node;
}

size_t Diff(ComplexNode* src,ComplexNode* dst)
{
    size_t offset=0;
    while(src!=NULL)
    {
        if(src == dst)
        {
            break;
        }
        ++offset;
        src=src->next;
    }
    if(src == NULL)
    {
        return(size_t)-1;   //是一个特别大的值
    }
}

ComplexNode* Step(ComplexNode* head,size_t offset)
{
    ComplexNode* cur=head;
    size_t i=0;
    while(1)
    {
        if(head == NULL)
        {
            return NULL;
        }
        if(i>=offset)
        {
            return cur;
        }
        ++i;
        cur=cur->next;
    }
    return NULL;
}
/*
ComplexNode* CopyComplexList(ComplexNode* head)
{
    //先按照简单的链表copy一份
    ComplexNode* new_head=NULL;
    ComplexNode* new_tail=NULL;
    ComplexNode* cur=head;
    for(;cur!=NULL;cur=cur->next)
    {
        ComplexNode* new_node=CreateComplexNode(cur->data);
        if(new_node == NULL)
        {
            new_head=new_tail=new_node;
        }
        else{
            new_tail->next=new_node;
            new_tail=new_tail->next;
        }
    }
    //遍历链表，找到每个链表节点random指针相对于链表头指针的偏移量  
    //遍历新链表，根据偏移量设新链表的random指针
    ComplexNode* new_cur=new_head;
    for(cur=head;cur!=NULL;cur=cur->next,new_cur=new_cur->next)
    {

    if(cur->random == NULL)
    {
        new_cur->random = NULL;
        continue;
    }
        //通过Diff函数计算出链表两个节点的偏移量
        size_t offset=Diff(head,cur->random);
        //通过Step函数，相当于求出从new_head出发，走了offset步到达的位置
        new_cur->random;
    }
    return new_head;

}
*/

ComplexNode* CopyComplexList2(ComplexNode* head)
{
    //遍历链表在每个链表后插入新节点
    //维护新节点的random指针
    //新节点排除
    ComplexNode* cur=head;
    for(;cur!=NULL;cur=cur->next->next)
    {
        ComplexNode* new_node=CreateComplexNode(cur->data);
        new_node->next=cur->next;
    }
    for(cur=head;cur!=NULL;cur=cur->next->next)
    {
        ComplexNode* new_cur=cur->next;
        if(cur->random==NULL)
        {
            new_cur->random=NULL;
            continue;
        }
        new_cur->random=cur->random->next;
    }
    ComplexNode* new_head=NULL;
    ComplexNode* new_tail=NULL;
    for(cur=head;cur!=NULL;cur=cur->next)
    {
        ComplexNode* new_cur=cur->next;
        cur->next=new_cur->next;
        if(new_head == NULL)
        {
            new_head=new_tail=new_cur;
        }
        else{
            new_tail->next=new_cur;
            new_tail=new_tail->next;
        }
        new_tail=NULL;
    }
    return new_head;
}

//以下为测试代码
#include<stdio.h>
#define TEST_HEADER printf("\n========%s=========\n",__FUNCTION__)
void LinkListPrintChar(LinkNode *head,const char *msg)
{
    printf("[%s]\n",msg);
    LinkNode *cur=head;
    for(;cur!=NULL;cur=cur->next)
    {
	printf("[%c|%p]",cur->data,cur);
    }
    printf("\n");
}

void Testsizeof()
{
    TEST_HEADER;
    printf("sizeof:%lu\n",sizeof(LinkNode));
}

void TestInit()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPrintChar(head,"对链表进行初始化操作");
}

void TestInit2()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit2(head);
    LinkListPrintChar(head,"对链表进行初始化操作");
}
void TestInit3()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit3(&head);
    LinkListPrintChar(head,"对链表进行初始化操作");
}
void TestPushBack()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPrintChar(head,"对链表尾部插如四个元素");   
}

void TestPopBack()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d'); 
    LinkListPrintChar(head,"对链表尾部进行删除");   
    LinkListPopBack(&head);
    LinkListPopBack(&head);
    LinkListPrintChar(head,"对链表尾部进行删除两个元素");   
}

void TestPushFront()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkListPrintChar(head,"对链表头部插入四个元素");   

}

void TestPopFront()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkListPrintChar(head,"对链表头部进行删除"); 
    LinkListPopFront(&head);
    LinkListPopFront(&head);
    LinkListPrintChar(head,"对链表头部进行删除两个元素"); 


}

void TestInsert()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkListPrintChar(head,"对链表pos位置之后进行新的节点插入"); 
    LinkNode* pos=head->next;	//头结点的下一个位置为节点c
    LinkListInsert(head,pos,'x');
    LinkListPrintChar(head,"对链表c位置之后进行新的节点插入x"); 
 
}

void TestInsertBefore()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkListPrintChar(head,"对链表pos位置之前进行新的节点插入"); 
    LinkNode* pos1=head; 
    //LinkListInsertBefore(&head,pos1,'x');
    LinkListPrintChar(head,"对链表头结点之前进行新的节点插入x");
    LinkNode* pos2=head->next->next;	//插入新的头结点之后，头结点的下两个节点为c
   // LinkListInsertBefore(&head,pos2,'y');
    LinkListPrintChar(head,"对链表c位置之前进行新的节点插入y"); 
 
}

void TestInsertBefore2()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkListPrintChar(head,"对链表pos位置之前进行新的节点插入"); 
    LinkNode* pos1=head; 
    LinkListInsertBefore2(pos1,'x');
    LinkListPrintChar(head,"对链表头结点之前进行新的节点插入x");
    LinkNode* pos2=head->next->next;	//插入新的头结点之后，头结点的下两个节点为c
    LinkListInsertBefore2(pos2,'y');
    LinkListPrintChar(head,"对链表c位置之前进行新的节点插入y"); 
 
}

void TestErase()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPrintChar(head,"对链表pos位置的节点进行删除");
//    LinkListErase((LinkNode*)0x11);
//    LinkListPrintChar(head,"对空链表进行删除");
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkNode* pos1=head->next;	//头结点的下一个节点为c
    LinkListErase(&head,pos1); 
    LinkListPrintChar(head,"对链表c节点进行删除");
    LinkNode* pos2=(LinkNode*)0x10;
    LinkListErase(&head,pos2);
    LinkListPrintChar(head,"对链表不存在的节点进行删除");
 
 
}

void TestErase2()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPrintChar(head,"对链表pos位置的节点进行删除");
//    LinkLinstErase((LinkNode*)0x11);
//    LinkListPrintChar(head,"对空链表进行删除");
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkNode* pos1=head->next;	//头结点的下一个节点为c
    LinkListErase(&head,pos1); 
    LinkListPrintChar(head,"对链表c节点进行删除");
//    LinkNode* pos2=(LinkNode*)0x10;
//    LinkListErase(&head,pos2);
//    LinkListPrintChar(head,"对链表不存在的节点进行删除");
 
 
}

void TestFind()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkNode* pos_x=LinkListFind(head,'x');
    printf("pos_x expect NULL,actuall %p\n",pos_x);
    LinkNode* pos_c=LinkListFind(head,'c');
    printf("pos_x expect %p,actuall %p\n",head->next,pos_c);
    
}

void TestRemove()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    //空链表
    LinkListRemove(&head,'x');
    LinkListPrintChar(head,"对空链表进行删除");
    //删除第一个元素
    LinkListPushFront(&head,'a');
    LinkListRemove(&head,'a');
    //删除后面的元素
    //(1)删除的元素不存在
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkListRemove(&head,'x');
    LinkListPrintChar(head,"删除不存在的元素x");
    //(2)删除的元素存在
    LinkListRemove(&head,'b');
    LinkListPrintChar(head,"删除存在的元素b");
    
}

void TestRemoveall()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    //空链表
    //LinkListRemoveall(&head,'x');
    //LinkListPrintChar(head,"对空链表进行删除");
    //删除第一个元素
    //LinkListPushFront(&head,'a');
    //LinkListRemoveall(&head,'a');
    //删除后面的元素
    //(1)删除的元素不存在
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d'); 
    LinkListPushFront(&head,'d'); 
    LinkListPushFront(&head,'d'); 
    //LinkListRemoveall(&head,'x');
    //LinkListPrintChar(head,"删除不存在的元素x");
    //(2)删除的元素存在
    LinkListRemoveall(&head,'d');
    LinkListPrintChar(head,"删除存在的元素d");
    
}

void TestEmpty()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPrintChar(head,"空链表应该返回1");
    LinkListEmpty(head);
    LinkListPrintChar(head,"非空链表应该返回0");
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d');  
    LinkListEmpty(head); 
    //printf("expect 0,actuall %d\n",);

}

void TestSize()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPrintChar(head,"空链表长度为0");
    LinkListSize(head); 
    LinkListPrintChar(head,"链表长度为4");
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d');  
    LinkListSize(head); 

}

void TestFront()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    //LinkListPrintChar(head,"第一个节点为d");
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d');  
    LinkListPrintChar(head,"第一个节点为d");
    LinkListFront(head); 

}

void TestBack()
{
    TEST_HEADER;
    LinkNode *head;
    LinkListInit(&head);
    LinkListPrintChar(head,"最后一个节点为d");
    LinkListPushFront(&head,'a');
    LinkListPushFront(&head,'b');
    LinkListPushFront(&head,'c');
    LinkListPushFront(&head,'d');  
    LinkListBack(head); 

}

void TestPrintReverse()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPrintChar(head,"逆置打印链表");
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPrintReverse(head);
}

void TestJosephCricle()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPrintChar(head,"约瑟夫环问题");
    LinkNode* a=CreateNode('a');
    LinkNode* b=CreateNode('b');
    LinkNode* c=CreateNode('c');
    LinkNode* d=CreateNode('d');
    LinkNode* e=CreateNode('e');
    LinkNode* f=CreateNode('f');
    LinkNode* g=CreateNode('g');
    LinkNode* h=CreateNode('h');
    a->next=b;
    b->next=c;
    c->next=d;
    d->next=e;
    e->next=f;
    f->next=g;
    g->next=h;
    h->next=a;
    LinkNode* survive=JosphCricle(a,5);
    printf("survive is %c\n",survive->data);

}

void TestReverse()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListReverse(&head);
    LinkListPrintChar(head,"将链表最后一个元素插入到链表头部");

}

void TestFindMidNode()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkNode* mid=LinkListFindMidNode(head);
    printf("mid expected b,actuall %c\n",mid->data);

}

void TestFindLastNode()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkNode* result=LinkListFindLastKNode(head,2);
    printf("last expected d,actuall %c\n",result->data);

}


void TestEraseLastKNode()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListEraseLastKNode(&head,2);
    LinkListPrintChar(head,"删除倒数第2个节点");
}

void TestHasCricle()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    //LinkNode* a=CreateNode('a');
   //LinkNode* b=CreateNode('b');
   // LinkNode* a=CreateNode('c');
    
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
    LinkNode* pos_e=LinkListFind(head,'e');
    pos_e->next=head->next;
    LinkNode* ret=LinkListHasCricle(head);
    printf("ret expected 1,actuall %p\n",ret);
}


void TestCricleLen()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head,'a');
    LinkListPushBack(&head,'b');
    LinkListPushBack(&head,'c');
    LinkListPushBack(&head,'d');
    LinkListPushBack(&head,'e');
    LinkNode* pos_e=LinkListFind(head,'e');
    pos_e->next=head->next;
    int len=LinkListCricleLen(head);
    printf("ret expected 4,actuall %d\n",len);

}

void TestHasCross()
{
    TEST_HEADER;
    LinkNode* head1;
    LinkListInit(&head1);
    LinkListPushBack(&head1,'a'); 
    LinkListPushBack(&head1,'b');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'d');

    LinkNode* head2;
    LinkListInit(&head2);
    LinkListPushBack(&head2,'a');
    LinkListPushBack(&head2,'b');
    LinkListPushBack(&head2,'c');
    //LinkListPushBack(&head2,'d');
    
    LinkNode* pos_c=LinkListFind(head2,'c');
    pos_c->next=head1->next;
    int ret = LinkListHasCross(head1,head2);
    printf("ret expected 1,actuall %d\n",ret);
}

void TestCrossPos()
{
    TEST_HEADER;
    LinkNode* head1;
    LinkListInit(&head1);
    LinkListPushBack(&head1,'a'); 
    LinkListPushBack(&head1,'b');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'d');

    LinkNode* head2;
    LinkListInit(&head2);
    LinkListPushBack(&head2,'a');
    LinkListPushBack(&head2,'b');
    LinkListPushBack(&head2,'c');
    //LinkListPushBack(&head2,'d');
    
    LinkNode* pos_c=LinkListFind(head2,'c');
    pos_c->next=head1->next;
    LinkNode* cross_pos=LinkListCrossPos(head1,head2);
    printf("cross_pos %c\n",cross_pos->data);
}

void TestHasCrossWithCircle()
{
    TEST_HEADER;
    LinkNode* head1;
    LinkListInit(&head1);
    LinkListPushBack(&head1,'a'); 
    LinkListPushBack(&head1,'b');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'d');
    LinkListPushBack(&head1,'e');
    LinkNode* pos_e=LinkListFind(head1,'e');
    pos_e->next=head1->next->next;

    LinkNode* head2;
    LinkListInit(&head2);
    LinkListPushBack(&head2,'a');
    LinkListPushBack(&head2,'b');
    LinkListPushBack(&head2,'c');
    //LinkListPushBack(&head2,'d');
    LinkNode* pos_c=LinkListFind(head2,'c');
    pos_c->next=head1->next;
    int ret =LinkListHasCrossWithCircle(head1,head2);
    printf("[测试环外相交]ret expected 1,actuall %d\n",ret);
       
    LinkNode* head3;
    LinkListInit(&head3);
    LinkListPushBack(&head3,'a');
    LinkListPushBack(&head3,'b');
    LinkListPushBack(&head3,'c');
    LinkNode* pos_c1=LinkListFind(head3,'c');
    pos_c1->next=head1->next->next->next;
    int ret2 =LinkListHasCrossWithCircle(head1,head3);
    printf("[测试环内相交]ret expected 1,actuall %d\n",ret2);


    LinkNode* head4;
    LinkListInit(&head4);
    LinkListPushBack(&head4,'a');
    LinkListPushBack(&head4,'b');
    LinkListPushBack(&head4,'c');
    int ret3 =LinkListHasCrossWithCircle(head1,head4);
    printf("[测试一个带环，一个不带环]ret expected 0,actuall %d\n",ret3);
}

void TestCrossWithCirclePos()
{

    TEST_HEADER;
    LinkNode* head1;
    LinkListInit(&head1);
    LinkListPushBack(&head1,'a'); 
    LinkListPushBack(&head1,'b');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'d');
    LinkListPushBack(&head1,'e');
    LinkNode* pos_e=LinkListFind(head1,'e');
    pos_e->next=head1->next->next;


    LinkNode* head2;
    LinkListInit(&head2);
    LinkListPushBack(&head2,'a');
    LinkListPushBack(&head2,'b');
    LinkListPushBack(&head2,'c');
    //LinkListPushBack(&head2,'d');
    LinkNode* pos_c=LinkListFind(head2,'c');
    pos_c->next=head1->next;
    LinkNode* cross_pos=LinkListCrossWithCirclePos(head1,head2);
    printf("cross_pos %c\n",cross_pos->data);
}


void TestUnionSet()
{

    TEST_HEADER;
    LinkNode* head1;
    LinkListInit(&head1);
    LinkListPushBack(&head1,'a'); 
    LinkListPushBack(&head1,'b');
    LinkListPushBack(&head1,'c');
    LinkListPushBack(&head1,'d');

    LinkNode* head2;
    LinkListInit(&head2);
    LinkListPushBack(&head2,'b');
    LinkListPushBack(&head2,'e');
    //LinkListPushBack(&head2,'c');
    //LinkListPushBack(&head2,'d');

    LinkNode* union_set=LinkListUnionSet(head1,head2);
    LinkListPrintChar(union_set,"链表的交集是");
}

void PrintComplexList(ComplexNode* head,const char* msg)
{
    printf("[%s]\n",msg);
    ComplexNode* cur=head;
    for(;cur!=NULL;cur=cur->next)
    {
        printf("[%c]",cur->data);
    }
    printf("\n");
    for(cur=head;cur!=NULL;cur=cur->next)
    {
        if(cur->random == NULL)
        {
            printf("[NULL]");
            continue;
        }
        printf("[%c]",cur->random->data);
    }
    printf("\n");
}

void TestCopyComplexList()
{
    TEST_HEADER;
    ComplexNode* a=CreateComplexNode('a');
    ComplexNode* b=CreateComplexNode('b');
    ComplexNode* c=CreateComplexNode('c');
    ComplexNode* d=CreateComplexNode('d');
    a->next=b;
    d->next=c;
    c->next=d;
    d->next=NULL;
    a->random=c;
    b->random=a;
    c->random=NULL;
    d->random=d;
    ComplexNode* new_head=CopyComplexList2(a);
    PrintComplexList(new_head,"拷贝复杂链表");

}

int main()
{
    Testsizeof();
    TestInit();
    TestInit2();
    TestInit3();
    TestPushBack();
    TestPopBack();
    TestPushFront();
    TestPopFront();
    TestInsert();
    TestInsertBefore();
    TestInsertBefore2();
    TestErase();
    TestErase2();
    TestFind();
    TestRemove();
    //TestRemoveall();
    //TestEmpty();
    //TestSize();
    //TestFront();
    //TestBack();
    TestPrintReverse();
    TestJosephCricle();
    TestReverse();
    TestFindMidNode();
    TestFindMidNode();
    TestEraseLastKNode();
    TestHasCricle();
    TestCricleLen();
    TestHasCross();
    TestCrossPos();
    TestHasCrossWithCircle();
    TestCrossWithCirclePos();
    TestUnionSet();
    TestCopyComplexList();
    return 0;
}

