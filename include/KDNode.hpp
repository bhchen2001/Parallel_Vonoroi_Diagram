#pragma once

#include <Point.hpp>

class KDNode{
    private:
        Point point;
        KDNode* left = nullptr;
        KDNode* right = nullptr;
        size_t axis = -1;

    public:
        /*
         * Constructor
         */

        KDNode(Point &point, size_t axis, KDNode* left, KDNode* right){
            this->point = point;
            this->axis = axis;
            this->left = left;
            this->right = right;
        }

        KDNode(Point &point, size_t axis){
            this->point = point;
            this->axis = axis;
        }

        KDNode(Point &point){
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
         * Destructor
         */

        ~KDNode(){
            delete this->left;
            delete this->right;
        }

        /*
         * Operator Overloading
         */

        bool operator==(const KDNode& node){
            return this->point == node.point;
        }

        /*
         * Getters
         */

        Point get_point(){
            return this->point;
        }

        KDNode* get_left(){
            return this->left;
        }

        KDNode* get_right(){
            return this->right;
        }

        size_t get_axis(){
            return this->axis;
        }

        /*
         * Setters
         */

        void set_left(KDNode* left){
            this->left = left;
        }

        void set_right(KDNode* right){
            this->right = right;
        }

        void set_point(Point point){
            this->point = point;
        }
};