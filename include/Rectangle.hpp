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

        bool contains(Point const &point) const{
            for(size_t i = 0; i < point.get_dim(); i++){
                if(point[i] < min_corner[i] || point[i] > max_corner[i]){
                    return false;
                }
            }
            return true;
        }
};