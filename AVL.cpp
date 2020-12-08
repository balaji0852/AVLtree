#include<iostream>
using namespace std;


class node{
  public:
  node *left=NULL,*right=NULL,*parent=NULL;
  int data,bf=0,rh=0,lh=0;
  bool type = false;
  node(int key){
    data = key;
  }

  void insert(int data,node **root);
  void checkBalance(node *root);
  void addheight(node *li_node);
  void rotate(node *li_node);
  int get_rh(node *root){
  return root->rh;
  }
  int get_lh(node *root){
  return root->lh;
  }
};

void node::rotate(node *li_node){
	node **copy = &li_node;
        while((*copy)!=NULL){
        	if((*copy)->bf>1){
 			//left rotate
			if((*copy)->parent==NULL){
				cout<<"RR for root\n";
				node **copy1 = &(*copy)->left->left;
				int data = (*copy)->data;
				(*copy)->data = (*copy)->left->data;
				(*copy)->left->data = data;
				// if((*copy)->left->right!=NULL){
				// 	if((*copy)->right!=NULL ){
				// 		(*copy)->right->left = (*copy)->left->right;
				// 		(*copy)->right->left->parent = (*copy)->right;
				// 		(*copy)->right->lh = (*copy)->left->right->rh+1;
				// 		(*copy)->left->right = (*copy)->right;
				// 		(*copy)->left->rh = (*copy)->right->rh+1;
				// 		(*copy)->left->right->parent = (*copy)->left;
				// 		(*copy)->left->left = NULL;
				// 		cout<<" ,";
				// 	}
				// 	else{
				// 		(*copy)->left->left = (*copy)->left->right;
				// 		(*copy)->left->left->parent = (*copy)->left;
				// 		(*copy)->left->lh = (*copy)->left->right->rh;
				// 		cout<<" ,,";
				// 	}	
				// 	//do cal
				// 	//(*copy)->left->bf = (*copy)->left->-(*copy)->right->rh;
				// // 	//(*copy)->right = (**copy1)->left;
				// }
				// else{
				// 	if((*copy)->right!=NULL ){
				// 		(*copy)->left->right = (*copy)->right;
				// 		(*copy)->left->rh = (*copy)->right->rh+1;
				// 		(*copy)->left->right->parent = (*copy)->left;
				// 		(*copy)->left->left = NULL;
				// 		cout<<" ;;";
				// 	}
				// 	else{
				// 		cout<<" ,";
						(*copy)->right = (*copy)->left;
				 		(*copy)->right->type = true;
				 		(*copy)->left = (*copy)->left->left;
			     		(*copy)->left->parent = (*copy);
						(*copy)->left->left = NULL;
				// 		(*copy)->left->left = NULL;
				// 		//(*copy)->left->left = NULL;
				// 	}
				// }
				
				// 		(*copy)->right->left = (**copy1)->left->right;
				// 		(*copy)->left->right->left->type = false;
				// 		(*copy)->left->right->lh = (**copy1)->left->right->rh+1;
				// 		(*copy)->left->right->left->parent = (*copy)->left->right;
				// }
				
				// // else{
				// // 	(*copy)->left->left = NULL;
				// // }
			   
			
			 	// (*copy)->rh = (*copy)->right->rh+1;
	            // (*copy)->lh = (*copy)->left->lh+1;
				// (*copy)->bf = (*copy)->lh-(*copy)->rh;
				// (*copy)->right->bf = (*copy)->left->lh-(*copy)->right->rh;
				
			}
			if((*copy)->parent!=NULL){
				cout<<"RR \n";
				(*copy)->left->parent = (*copy)->parent;
				(*copy)->parent->left = (*copy)->left;
 				(*copy)->left->right = (*copy);
				(*copy)->parent = (*copy)->left;
				(*copy)->lh = 0;
				(*copy)->type = true;
				(*copy)->bf = 0;
				(*copy)->left = NULL;
				addheight(*copy);
			}	
			
		}
		else if((*copy)->bf<-1){
			cout<<"LL \n";
		}
		(*copy) = (*copy)->parent;
        } 
	return;
}


void node::addheight(node *li_node){
	node **copy = &li_node;
        while((*copy)->parent!=NULL){
		 if((*copy)->lh==0 && (*copy)->right==NULL || (*copy)->rh==0 && (*copy)->left==NULL){
			if((*copy)->type){
 		 		(*copy)->parent->rh = 1;
                	}
                	else{
				
				(*copy)->parent->lh = 1;	
                	}
		}
                else if((*copy)->rh==(*copy)->lh && (*copy)->rh!=0){
			if((*copy)->type){
 		 		(*copy)->parent->rh = (*copy)->parent->rh+1;	
                	}
                	else{
				(*copy)->parent->lh = (*copy)->parent->rh+1;	
                	}
		}
                else if((*copy)->rh>(*copy)->lh){
                	if((*copy)->type){
 		 		(*copy)->parent->rh = (*copy)->rh+1;
			}
                	else{
				(*copy)->parent->lh = (*copy)->rh+1;	
                	}
                }
 		else if((*copy)->lh>(*copy)->rh){
                	if((*copy)->type){
 		 		(*copy)->parent->rh = (*copy)->lh+1;	
                	}
                	else{
				(*copy)->parent->lh = (*copy)->lh+1;	
                	}
                }
		(*copy)->parent->bf = (*copy)->parent->lh-(*copy)->parent->rh;
              	(*copy) = (*copy)->parent;  
        }
	return;
}
 		
  
void node::insert(int data,node **root){
        //if the data is less than parent node
	if(*root==NULL){
		(*root) = new node(data);
		return;
	}
	if(data<=(*root)->data){
                //while left node of current parent is empty
     		if((*root)->left==NULL){
     			node *new_node = new node(data);
                        new_node->parent = (*root);
     			(*root)->left = new_node;
     			cout<<(*root)->data<<"---| L node- "<<data<<"|\n";
			addheight(new_node);
			rotate(new_node);
     			return;
     		}
    		else{
             		//when left node of current parent is not empty
			insert(data,&(*root)->left);
     		}
  	}
        //if the data is more than the root
  	else{
                //while right node of current parent is empty
     		if((*root)->right==NULL){
     			node *new_node = new node(data);
                	new_node->parent = (*root);
                        new_node->type = true;
     			(*root)->right = new_node;
                	cout<<(*root)->data<<"---| R node- "<<data<<"|\n";
			addheight(new_node);
			rotate(new_node);
     			return;
     		}
     		else{
                        //when right node of current parent node is not empty
    			insert(data,&(*root)->right);
     		}
  	}
}





void node::checkBalance(node *root){
 if(root->left!=NULL){
   checkBalance(root->left);
 }
 cout<<root->data;
 if(root->right!=NULL){
   cout<<" r-"<<root->rh<<"---"<<root->right->data;
 }
 else{
   cout<<" r-0";
 }
 if(root->left!=NULL){
 cout<<" l-"<<root->lh<<"---"<<root->left->data;
 }
 else{
   cout<<" l-0";
 }
 cout<<" BF="<<root->bf<<" \n";
 if(root->right!=NULL){
   checkBalance(root->right);
 }

}
  






int main(){

node *root = NULL;
root->insert(9,&root);
root->insert(7,&root);
root->insert(4,&root);
//root->insert(3,&root);
//root->insert(5,&root);
//root->insert(2,&root);
//root->insert(2,&root);
//root->insert(10,&root);
//root->insert(71,&root);
//cout<<root->right->right->parent->parent->lh-root->right->right->parent->parent->rh;
root->checkBalance(root);
//root->addheight(root);
//root->addheight2(root);
//root->addheight(&root);
//root->addheight2(root);
//root->addheight(root);
//root->addheight(root->right->right);
//root->addheight2(root->left);




 
 return 0;
}