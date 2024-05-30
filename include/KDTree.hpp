# pragma once

#include <KDNode.hpp>
#include <vector>
#include <algorithm>

class KDTree{
    private:
        KDNode *root = nullptr;
        KDNode *build_kd_tree(std::vector<Point> &points, size_t depth);
        size_t dimensions = 0;

    public:
        /*
         * Constructor
         */
        
        KDTree(std::vector<Point> &points, size_t dimensions){
            this->dimensions = dimensions;
            this->root = build_kd_tree(points, 0);
        }

        /*
         * Destructor
         */

        ~KDTree(){
            delete root;
        }

        /*
         * Getter
         */

        KDNode* get_root(){
            return root;
        }

        /*
         * Functionality of KDTree
         */
        void insert_node(Point point);
        void delete_node(Point point);
};