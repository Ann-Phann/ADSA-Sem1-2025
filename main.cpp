#include <iostream>
#include <sstream>
#include <vector>
#include <string>




// Define TreeNode here (as a struct or class)
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
};
// pre defined
TreeNode* insert(TreeNode* node, int val);
TreeNode* deletion(TreeNode* root, int key);

void preOrder (TreeNode* root) {
    if (root == nullptr) return;

    // print the node 
    std::cout << root->val << " ";

    // go left
    preOrder(root->left);

    // go right
    preOrder(root->right);
}

void inOrder (TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    // go left 
    inOrder(root->left);

    // deal with the node
    std::cout << root->val << " ";

    // go right
    inOrder(root->right);
}

void postOrder (TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    // go left 
    postOrder(root->left);

    // go right
    postOrder(root->right);

    // deal with node 
    std::cout << root->val << " ";
}

void printMethod(std::string method, TreeNode* root) {
    if (root == nullptr) {
        std::cout << "EMPTY";
        return;
    }

    if (method == "IN") inOrder (root);
    
    else if (method == "PRE") preOrder(root);
        
    else if (method == "POST") postOrder(root);
}

TreeNode* workOnAVL(TreeNode* root, std::string instruction) {
    // get the instruction Aint (insert int) or Dint (delete int) 
    char method = instruction[0];

    // create own copy --> no interfere
    std::string copy = instruction;

    // get the value
    copy = copy.substr(1);
    
    // translate from string to int
    int value = std::stoi(copy);

    if (method == 'A') {
        return insert(root, value);
    } 

    else if (method == 'D') {
        return deletion(root, value);
    }

    return root;
}

// get height of a node
int getHeightOfNode (TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// update, if have 2 children, take the max height
void updateHeight (TreeNode* node) {
    if (node) {
        node->height = 1 + std::max(getHeightOfNode(node->left), getHeightOfNode(node->right));
    }
}

TreeNode* rotateLeft(TreeNode* node) {
    TreeNode* currentRightChild = node->right;
    TreeNode* leftOfCurrentRight = currentRightChild->left;

    // perform roation
    currentRightChild->left = node;
    node->right = leftOfCurrentRight;

    // update height after rotation
    updateHeight(node);
    updateHeight(currentRightChild);

    return currentRightChild;
}

TreeNode* rotateRight(TreeNode* node) {
    TreeNode* currentLeftChild = node->left;
    TreeNode* rightOfCurrentLeft = currentLeftChild->right;

    // perform rotation
    currentLeftChild->right = node;
    // connect the node with the current branch/node on the right of the new parent
    node->left = rightOfCurrentLeft;

    // update heights
    updateHeight(node);
    updateHeight(currentLeftChild);

    return currentLeftChild;
    
}

// get the balance factor --> only allow {-1, 0, 1} or else it will be unbalanced --> balance that out-of-range node
int getBalanceFactor(TreeNode* node) {
    return getHeightOfNode(node->left) - getHeightOfNode(node->right);
}

TreeNode* insert(TreeNode* node, int val) {

    // insert at leaf or have no TreeNode at the begining
    if (node == nullptr) return new TreeNode(val);

    // if can find the value / the value is already in the tree
    if (node->val == val) {
        return node;
    }

    // insert the right hand side if the new key value > current node->val
    if (val > node->val) {
        node->right = insert(node->right, val);
    } 
    // insert the left hand side if the new key value < current node->val
    else if (val < node->val) {
        node->left = insert(node->left, val);
    }

    // calculate the height of the previous node (the node above the new node)
    updateHeight(node);

    // then get the balance factor of the node
    int balance = getBalanceFactor(node);

    // if become imbalnce --> 4 cases

    // case 1: left left imbalance
    if (balance > 1 && node->left->val > val) {
        // only 1 rotate
        return rotateRight(node);
    }

    // Case 2: left right imbalance: 2 step rotation
    if (balance > 1 && node->left->val < val) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Case 3: right right imbalance
    if (balance < -1 && node->right->val < val) {
        return rotateLeft(node);
    }

    // Case 4: right left imbalance
    if (balance < -1 && node->right->val > val) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// get largest --> go right: inorder predeseccor
TreeNode* getLargestFromLeftSubTree (TreeNode* node) {
    // // recursion way 
    // if (node == nullptr || node->right == nullptr) {
    //     return node;
    // }
    // return getLargestFromLeftSubTree(node->right);

    
    // iterative way:
    TreeNode* current = node;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
    
}

// return the root of the modified subtree
TreeNode* deletion(TreeNode* root, int key) {
    /*
    Deletion is like BST. Have 3 types:
    - no child: at leaf
    - one child
    - two child
    */

    // if no TreeNode or cannot find the node
    if (root == nullptr) return root;

    //////////// First: find and delete ////////////
    // if key < the current node value --> call delete on the left subtree
    if (key < root->val) {
        root->left = deletion(root->left, key);
    }

    else if (key > root->val)
    {
        root->right = deletion(root->right, key);
    }
    // if the same as the key --> the node have to be deleted
    else {
        // node with only 1 child or no child 
        if ((root->left == nullptr) || (root->right == nullptr)) {
            // TreeNode* temp = nullptr;
            // if (root->left) {
            //     temp = root->left;
            // } else {
            //     temp = root->right;
            // }
            TreeNode* temp = root->left ? root->left : root->right;

            // no child case
            if (temp == nullptr) {
                // technically fine but not too readable
                // temp = root;
                // root = nullptr;
                // delete temp;
                

                // will not do balance for the deleted node but when return the nullptr to the parent, the parent will do the updateHeight and rebalance
                delete root;
                return nullptr;
            }
            // 1 child case: preserve the child (which is temp) and delete the current root node,
            else {
                TreeNode* nodeTobeDeleted = root;
                root = temp;
                delete nodeTobeDeleted;
            }
        } 
        // node with two children: get the largest from the left subtree
        else {
            TreeNode* temp = getLargestFromLeftSubTree(root->left);

            // copy this inorder predessesor to the node value
            root->val = temp->val;

            // delete the inorder predeseesor
            root->left = deletion(root->left, temp->val);
        }
    }    

    /////////// Second: update the height and get the balance factor /////////////
    // handle the no child case where we delete the root already
    if (root == nullptr) return root;

    // update the height
    updateHeight(root);

    // get the balance factor of the node to check if this node became unbalnced
    int balance = getBalanceFactor(root);

    /////////// Third: Rebalance if needed /////////////
    if (balance > 1) {
        // left left case
        if (getBalanceFactor(root->left) >= 0){
            return rotateRight(root);
        }
        // left right case
        else if (getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if (balance < -1) {
        // right right case 
        if (getBalanceFactor(root->right) <=0) {
            return rotateLeft(root);
        }
        // right left case
        else if (getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;

}

int main (void) {
    // get the input
    std::string input;
    std::getline(std::cin, input);

    std::string word;
    std::stringstream ss (input);

    std::vector<std::string> instructions;
    while (ss >> word){
        instructions.push_back(word);
    }
    int sizeInstr = instructions.size();

    TreeNode* avl = nullptr;
    for (int i = 0; i < sizeInstr - 1; i++) {
        avl =  workOnAVL(avl, instructions[i]);
    }

    printMethod(instructions[sizeInstr - 1], avl);

    return 0;
}