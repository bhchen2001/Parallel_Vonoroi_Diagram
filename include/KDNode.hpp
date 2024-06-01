#pragma once

#include <Point.hpp>
#include <memory>

class KDNode{
    private:
        Point point;
        std::shared_ptr<KDNode> left = nullptr;
        std::shared_ptr<KDNode> right = nullptr;
        size_t axis = -1;

    public:
        /*
         * Constructor
         */

        KDNode(Point const &point, size_t axis, std::shared_ptr<KDNode> left, std::shared_ptr<KDNode> right){
            this->point = point;
            this->axis = axis;
            this->left = left;
            this->right = right;
        }

        KDNode(Point const &point, size_t axis){
            this->point = point;
            this->axis = axis;
        }

        KDNode(Point const &point){
            this->point = point;
        }

        KDNode(){
            this->point = Point();
        }

        KDNode(KDNode const &node){
            this->point = node.point;
            this->axis = node.axis;
            this->left = node.left;
            this->right = node.right;
        }

        KDNode& operator=(const KDNode &node){
            if(this == &node){
                return *this;
            }
            this->point = node.point;
            this->axis = node.axis;
            this->left = node.left;
            this->right = node.right;
            return *this;
        }

        /*
         * Operator Overloading
         */

        bool operator==(const KDNode& node){
            /*
             * Check if the point and axis of both the nodes are same
             */
            return this->point == node.point && this->axis == node.axis;
        }

        /*
         * Getters
         */

        Point get_point(){
            return this->point;
        }

        std::shared_ptr<KDNode> get_left(){
            return this->left;
        }

        std::shared_ptr<KDNode> get_right(){
            return this->right;
        }

        size_t get_axis(){
            return this->axis;
        }

        /*
         * Setters
         */

        void set_left(std::shared_ptr<KDNode> left){
            this->left = left;
        }

        void set_right(std::shared_ptr<KDNode> right){
            this->right = right;
        }

        void set_point(Point point){
            this->point = point;
        }

        void set_axis(size_t axis){
            this->axis = axis;
        }

        /*
         * Operations
         */

        bool is_leaf(){
            return this->left == nullptr && this->right == nullptr;
        }
};