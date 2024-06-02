# pragma once

#include "BoundedPriorityQueue.hpp"
#include "Rectangle.hpp"
#include "Point.hpp"
#include "KDNode.hpp"

#include <vector>
#include <algorithm>

class KDTree{
    private:
        std::shared_ptr<KDNode> root = nullptr;
        Rectangle get_initial_region(size_t dim);
        std::shared_ptr<KDNode> build_kd_tree(std::vector<Point> &points, size_t depth, const Rectangle &region);
        size_t dimensions = -1;

    public:
        /*
         * Constructor
         */
        
        KDTree(std::vector<Point> &points, size_t dimensions){
            this->dimensions = dimensions;
            Rectangle initial_region = get_initial_region(dimensions);
            this->root = build_kd_tree(points, 0, initial_region);
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
         * Tree Operations
         */
        
        void insert_node(Point point);
        bool delete_node(Point point);

        /*
         * Search Operations
         */

        std::vector<Point> search_nearest_neighbors(Point point, size_t k);
        void search_nearest_neighbors_recursive(Point point, std::shared_ptr<KDNode> current, BoundedPriorityQueue &bpq, size_t k);

        std::vector<Point> range_search(Rectangle &range);
        void range_search_recursive(Rectangle &range, std::shared_ptr<KDNode> current, std::vector<Point> &points);
};