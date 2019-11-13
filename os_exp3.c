#include <stdio.h>
#include <stdlib.h>

typedef struct Page {
	int flag; //ҳ���� 
	int read;    //Rλ�������Ƿ���� 
	int modify;    //Mλ�������Ƿ�д�� 
	struct Page* next;  //��һ�ڵ� 
	
}Page;

void add_node(Page* head, Page* node) {
	
	Page* p = head;
	while(p->next != head) p = p->next;
	
	p->next = node;
	node->next = head;
}

void traversal_list_from(Page* head) {
	
	Page* p = head;
	
	printf("��ǰ��ҳ�����(-1ҳ��˵����ҳ��δ��ʹ��):\n");
	printf("ҳ��    R    M\n");
	
	do {
		printf("%d      %d    %d\n",p->flag,p->read,p->modify);
		p = p->next;
	} while(p!=head); 
}

void clock_displace_algorithm(Page* head, int flag, int read, int modify) {
	
	Page* p = head;
	
	/*
	��һ�ֲ��ң�����Ŀ��ΪR=0��M=0�Ľ�㣬���û� 
	*/ 
	do {
		
		if(p->read == 0 && p->modify == 0) {
			
			printf("��ҳ��Ϊ%d��ҳ����̭\n",p->flag);
		    p->flag = flag;
		    p->read = read;
		    p->modify = modify;
		    return;
		}
		
		p = p->next;
	}while(p!=head);
	
	/*
	�ڶ��ֲ��ң�����Ŀ��ΪR=0��M=1�Ľ�㣬���û�,��������ɨ�����ҳ�ŵ�R��Ϊ0��
	*/
    do {
		
		if(p->read == 0 && p->modify == 1) {
			
			printf("��ҳ��Ϊ%d��ҳ����̭\n",p->flag);
		    p->flag = flag;
		    p->read = read;
		    p->modify = modify;
		    return;
		}
		p->read = 0;
		p = p->next;
		
	}while(p!=head); 
	 
	/*
	�����ֲ���֮����δ�ҵ�������ִ��һ�飬��ʱ�����ҵ������������ֵݹ� 
	*/ 
	clock_displace_algorithm(head,flag,read,modify);
}

int direct_alloc(Page* head, int flag, int read, int modify) {
	
	Page* p = head;
	do {
		if(p->flag == -1) { p->flag = flag; p->read = read; p->modify = modify; return 1;}
		p = p->next;
	}while(p!=head);
	
	return 0;
}

Page* construct_loop_list() {
	
	int i;
	int number;
	
	Page* head = (Page*)malloc(sizeof(Page));
	head->next = head;
	head->flag = -1;
	head->read = 0;
	head->modify = 0; 
	
	printf("������ҵ��ռ�õ���ҳ����:");
	scanf("%d",&number);
	
	for(i=0;i<number-1;i++) {
		
		Page* node = (Page*)malloc(sizeof(Page));
		node->read = 0;
		node->flag = -1;
		node->modify = 0;
		
		add_node(head,node);
	}
	
	return head;
}

void input_req_sequence(Page* head) {
	
	int flag, read, modify;
	
	while(1) {
	
	    printf("������һ����ҳ�ŷ�����������У���ʽΪ(�����ҳ�� �Ƿ�� �Ƿ�д)������Ϊ1��Ϊ0 ���ָ�����Ϊ�˳�:");
	    scanf("%d %d %d",&flag,&read,&modify);
	    
	    if(flag < 0 || read < 0 || modify < 0) break;
	
	    if(direct_alloc(head,flag,read,modify)) continue;
	
	    clock_displace_algorithm(head,flag,read,modify);
	
	    traversal_list_from(head);
    }
}

void user_select(Page* head) {
	
	int sel;
	while(1) {
		printf("����ѡ����ѡ��:(1)����һ����������(2)��ӡ��ǰҳ������(����)�˳�:");
	    scanf("%d",&sel);
	    
	    if (sel == 1) input_req_sequence(head);
	    else if (sel == 2) traversal_list_from(head);
	    else break;
	}
}

int main (void) {
	
	Page* head = construct_loop_list();
	
	user_select(head);
}
