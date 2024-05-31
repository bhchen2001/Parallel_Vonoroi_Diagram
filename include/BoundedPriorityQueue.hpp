#include "Point.hpp"

#include <queue>

struct PairComparator{
    bool operator()(const std::pair<double, Point> &p1, const std::pair<double, Point> &p2){
        return p1.first > p2.first;
    }
};

class BoundedPriorityQueue{
    private:
        std::vector<std::pair<double, Point>> items;
        std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, PairComparator> pq;
        size_t capacity = 0;
        size_t size = 0;

    public:
        /*
         * Constructor
         */
        
        BoundedPriorityQueue(size_t capacity){
            this->capacity = capacity;
        }

        /*
         * Getter
         */

        size_t get_size(){
            return size;
        }

        size_t get_capacity(){
            return capacity;
        }

        std::vector<std::pair<double, Point>> get_items(){
            return items;
        }

        double max_priority(){
            return pq.top().first;
        }

        /*
         * Operations
         */

        void push(double distance, Point const &point){
            if(size < capacity){
                items.push_back(std::make_pair(distance, point));
                pq.push(std::make_pair(distance, point));
                size++;
            }
            else{
                if(distance < pq.top().first){
                    pq.pop();
                    pq.push(std::make_pair(distance, point));
                }
            }
        }
};