#pragma once

#include "Point.hpp"

class Rectangle{
    private:
        Point min_corner, max_corner;
        size_t dim = 0;
    public:

        /*
         * Constructors
         */

        Rectangle(Point const &min_corner, Point const &max_corner){
            /*
             * Check if
             *     1. Dimensions of the two points are same
             *     2. min_corner is less than max_corner
             */
            if(min_corner.get_dim() != max_corner.get_dim()){
                throw std::invalid_argument("Dimensions of the two points are not same");
            }
            for(size_t i = 0; i < min_corner.get_dim(); i++){
                if(min_corner[i] > max_corner[i]){
                    throw std::invalid_argument("min_corner is not less than max_corner");
                }
            }
            this->min_corner = min_corner;
            this->max_corner = max_corner;
            this->dim = min_corner.get_dim();
        }

        Rectangle(Rectangle const &rect){
            this->min_corner = rect.min_corner;
            this->max_corner = rect.max_corner;
            this->dim = rect.dim;
        }

        Rectangle(){
            this->min_corner = Point();
            this->max_corner = Point();
            this->dim = 0;
        }

        Rectangle& operator=(const Rectangle &rect){
            if(this == &rect){
                return *this;
            }
            this->min_corner = rect.min_corner;
            this->max_corner = rect.max_corner;
            this->dim = rect.dim;
            return *this;
        }

        Rectangle(Rectangle &&rect){
            this->min_corner = rect.min_corner;
            this->max_corner = rect.max_corner;
            this->dim = rect.dim;
        }

        Rectangle& operator=(Rectangle &&rect){
            if(this == &rect){
                return *this;
            }
            this->min_corner = rect.min_corner;
            this->max_corner = rect.max_corner;
            this->dim = rect.dim;
            return *this;
        }

        /*
         * Operator Overloading
         */

        bool operator==(const Rectangle &rect){
            return this->min_corner == rect.min_corner && \
                   this->max_corner == rect.max_corner && \
                   this->dim == rect.dim;
        }

        /*
         * Getter
         */

        Point get_min_corner() const{
            return min_corner;
        }

        Point get_max_corner() const{
            return max_corner;
        }

        size_t get_dim() const{
            return dim;
        }

        /*
         * Rect Operations
         */

        Rectangle left_half(size_t axis, double split) const{
            Point new_max_corner = max_corner;
            new_max_corner[axis] = split;
            return Rectangle(min_corner, new_max_corner);
        }

        Rectangle right_half(size_t axis, double split) const{
            Point new_min_corner = min_corner;
            new_min_corner[axis] = split;
            return Rectangle(new_min_corner, max_corner);
        }

        bool contains(Point const &point) const{
            for(size_t i = 0; i < point.get_dim(); i++){
                if(point[i] < min_corner[i] || point[i] > max_corner[i]){
                    return false;
                }
            }
            return true;
        }
};

bool intersects(Rectangle const &rect1, Rectangle const &rect2){
    for(size_t i = 0; i < rect1.get_dim(); i++){
        if(rect1.get_min_corner()[i] > rect2.get_max_corner()[i] || \
           rect1.get_max_corner()[i] < rect2.get_min_corner()[i]){
            return false;
        }
    }
    return true;
}