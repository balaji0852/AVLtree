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
			 	if((*copy)->right!=NULL){
					if((*copy)->left->right!=NULL){
						//Two cases exist in the if conditon; case1 and LR Rotation..
						//case1: case for root node rotation with (*copy)->left->right not being empty
						if((*copy)->left->lh >=(*copy)->left->rh){
							cout<<"RR for root \n";

							int data = (*copy)->data;
							(*copy)->data = (*copy)->left->data;
							(*copy)->left->data = data;

							//adding the (*copy)->left->right to (*copy)->left->left 
							(*copy)->parent = (*copy)->left->left;
							(*copy)->left->left = (*copy)->left->right;
							(*copy)->left->left->type = false;
							(*copy)->left->left->lh = (*copy)->left->left->rh;
							(*copy)->left->left->rh = 0;
							(*copy)->left->lh = (*copy)->left->left->lh+1;

							//adding the (*copy)->right to (*copy)->left->right
							(*copy)->left->right = (*copy)->right;
							(*copy)->left->right->parent = (*copy)->left;
							(*copy)->left->rh = (*copy)->left->right->rh+1;
							(*copy)->left->bf = (*copy)->left->lh-(*copy)->left->rh;
							
							//Now adding (*copy)->left to (*copy)->right and adding (*copy)->left->left's address to (*copy)->left
							(*copy)->right = (*copy)->left;
							(*copy)->right->type = true;
							(*copy)->rh = (*copy)->right->rh>=(*copy)->right->lh?(*copy)->right->rh+1:(*copy)->right->lh+1;
							(*copy)->left = (*copy)->parent;
							(*copy)->parent = NULL;
							(*copy)->left->parent = (*copy);
							(*copy)->left->parent = (*copy);
                            (*copy)->lh = (*copy)->left->lh+1;
							(*copy)->bf = (*copy)->lh - (*copy)->rh;
							addheight((*copy)->left->left);
							checkBalance(*copy);
							rotate((*copy)->left->left);
						}
						else{
							//LR Rotation for Root element 
							//case 1: (*copy)->left->right->left==NULL
							//case 2: (*copy)->left->right->left!=NULL

							if((*copy)->left->right->left==NULL){
									cout<<" LR Rotation for root element \n";
									node *new_node = new node((*copy)->left->data);
								 	if ((*copy)->left->left!=NULL){
											(*copy)->parent = (*copy)->left->left;
											new_node->left = (*copy)->parent;
											new_node->left->parent = new_node;
											new_node->lh = new_node->left->lh+1;
											(*copy)->parent = NULL;
									}

									(*copy)->left->right->left = new_node;
									(*copy)->left->right->left->type = false;
									(*copy)->left->right->left->parent = (*copy)->left->right;
									(*copy)->left->right->lh = (*copy)->left->right->left->lh+1;

									(*copy)->left = (*copy)->left->right;
									(*copy)->left->parent = (*copy);
									(*copy)->left->type = false;
									(*copy)->lh = (*copy)->left->lh+1;

									addheight(new_node->left!=NULL?new_node->left:new_node);
									rotate(new_node->left!=NULL?new_node->left:new_node);
							}
							else{
								//case 2
								(*copy)->parent = (*copy)->left->right->left;

								cout<<" LR Rotation for root element \n";

								node **temp = &(*copy)->left->right;

								//creating a new (*copy)->left node
								node *n_node = new node((*copy)->left->data);
								n_node->left = (*copy)->left->left;
								n_node->left->parent = n_node;
								n_node->lh = n_node->left->lh+1;

								(*temp)->left = n_node;
								(*temp)->left->parent = (*temp);
								(*temp)->lh = (*temp)->left->lh+1;

								(*temp)->left->right = (*copy)->parent;
								(*temp)->left->right->parent = (*temp)->left;
								(*temp)->left->rh = (*temp)->left->right->rh+1;

								(*copy)->left = *temp;
								(*copy)->left->parent = (*copy);
								(*copy)->parent = NULL;
								(*copy)->lh = (*copy)->left->lh+1;

								checkBalance(*copy);
								addheight(n_node->right);
								rotate(n_node->right);
								
								

							}


						}
					}
					else{
						int data = (*copy)->data;
						(*copy)->data = (*copy)->left->data;
						(*copy)->left->data = data;

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

					    checkBalance(*copy);
					}
				}
				else{

					int data = (*copy)->data;
					(*copy)->data = (*copy)->left->data;
					(*copy)->left->data = data;
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

				    checkBalance(*copy);
				}
				//just RR for the three node tree with bf of root:2
						
			}
			if((*copy)->parent!=NULL){
				cout<<"RR \n";
				if((*copy)->left->lh>=(*copy)->left->rh){
					//(*copy)->left->lh is greater than (*copy)->left->rh, So it is a RR rotation
					(*copy)->left->parent = (*copy)->parent;
					(*copy)->parent->left = (*copy)->left;
					if((*copy)->left->right!=NULL){
						//adding (*copy)->left->right to (*copy)->left
						(*copy)->left = (*copy)->parent->left->right;
						(*copy)->lh = (*copy)->parent->left->right->rh+1;
						(*copy)->left->parent = (*copy);
						(*copy)->left->type = false;

						(*copy)->parent->left->right = (*copy);
						(*copy)->parent = (*copy)->parent->left;
						(*copy)->type = true;
						(*copy)->bf = (*copy)->lh-(*copy)->rh;

						addheight(*copy);
			
					}
					else{
						(*copy)->left->right = (*copy);
						(*copy)->parent = (*copy)->left;
						(*copy)->lh = 0;
						(*copy)->type = true;
						(*copy)->bf = -(*copy)->rh;
						(*copy)->left = NULL;
						addheight(*copy);
					}
				}
				else{
					//(*copy)->left->rh is greater than (*copy)->left->lh, So it is a LR rotation
					cout<<"LR Rotation for non-root element \n";

						if((*copy)->left->right->left==NULL){
									node *new_node = new node((*copy)->left->data);
								 	if ((*copy)->left->left!=NULL){
											new_node->left = (*copy)->left->left;
											new_node->left->parent = new_node;
											new_node->lh = new_node->left->lh+1;
									}

									(*copy)->left->right->left = new_node;
									(*copy)->left->right->left->type = false;
									(*copy)->left->right->left->parent = (*copy)->left->right;
									(*copy)->left->right->lh = (*copy)->left->right->left->lh+1;

									(*copy)->left = (*copy)->left->right;
									(*copy)->left->parent = (*copy);
									(*copy)->left->type = false;
									(*copy)->lh = (*copy)->left->lh+1;

									addheight(new_node->left!=NULL?new_node->left:new_node);
									rotate(new_node->left!=NULL?new_node->left:new_node);
							}
							else{
								//case 2
								node **child = &(*copy)->left->right->left;
								node **temp = &(*copy)->left->right;

								cout<<"LR Rotation for non-root element \n";

								//creating a new (*copy)->left node
								node *n_node = new node((*copy)->left->data);
								if ((*copy)->left->left!=NULL){
									n_node->left = (*copy)->left->left;
									n_node->left->parent = n_node;
									n_node->lh = n_node->left->lh+1;
								}

								(*temp)->left = n_node;
								(*temp)->left->parent = (*temp);
								(*temp)->lh = (*temp)->left->lh+1;

								(*temp)->left->right = (*child);
								(*temp)->left->right->parent = (*temp)->left;
								(*temp)->left->rh = (*temp)->left->right->rh+1;

								(*copy)->left = *temp;
								(*copy)->left->parent = (*copy);
								(*copy)->lh = (*copy)->left->lh+1;

								checkBalance(*copy);
								addheight(n_node->right);
								rotate(n_node->right);
								
								

							}

				}
			    //checkBalance((*copy)->parent);
			}	
			
		}
		else if((*copy)->bf<-1){




			if((*copy)->parent==NULL){
				cout<<"LL for root\n";
				node **copy1 = &(*copy)->right->right;
				int data = (*copy)->data;
				(*copy)->data = (*copy)->right->data;
				(*copy)->right->data = data;
			 	if((*copy)->left!=NULL){
					if((*copy)->right->left!=NULL){
						//Two cases exist in the if conditon; case1 and LR Rotation..
						//case1: case for root node rotation with (*copy)->left->right not being empty
						if((*copy)->right->rh >=(*copy)->right->lh){
							cout<<"LL for root \n";

							//copying the address of (*copy)->right->right in (*copy)->parent, for future purpose 
							(*copy)->parent = (*copy)->right->right;

							//adding (*copy) as left child of (*copy)->right->left
							//creating a replica of (*copy) to add to left child of (*copy)->right->left
							node *new_node = new node(data);
							new_node->left = (*copy)->left;
							new_node->left->parent = new_node;
							new_node->lh = new_node->left->lh+1;

							node **temp = &(*copy)->right->left;
							node **temp1 = &(*copy)->right->left;

							while((*temp)->left!=NULL){
								temp = &(*temp)->left;
							}

  
							(*temp)->left = new_node;
							new_node->parent = (*temp);
							new_node->type = false;
							(*temp)->lh = new_node->lh+1;
							checkBalance((*copy)->right->left);
						

							//adding the right and left subtree to the root
							(*copy)->left = (*copy)->right->left;
							//checkBalance((*copy)->left);
							cout<< (*copy)->right->left->left->data<<" \n";
							(*copy)->left->parent = (*copy);
							(*copy)->lh = (*copy)->right->left->lh>=(*copy)->right->left->rh?(*copy)->right->left->lh+1:(*copy)->right->left->rh+1;

							(*copy)->right = (*copy)->parent;
							(*copy)->parent = NULL;
							(*copy)->right->parent = (*copy);
							(*copy)->rh = (*copy)->right->rh+1;
							addheight(new_node->left);
							rotate(new_node->left);
						}
						else{
							//(*copy)->left->lh is greater than (*copy)->left->rh, So it is a RL rotation
							// cout<<"RL Rotation for root element \n";

							// //temp stores (*copy)->right
							// node **temp = &(*copy)->right;

							// //creating a node out of (*copy)->right->data;
							// node *n_node = new node((*temp)->data);
							// 	if((*temp)->right!=NULL){
							// 		//adding (*copy)->right->right 
							// 		n_node->right = (*temp)->right;
							// 		n_node->rh = n_node->right->rh+1;
							// 		n_node->right->parent = n_node;
							// 	}
							// 	if((*temp)->left->right!=NULL){
							// 		//adding (*copy)->right->left->right to n_node's left
							// 		n_node->left = (*temp)->left->right;
							// 		n_node->left->parent = n_node;
							// 		n_node->left->type = false;
							// 		n_node->lh = n_node->left->lh+1;
							// 	}
							
							// //Fixing the create n_node to the (*copy)->right->left->right
							// (*temp)->right = n_node;
							// (*temp)->right->parent = *temp;
							// (*temp)->right->type = true;
							// (*temp)->rh = (*temp)->right->rh+1;

							// //adding the (*temp) to right (*copy)->right
							// (*copy)->right = *temp;
							// (*copy)->right->parent = (*copy);

							// addheight(n_node);
							// rotate(n_node);
						}
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

					    checkBalance(*copy);
					}
				}
				else{
					//adding the left tree from the right  element of root
					(*copy)->left = (*copy)->right;
					(*copy)->left->type = false;
					(*copy)->lh = (*copy)->left->lh+1;
					(*copy)->left->bf = (*copy)->left->lh;

					//post adding the left node for the root
					(*copy)->left->rh = 0;

					//adding the right tree from the right right element of root
					(*copy)->right = (*copy)->right->right;
					(*copy)->right->parent = (*copy);
					(*copy)->rh = (*copy)->right->rh+1;
					
					//removing right right node of root node, came along to root left right node
					(*copy)->left->right = NULL;

					//updating the BF.
					(*copy)->bf = (*copy)->lh-(*copy)->rh;

				    checkBalance(*copy);
				}
				//just RR for the three node tree with bf of root:2
						
			}
			if((*copy)->parent!=NULL){
				cout<<"LL ROTATION \n";
				if((*copy)->right->rh>=(*copy)->right->lh){
					//(*copy)->right->rh is greater than (*copy)->right->lh, So it is a LL rotation
					(*copy)->right->parent = (*copy)->parent;
					(*copy)->parent->right = (*copy)->right;
					if((*copy)->right->left!=NULL){
						//adding (*copy) below (*copy)->right->left
						insert((*copy)->data,&(*copy)->right);
						if((*copy)->left!=NULL){
							node **temp = &(*copy)->right->left;
							while((*temp)->left!=NULL){
								temp = &(*temp)->left;
							}
							(*temp)->left = (*copy)->left;
							(*temp)->left->parent = (*temp);
							(*temp)->lh = (*temp)->left->lh+1;
							addheight((*temp)->left);
							rotate((*temp)->left);
							//insert((*copy)->left->data,&(*copy)->right);
						}
						//insert will manage to add (*copy)
					}
					else{
						//direct LL Rotation without any (*copy)->right->left node
						(*copy)->right->left = (*copy);
						(*copy)->parent = (*copy)->right;
						(*copy)->right = NULL;
						(*copy)->rh = 0;
						(*copy)->type = false;
						(*copy)->bf = (*copy)->lh;
						addheight(*copy);
						checkBalance((*copy)->parent->parent);
					}
				}
				else{
							//(*copy)->left->lh is greater than (*copy)->left->rh, So it is a RL rotation
							cout<<"RL Rotation for non-root element \n";

							//temp stores (*copy)->right
							node **temp = &(*copy)->right;

							//creating a node out of (*copy)->right->data;
							node *n_node = new node((*temp)->data);
								if((*temp)->right!=NULL){
									//adding (*copy)->right->right 
									n_node->right = (*temp)->right;
									n_node->rh = n_node->right->rh+1;
									n_node->right->parent = n_node;
								}
								if((*temp)->left->right!=NULL){
									//adding (*copy)->right->left->right to n_node's left
									n_node->left = (*temp)->left->right;
									n_node->left->parent = n_node;
									n_node->left->type = false;
									n_node->lh = n_node->left->lh+1;
								}
							
							//Fixing the create n_node to the (*copy)->right->left->right
							(*temp)->right = n_node;
							(*temp)->right->parent = *temp;
							(*temp)->right->type = true;
							(*temp)->rh = (*temp)->right->rh+1;

							//adding the (*temp) to right (*copy)->right
							(*copy)->right = *temp;
							(*copy)->right->parent = (*copy);

							addheight(n_node);
							rotate(n_node);

				}
			    //checkBalance((*copy)->parent);
			}	




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
 		 		(*copy)->parent->rh = (*copy)->rh+1;
				//changed (*copy)->parent->rh+1 to (*copy)->rh+1
            }
            else{
				(*copy)->parent->lh = (*copy)->rh+1;	
				//changed (*copy)->parent->lh+1 to (*copy)->lh+1
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
root->insert(8,&root);
root->insert(5,&root);
root->insert(4,&root);
root->insert(10,&root);
root->insert(12,&root);
root->insert(9,&root);
root->insert(9,&root);
root->insert(10,&root);
root->insert(11,&root);
root->insert(12,&root);
root->insert(11,&root);
root->insert(11,&root);
root->insert(4,&root);
root->insert(3,&root);
root->insert(3,&root);
root->insert(1,&root);
root->insert(4,&root);
root->insert(3,&root);
root->insert(3,&root);
root->insert(1,&root);
root->checkBalance(root);
//root->insert(6,&root);

// root->insert(7,&root);




















root->checkBalance(root);
//cout<<root->right->right->parent->parent->lh-root->right->right->parent->parent->rh;

//root->addheight(root);
//root->addheight2(root);
//root->addheight(&root);
//root->addheight2(root);
//root->addheight(root);
//root->addheight(root->right->right);
//root->addheight2(root->left);


 return 0;
}