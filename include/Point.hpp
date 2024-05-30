#pragma once

#include <cstddef>

class Point{
    private:
        std::size_t dim = 0;
        double *coords = nullptr;

    public:

        /*
         * Constructors
         */
        Point(size_t dim, double *coords){
            this->dim = dim;
            this->coords = new double[dim];
            for(std::size_t i = 0; i < dim; i++){
                this->coords[i] = coords[i];
            }
        }

        Point(Point const &p){
            this->dim = p.dim;
            for(std::size_t i = 0; i < dim; i++){
                this->coords[i] = p.coords[i];
            }
        }

        Point(){
            this->dim = 0;
            this->coords = nullptr;
        }

        Point& operator=(const Point& p){
            if(this == &p){
                return *this;
            }
            delete[] this->coords;
            this->dim = p.dim;
            this->coords = new double[dim];
            for(std::size_t i = 0; i < dim; i++){
                this->coords[i] = p.coords[i];
            }
            return *this;
        }

        Point(Point&& p){
            this->dim = p.dim;
            this->coords = p.coords;
            p.coords = nullptr;
        }

        Point& operator=(Point&& p){
            if(this == &p){
                return *this;
            }
            delete[] this->coords;
            this->dim = p.dim;
            this->coords = p.coords;
            p.coords = nullptr;
            return *this;
        }

        /*
         * Destructor
         */

        ~Point(){
            delete[] this->coords;
        }

        /*
         * Operator Overloading
         */
        
        double operator[](std::size_t i) const{
            return this->coords[i];
        }

        double& operator[](std::size_t i){
            return this->coords[i];
        }

        bool operator==(const Point &p) const{
            if(this->dim != p.dim){
                return false;
            }
            for(std::size_t i = 0; i < this->dim; i++){
                if(this->coords[i] != p.coords[i]){
                    return false;
                }
            }
            return true;
        }

        /*
         * Getters
         */

        std::size_t get_dim() const{
            return this->dim;
        }

        double* get_coords() const{
            return this->coords;
        }
};