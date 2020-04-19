// ========[AVL Tree]======== //
/*
    Dibuat dan ditulis oleh ABDUR ROCHMAN
    28-03-2020
    Struktur Data 2020
    For C
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

void sumright(AVLNode *root, int* lc, int* rc, int index);
void sumleft(AVLNode *root, int* lc, int* rc, int index);


AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int _max(int a,int b){
    return (a > b)? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value){
    
    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
    	node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data)
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL)
        return node;
    if(value > node->data)
    	node->right=_remove_AVL(node->right,value);
    else if(value < node->data)
    	node->left=_remove_AVL(node->left,value);
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=_remove_AVL(node->right,temp->data);
        }    
    }

	if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor<-1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor<-1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl,int value){
    // Duplicate value cannot be added!
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }

}

void avl_remove(AVL *avl,int value){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }
}

void preorder(AVLNode *root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int leftmax = 0;
int rightmax = 0;

void left(AVLNode *root){
    if(root->left != NULL){
        leftmax++;
        left(root->left);
    }
}

void right(AVLNode *root){
    if(root->right != NULL){
        rightmax++;
        right(root->right);
    }
}

void sumleft(AVLNode *root, int* lc, int* rc, int index){
    if(root){
        if(index > leftmax){
            leftmax = index;
            lc = realloc(lc, leftmax * sizeof(int) );
        }

        if(index < 0){
            // do rightsum
            sumright(root, lc, rc, index*-1);
        }else{
            // printf("lefcol[%d] += %d\n", index, root->data);
            *(lc + index) += root->data;
            sumleft(root->left, lc, rc, ++index);
            sumleft(root->right, lc, rc, index-2);
        }
    }else{
        // leftdone = 1;
    }
}

void sumright(AVLNode *root, int* lc, int* rc, int index){
    if(root){
        if(index > rightmax){
            rightmax = index;
            rc = realloc(rc, rightmax * sizeof(int) );
        }

        if(index < 0){
            // do leftsum
            sumleft(root, lc, rc, index*-1);
        }else{
            // printf("rigcol[%d] += %d\n", index, root->data);
            *(rc + index) += root->data;
            sumright(root->right,lc, rc, ++index);
            sumright(root->left, lc, rc, index-2);
        }
    }
}


int findwidht(AVLNode *root){
    left(root);
    right(root);
    return leftmax + rightmax + 1;
    // printf("Left : %d | Right : %d\n",leftmax, rightmax);
}

int main(){
    AVL avlku;
    avl_init(&avlku);

    int n;
    scanf("%d", &n);
    while(n--){
        char kal[10];
        
        scanf("%s", &kal);
        if(!strcmp(kal, "insert")){
            int x;
            scanf("%d", &x);
            avl_insert(&avlku,x);    
        }else if(!strcmp(kal, "print")){
            int lebar = findwidht(avlku._root);
            int* lefcol = malloc((leftmax + 1) * sizeof(int) );
            int i;
            for(i=0; i< leftmax+1; i++){
                *(lefcol +i) = 0;
            }
            int* rigcol = malloc((rightmax + 1) * sizeof(int) );
            for(i=0; i< rightmax+1; i++){
                *(rigcol +i) = 0;
            }
            // int col[lebar];
            sumleft(avlku._root->left, lefcol, rigcol, 1);
            sumright(avlku._root->right, lefcol, rigcol, 1);
            leftmax += 1;
            while(--leftmax){
                // printf("rigcol[%d] = ", leftmax);
                if(*(lefcol+leftmax) == 0){
                    continue;
                }
                printf("%d ", *(lefcol+leftmax));
            }
            printf("%d ", *(lefcol+0) + *(rigcol+0) + avlku._root->data);
            i=0;
            while(++i <= rightmax){
                // printf("rigcol[%d] = ", i);
                if(*(rigcol+i) == 0){
                    continue;
                }
                printf("%d ", *(rigcol+i));
            }
            printf("\n");
            // preorder(avlku._root);
        }
    }
}
