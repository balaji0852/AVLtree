#include<iostream>
#include<string>
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
				cout<<&(*copy)->left->left<<" \n";
				cout<<(*copy)->left->left->data<<" \n";
				cout<<(*copy1)->data<<" \n";
				cout<<&(*copy1)<<" \n";
			 	if((*copy)->right!=NULL){
					if((*copy)->left->right!=NULL){
						//add (*copy)->right as right child of (*copy)->left and 
						//(*copy)->left->right as left child of (*copy)->left
						(*copy)->left->left = (*copy)->left->right;
						(*copy)->left->lh = (*copy)->left->left->rh+1;
						(*copy)->left->left->type = false;
						//(*copy)->left->left is added, now right element
						(*copy)->left->right = (*copy)->right;
						(*copy)->left->right->parent = (*copy)->left;
						(*copy)->left->rh = (*copy)->left->right->rh+1;
						(*copy)->left->bf = (*copy)->left->lh-(*copy)->left->rh;
					}
					else{
						//adding the (*copy)->right for the (*copy)->left->right
						(*copy)->left->right = (*copy)->right;
						(*copy)->left->right->parent = (*copy)->left;
						(*copy)->left->rh = (*copy)->left->right->rh+1;
						(*copy)->left->lh = 0;
						(*copy)->left->bf = -(*copy)->left->rh;

						//adding (*copy)->left to (*copy)->right
						(*copy)->right = (*copy)->left;
						(*copy)->right->type = true;
						(*copy)->rh = (*copy)->right->rh+1;

						//adding (*copy)->left->left to (*copy)->left
						(*copy)->left = (*copy)->left->left;
						(*copy)->left->parent = (*copy);
						(*copy)->lh = (*copy)->left->lh+1;

						//remvoing (*copy)->left->left from (*copy)->right->left
						(*copy)->right->left = NULL;
						
						//updating the root BF
						(*copy)->bf = (*copy)->lh-(*copy)->rh;
					}
				}
				else{
					//adding the right tree from the left element of root
					(*copy)->right = (*copy)->left;
					(*copy)->right->type = true;
					(*copy)->rh = (*copy)->right->rh+1;
					(*copy)->right->bf = -(*copy)->right->rh;

					//post adding the right node for the root
					(*copy)->right->lh = 0;

					//adding the left tree from the left left element of root
					(*copy)->left = (*copy)->left->left;
					(*copy)->left->parent = (*copy);
					(*copy)->lh = (*copy)->left->lh+1;
					
					//removing left left node of root node, came along to root right left node
					(*copy)->right->left = NULL;

					//updating the BF.
					(*copy)->bf = (*copy)->lh-(*copy)->rh;
				}
				//just RR for the three node tree with bf of root:2
				
				//(*copy)->right->rh = 0;
				//(*copy)->right->lh = 0;
				//(*copy)->right->bf = 0;
				//(*copy)->left = *copy1;
				
				
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
root->insert(3,&root);
root->insert(2,&root);
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