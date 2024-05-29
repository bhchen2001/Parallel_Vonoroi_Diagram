class Point{
    private:
        size_t dim = 0;
        double* coords = nullptr;

        void reset_coords(size_t dim){
            if(!this->coords) delete[] this->coords;
            this->dim = dim;
            if (dim) this->coords = new double[dim];
            else this->coords = nullptr;
        }
    public:

        /*
         * Constructors
         */
        Point(int dim, double* coords){
            this->dim = dim;
            this->coords = new double[dim];
            for(size_t i = 0; i < dim; i++){
                this->coords[i] = coords[i];
            }
        }

        Point(double *coords){
            this->dim = sizeof(coords)/sizeof(coords[0]);
            this->coords = new double[dim];
            for(size_t i = 0; i < dim; i++){
                this->coords[i] = coords[i];
            }
        }

        Point(Point const &p){
            this->dim = p.dim;
            for(size_t i = 0; i < dim; i++){
                this->coords[i] = p.coords[i];
            }
        }

        Point& operator=(const Point& p){
            if(this == &p){
                return *this;
            }
            delete[] this->coords;
            this->dim = p.dim;
            this->coords = new double[dim];
            for(size_t i = 0; i < dim; i++){
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
        
        double operator[](size_t i) const{
            return this->coords[i];
        }

        double& operator[](size_t i){
            return this->coords[i];
        }

        /*
         * Getters
         */

        size_t get_dim() const{
            return this->dim;
        }

        double* get_coords() const{
            return this->coords;
        }
};