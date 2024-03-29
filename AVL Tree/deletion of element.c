#include<stdio.h> 
#include<stdlib.h> 
struct treenode 
{ 
    int data; 
    struct treenode *left; 
    struct treenode *right; 
    int height; 
}; 
int height(struct treenode *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
int max(int a, int b) 
{ 
    return (a > b)?a:b; 
} 
struct treenode* newNode(int key) 
{ 
    struct treenode* node = (struct treenode*) 
                        malloc(sizeof(struct treenode)); 
    node->data  = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1; 
    return(node); 
}
int getBalance(struct treenode *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
}
struct treenode * leftrotate(struct treenode * x){
    struct treenode * y=x->right;
    struct treenode * t2=y->left;
        y->left=x;
        x->right=t2;
    y->height=1+max(height(y->left),height(y->right));
    x->height=1+max(height(x->left),height(x->right));
    return y;
}
struct treenode * rightrotate(struct treenode * x){
    struct treenode * y=x->left;
    struct treenode * t2=y->right;
        y->right=x;
        x->left=t2;
    y->height=1+max(height(y->left),height(y->right));
    x->height=1+max(height(x->left),height(x->right));
    return y;
}
struct treenode * insert(struct treenode * start,int data){
    struct treenode * n;
    n=newNode(data);
    if(start==NULL){
        start=n;
    }
    if(data<start->data){
        start->left=insert(start->left,data);
    }
    else if(data>start->data){
        start->right=insert(start->right,data);
    }
    else {
        return start;
    }
    start->height=1+max(height(start->left),height(start->right));
    int balance=getBalance(start);
    if (balance>1 && data<start->left->data){
        return rightrotate(start);
    }
    else if (balance>1 && data>start->left->data){
        start->left=leftrotate(start->left);
        rightrotate(start);
    }
    else if (balance<-1 && data>start->right->data){
        return leftrotate(start);
    }
    else if (balance<-1 && data<start->right->data){
        start->right=rightrotate(start->left);
        leftrotate(start);
    }
    return start;
}
struct treenode * findmax(struct treenode * start){
    if(start==NULL){
        return NULL;
    }
    while(start->right!=NULL){
        start=start->right;
    }
    return start;
}
struct treenode * delete(struct treenode * start,int key){
    if(start==NULL){
        return NULL;
    }
    else if (key<start->data){
        start->left=delete(start->left,key);
    }
    else if (key>start->data){
        start->right=delete(start->right,key);
    }
    else {
        struct treenode * temp;
        if(start->left!=NULL && start->right!=NULL){
            temp=findmax(start->left);
            start->data=temp->data;
            start->left=delete(start->left,start->data);
        }
        else {
            temp=start;
            if(start->left==NULL){
                start=start->right;
            }
            else if(start->right==NULL){
                start=start->left;
            }
            free(temp);
        }
    }
    return start;
}
struct treenode * avdelete(struct treenode * start,int key){
    if(start==NULL){
        return NULL;
    }
    else if(key<start->data){
        start->left=avdelete(start->left,key);
    }
    else if(key>start->data){
        start->right=avdelete(start->right,key);
    }
    else {// element found
         start=delete(start,key);
        }
    // look for the deletion at gfg please
    if(start!=NULL){
        start->height=1+max(height(start->left),height(start->right));
        int balance=getBalance(start);
        if (balance>1){
            if(key<start->left->data){
                return rightrotate(start);
            }
        }
        else if (balance>1){
            if( key>start->left->data){
                start->left=leftrotate(start->left);
                rightrotate(start);
            }
        }
        else if (balance<-1 ){
            if(key>start->right->data){
                 return leftrotate(start);
            }
        }
        else if (balance<-1){
            if(key<start->right->data){
                start->right=rightrotate(start->left);
                leftrotate(start);
            }
        }
    }
    return start;
}
void preorder(struct treenode *root) 
{ 
    if(root != NULL) 
    { 
        printf("%d ", root->data); 
        preorder(root->left); 
        preorder(root->right); 
    } 
}
int main(){
    int data,key;
    struct treenode * temp;
    struct treenode * root=NULL;
    for (int i=0;i<9;i++){
    printf("\nEnter the data:");
    scanf("%d",&data);
    root=insert(root,data);
    }
    printf("\npreorder of avl :");
    preorder(root);
    printf("\nEnter the element to delete:");
    scanf("%d",&key);
    while(key>=0){
    temp=avdelete(root,key);
    printf("\npreorder of avli :");
    preorder(temp);
    printf("\nEnter the element to delete(Enter negative no. to stop):");
    scanf("%d",&key);
    }
    
}
