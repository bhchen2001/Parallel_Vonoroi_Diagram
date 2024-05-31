# pragma once

#include <KDNode.hpp>
#include <vector>
#include <algorithm>

class KDTree{
    private:
        std::shared_ptr<KDNode> root = nullptr;
        std::shared_ptr<KDNode> build_kd_tree(std::vector<Point> &points, size_t depth);
        size_t dimensions = -1;

    public:
        /*
         * Constructor
         */
        
        KDTree(std::vector<Point> &points, size_t dimensions){
            this->dimensions = dimensions;
            this->root = build_kd_tree(points, 0);
        }

        /*
         * Getter
         */

        std::shared_ptr<KDNode> get_root(){
            return root;
        }

        size_t get_dimensions(){
            return dimensions;
        }

        size_t get_depth(){
            size_t depth = 0;
            std::shared_ptr<KDNode> current = root;

            while(current != nullptr){
                depth++;
                current = current->get_left();
            }

            return depth;
        }

        size_t count_nodes(std::shared_ptr<KDNode> node){
            if(node == nullptr){
                return 0;
            }
            else{
                return 1 + count_nodes(node->get_left()) + count_nodes(node->get_right());
            }
        }

        size_t get_size(){
            return count_nodes(root);
        }

        /*
         * Functionality of KDTree
         */
        void insert_node(Point point);
        bool delete_node(Point point);
};