#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include "OrgChart.hpp"
using namespace std;

namespace ariel{
    OrgChart& OrgChart::add_root(const std::string& name)
    {   //adds a root to the OrgChart
    //if name is empty, throw exception
        if(name.empty()){
            throw std::invalid_argument("name cannot be empty");}
        
        if (root == nullptr){
            root = new Node(name);
            size++;
        }
        else{
            root->set_name(name);
        }
        return *this;
    }
    OrgChart& OrgChart::add_sub(const std::string& parent, const std::string& child)
    { // adds a sub to the OrgChart
    //if parent or chiled is empty, throw exception
    // if parent not found, throw exception
        this->iter_data.clear();
        if(root == NULL){
            throw std::invalid_argument("parent not found");
            return *this;
        }
        if(parent.empty()){
            throw std::invalid_argument("parent cannot be empty");}
        if(child.empty()){
            throw std::invalid_argument("child cannot be empty");}
        std::queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* temp = q.front();
            if (temp->get_name() == parent){
                temp->add_sub(new Node(child));
                this->size++;
                return *this;
            }
            q.pop();
            for(size_t i = 0; i < temp->size(); i++){
                q.push(temp->get_sub()[i]);
            }
        }
        throw std::invalid_argument("parent not found");
    }
    void OrgChart::level_order(Node* root){
        //sets the OrgChart in level order
        //push it to queue for the levels 
        if(root == NULL){
            return;}
        iter_data.push_back(root->get_name());
        std::queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* temp = q.front();
            q.pop();
            for(size_t i = 0; i < temp->size(); i++){
                q.push(temp->get_sub()[i]);
                iter_data.push_back(temp->get_sub()[i]->get_name());
            }
        }
    }
    void OrgChart::rev_level_order(Node* root){
        //sets the OrgChart in reverse level order
        //push it to a stack to reverse it (from right to left children) not like queue
        if(root == NULL){
            return;}
        std::stack <Node *> S;
        std::queue <Node *> Q;
        Q.push(root);
    
        // Do something like normal level order traversal order. Following are the
        // differences with normal level order traversal
        // 1) Instead of printing a node, we push the node to stack
        // 2) Right subtree is visited before left subtree
        while (!Q.empty())
        {
            /* Dequeue node and make it root */
            root = Q.front();
            Q.pop();
            S.push(root);
    
            /* Enqueue right child */
            std::vector<Node *> sub = root->get_sub();
            reverse(sub.begin(), sub.end());
            for (size_t i = 0; i < sub.size(); i++){
                Q.push(sub[i]);}
        }
    
        // Now pop all items from stack one by one and print them
        while (!S.empty())
        {
            root = S.top();
            cout << root->get_name() << " ";
            this->iter_data.push_back(root->get_name());
            S.pop();
        }

    }
    void OrgChart::pre_order(struct Node* node){

        //sets the OrgChart in pre order
    if (node == NULL){
        return;
    }
    this->iter_data.push_back(node->get_name());    
    for (size_t i = 0; i < node->size(); i++){
        this->pre_order(node->get_sub()[i]);}
    /* then print the data of node */
    
    }
    void OrgChart::create_iter_data(int opt){
        switch (opt)
        {
        case 1://call level order
            this->level_order(this->root);
            break;
        
        case 2://call reverse level order
            this->rev_level_order(this->root);

            break;
        
        case 3://call pre order
            cout << "pre order" << endl;

            this->pre_order(this->root);
            
            cout << this->iter_data.size() << endl;

            break;
        }

    }

    std::ostream& operator<<(std::ostream& s, OrgChart& oc){
        /*print like this:
            p 
            p->c1
            p->c2
            p->c1->g1
            p->c1->g2
        */
        cout << "OrgChart:" << endl;
        if(oc.root == NULL){
            return s;
        }
        std::queue<OrgChart::Node*> q;
        std::queue<string> q2;
        int i = 1;
        q.push(oc.root);
        q2.push(oc.root->get_name());
        s << oc.root->get_name() << endl;
        while(!q.empty()){
            OrgChart::Node* temp = q.front();
            q.pop();
            string temp_name = q2.front();
            q2.pop();
            for(size_t i = 0; i < temp->size(); i++){
                q.push(temp->get_sub()[i]);
                string temp_name2 = temp_name + "->" + temp->get_sub()[i]->get_name();
                s << temp_name2 << endl;
                q2.push(temp_name2);
            }
        }
        
        return s;

    }

}